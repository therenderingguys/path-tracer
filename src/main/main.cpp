// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "window/glfwWindow.h"
#include <GLFW/glfw3.h>
#include <iostream>

int main(int argc, char *argv[]) {
  GWindowMgr gWindow("Test");
  GWindowMgr gWindow2("Test2");
  gWindow.init();
  gWindow2.init();
  keyCallBack aFunc = [](GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
      std::cout << "the letter a was pressed" << std::endl;
    }
  };
  keyCallBack bFunc = [](GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
    if (key == GLFW_KEY_B && action == GLFW_PRESS) {
      std::cout << "the letter b was pressed" << std::endl;
    }
  };
  gWindow.insertKeyCallback(aFunc);
  gWindow2.insertKeyCallback(bFunc);
  gWindow.run();
  gWindow2.run();

  return 0;
}