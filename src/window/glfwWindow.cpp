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
  glViewport(0.0f, 0.0f, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, height, 0, 0, 1);
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
  // exit(EXIT_SUCCESS);
}

void GWindowMgr::run() {
  while (!glfwWindowShouldClose(pGlfwWindow)) {
    if (this->pGlfwWindow != glfwGetCurrentContext()) {
      glfwMakeContextCurrent(this->pGlfwWindow);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    draw();
    // Swap buffers
    glfwSwapBuffers(pGlfwWindow);

    // this has to run on the main thread
    glfwPollEvents();
  }
}

void GWindowMgr::init() {
  if (glfwInit() != GL_TRUE) {
    std::cerr << "Failed to initialize GLFW!" << std::endl;
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->pGlfwWindow = glfwWindowInit(title, width, height);
  Singleton::get().insertNewWindow(this);
  keyCallbackInit(this->pGlfwWindow, this->keyCallBacks);
  glInit();
}