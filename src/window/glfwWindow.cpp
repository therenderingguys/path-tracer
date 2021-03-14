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

struct KeyCallbackStruct {
private:
  std::unordered_map<GLFWwindow *, GWindowMgr *> windowMap;

public:
  void insertNewWindow(GWindowMgr *window);
  GWindowMgr *getWindowMgr(GLFWwindow *window);
  static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);
};

typedef SingletonBase<KeyCallbackStruct> Singleton;

void KeyCallbackStruct::keyCallback(GLFWwindow *window, int key, int scancode,
                                    int action, int mods) {
  GWindowMgr *windowMgr = Singleton::get().getWindowMgr(window);
  if (windowMgr == nullptr) {
    return;
  }
  for (const keyCallBack &kb : windowMgr->getKeyCallBacks()) {
    kb(window, key, scancode, action, mods);
  }
}

void KeyCallbackStruct::insertNewWindow(GWindowMgr *window) {
  if (window) {
    windowMap[window->getGLFWwindow()] = window;
  }
}

GWindowMgr *KeyCallbackStruct::getWindowMgr(GLFWwindow *window) {
  if (windowMap.count(window) == 1) {
    return windowMap[window];
  }
  return nullptr;
}

const std::vector<keyCallBack> &GWindowMgr::getKeyCallBacks() {
  return keyCallBacks;
}

static void keyCallbackInit(GLFWwindow *window,
                            std::vector<keyCallBack> &keyCallbacks) {
  keyCallbacks.push_back([](GLFWwindow *window, int key, int scancode,
                            int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      std::cout << "esc pressed on "
                << Singleton::get().getWindowMgr(window)->Title() << std::endl;
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
  });

  glfwSetKeyCallback(window, KeyCallbackStruct::keyCallback);
}

void GWindowMgr::textureInit() {
  //std::cout << *(this->mPixelBuffer.get()) << std::endl;
  glGenTextures(1, &this->pixelBufferTexture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->pixelBufferTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->Width(), this->Height(), 0,
               GL_RGB, GL_UNSIGNED_BYTE, this->mPixelBuffer->data());
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void GWindowMgr::drawCallbackInit() {
  drawFunctors.push_back([this]() {
    glGenTextures(1, &this->pixelBufferTexture);
    glBindTexture(GL_TEXTURE_2D, this->pixelBufferTexture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->Width(), this->Height(),
                    GL_RGB, GL_UNSIGNED_BYTE, this->mPixelBuffer->data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
  });
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

GLFWwindow *GWindowMgr::getGLFWwindow() { return this->pGlfwWindow; }

void GWindowMgr::glInit() {
  glViewport(0.0f, 0.0f, Width(), Height());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, Width(), Height(), 0, 0, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void GWindowMgr::insertKeyCallback(keyCallBack &kb) {
  this->keyCallBacks.push_back(kb);
}

GWindowMgr::GWindowMgr(std::string title, int width, int height)
    : Window(title, width, height), pGlfwWindow(nullptr) {}

GWindowMgr::~GWindowMgr() {
  if (pGlfwWindow) {
    glfwDestroyWindow(pGlfwWindow);
  }
  glfwTerminate();
}

void GWindowMgr::loadShaders() {
  int attempts = 0;
  while (attempts < 3) {
    try {
      mPlainShader.loadShaders("shaders/uiShader.vert",
                               "shaders/uiShader.frag");
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

void GWindowMgr::run() {
  try {
    while (!glfwWindowShouldClose(pGlfwWindow)) {
      if (this->pGlfwWindow != glfwGetCurrentContext()) {
        glfwMakeContextCurrent(this->pGlfwWindow);
      }
      glClear(GL_COLOR_BUFFER_BIT);
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

void GWindowMgr::init() {
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

  this->pGlfwWindow = glfwWindowInit(title, Width(), Height());
  Singleton::get().insertNewWindow(this);
  keyCallbackInit(this->pGlfwWindow, this->keyCallBacks);
  textureInit();
  drawCallbackInit();
  glInit();

#ifdef DEBUG
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
#endif

  loadShaders();
}