// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <cassert>
#include <iostream>
#include <unordered_map>
#include "singleton.h"
#include "glfwWindow.h"

ShaderProperties::ShaderProperties()
    : uiTextureSampler(0), uiTextureHandle(0), uiPositionHandle(0) {}

void ShaderProperties::init(Shader &uiShader) {
  uiPositionHandle = uiShader.getAttribLocation("a_position");
  uiTextureHandle = uiShader.getAttribLocation("a_texture");
  uiTextureSampler = uiShader.getUniformLocation("u_texture");
}

struct GWindowMgr {
private:
  std::unordered_map<GLFWwindow *, GLWindow *> windowMap;

public:
  void insertNewWindow(GLWindow *window);
  GLWindow *getGLWindow(GLFWwindow *window);
  static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);
  static void windowResizeCallback(GLFWwindow *window, int width, int height);
};

typedef SingletonBase<GWindowMgr> Singleton;

void GWindowMgr::keyCallback(GLFWwindow *window, int key, int scancode,
                             int action, int mods) {
  GLWindow *glWindow = Singleton::get().getGLWindow(window);
  if (glWindow == nullptr) {
    return;
  }
  for (const keyCallBack &kb : glWindow->getKeyCallBacks()) {
    kb(window, key, scancode, action, mods);
  }
}

void GWindowMgr::windowResizeCallback(GLFWwindow *window, int width,
                                      int height) {
  GLWindow *glWindow = Singleton::get().getGLWindow(window);
  if (glWindow == nullptr) {
    return;
  }
  glWindow->windowResized(width, height);
}

void GWindowMgr::insertNewWindow(GLWindow *window) {
  if (window) {
    windowMap[window->getGLFWwindow()] = window;
  }
}

GLWindow *GWindowMgr::getGLWindow(GLFWwindow *window) {
  if (windowMap.count(window) == 1) {
    return windowMap[window];
  }
  return nullptr;
}

const std::vector<keyCallBack> &GLWindow::getKeyCallBacks() {
  return keyCallBacks;
}

static void keyCallbackInit(GLFWwindow *window,
                            std::vector<keyCallBack> &keyCallbacks) {
  keyCallbacks.push_back([](GLFWwindow *window, int key, int scancode,
                            int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      std::cout << "esc pressed on "
                << Singleton::get().getGLWindow(window)->Title() << std::endl;
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
  });

  glfwSetKeyCallback(window, GWindowMgr::keyCallback);
}

static void resizeCallbackInit(GLFWwindow *window) {

  glfwSetWindowSizeCallback(window, GWindowMgr::windowResizeCallback);
}

void GLWindow::windowResized(int width, int height) {
  this->mWidth = width;
  this->mHeight = height;
  glViewport(0, 0, width, height);
  for (int rectIndex = 0; rectIndex < mRectangles.size(); rectIndex++) {
    for (int i = 0; i < height; i += height / mLayout.Cols) {
      for (int j = 0; j < width; j += width / mLayout.Rows) {
        mRectangles[rectIndex]->storePoints(
            Rectangle::toCartesian(j, i, width, height),
            Rectangle::toCartesian(j + width / mLayout.Rows, i, width, height),
            Rectangle::toCartesian(j + width / mLayout.Rows,
                                   i + height / mLayout.Cols, width, height),
            Rectangle::toCartesian(j, i + height / mLayout.Cols, width,
                                   height));
        mRectangles[rectIndex]->getPixelBuffer()->resizeBuffer(width, height);
      }
    }
  }
}

static GLFWwindow *glfwWindowInit(const std::string &title, int width,
                                  int height) {
  GLFWwindow *window =
      glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    std::cerr << "Failed to initialize GLFW Window!" << std::endl;
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize OpenGL context" << std::endl;
    exit(EXIT_FAILURE);
  }
  return window;
}

GLFWwindow *GLWindow::getGLFWwindow() { return this->pGlfwWindow; }

void GLWindow::glInit() {
  glViewport(0.0f, 0.0f, width(), height());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width(), height(), 0, 0, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void GLWindow::insertKeyCallback(keyCallBack &kb) {
  this->keyCallBacks.push_back(kb);
}

GLWindow::GLWindow(std::string title, int width, int height,
                   RectangleLayout layout)
    : Window(title, width, height), pGlfwWindow(nullptr), keyCallBacks(),
      mRectangles(), mPlainShader(), mShaderProperties(), mLayout(layout) {}

GLWindow::~GLWindow() {
  if (pGlfwWindow) {
    glfwDestroyWindow(pGlfwWindow);
  }
  glfwTerminate();
}

void GLWindow::loadShaders() {
  int attempts = 0;
  while (attempts < 3) {
    try {
      // glEnable(GL_TEXTURE_2D);
      mPlainShader.loadShaders("shaders/uiShader.vert",
                               "shaders/uiShader.frag");
      mShaderProperties.init(mPlainShader);
      drawCallBack dfunc = [this]() {
        for (unsigned int i = 0; i < this->mRectangles.size(); i++) {
          mRectangles[i]->render(mShaderProperties.uiPositionHandle,
                                 mShaderProperties.uiTextureHandle);
        }
      };
      // TODO setup the pixelBuffer
      insertDrawCallback(dfunc);
      return;
    } catch (std::runtime_error &error) {
      std::cerr << error.what() << std::endl;
    } catch (std::exception &error) {
      std::cerr << error.what() << std::endl;
    }
    attempts++;
  }
  std::cerr << "Max attempts of " << attempts << " reached." << std::endl;
  exit(EXIT_FAILURE);
}

#if DEBUG
void GLWindow::queryGPU() {
  const char *gl_vendor =
      reinterpret_cast<const char *>(glGetString(GL_VENDOR));
  const char *gl_renderer =
      reinterpret_cast<const char *>(glGetString(GL_RENDERER));
  const char *gl_version =
      reinterpret_cast<const char *>(glGetString(GL_VERSION));
  const char *gl_extensions =
      reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS));
  std::cout << "GL_VENDOR: " << (gl_vendor ? gl_vendor : "(null)") << std::endl;
  std::cout << "GL_RENDERER: " << (gl_renderer ? gl_renderer : "(null)")
            << std::endl;
  std::cout << "GL_VERSION: " << (gl_version ? gl_version : "(null)")
            << std::endl;
  std::cout << "GL_EXTENSIONS: " << (gl_extensions ? gl_extensions : "(null)")
            << std::endl;
}
#endif

void GLWindow::run() {
  try {
    while (!glfwWindowShouldClose(pGlfwWindow)) {
      if (this->pGlfwWindow != glfwGetCurrentContext()) {
        glfwMakeContextCurrent(this->pGlfwWindow);
      }
      glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      mPlainShader.begin();

      draw();

      // Swap buffers
      glfwSwapBuffers(pGlfwWindow);

      // this has to run on the main thread
      glfwPollEvents();

      mPlainShader.end();
    }
  } catch (std::runtime_error &error) {
    std::cerr << error.what() << std::endl;
    std::cin.get();
  } catch (std::exception &error) {
    std::cerr << error.what() << std::endl;
    std::cin.get();
  }
}

void GLWindow::init() {
  if (glfwInit() != GL_TRUE) {
    std::cerr << "Failed to initialize GLFW!" << std::endl;
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->pGlfwWindow = glfwWindowInit(mTitle, width(), height());
  Singleton::get().insertNewWindow(this);
  keyCallbackInit(this->pGlfwWindow, this->keyCallBacks);
  glInit();

#ifdef DEBUG
  queryGPU();
#endif

  loadShaders();
  mRectangles.push_back(std::make_unique<Rectangle>(width(), height()));
}

PixelBuffer *GLWindow::getPixelBuffer() {
  return mRectangles[0]->getPixelBuffer();
}

void GLWindow::setPixel(size_t x, size_t y, uint8_t color) {
  mRectangles[0]->setPixel(x, y, color);
}

void GLWindow::setPixel(size_t x, size_t y, glm::u8vec4 color) {
  mRectangles[0]->setPixel(x, y, color);
}

void GLWindow::setPixel(size_t x, size_t y, glm::u8vec3 color) {
  mRectangles[0]->setPixel(x, y, color);
}