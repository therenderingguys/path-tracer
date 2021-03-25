// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "window/glfwWindow.h"
#include <GLFW/glfw3.h>
#include <iostream>

int main(int argc, char *argv[]) {
  GLWindow gWindow("Test");
  gWindow.init();

  // Right now this has to be done after gWindow init, but if
  // we made the pixel buffer a shared pointer between the window and Rectangle
  // Texture class we could call it before init.
  // https://github.com/therenderingguys/path-tracer/issues/34
  for (size_t y = 0; y < gWindow.height(); y++) {
    for (size_t x = 0; x < gWindow.width(); x++) {
      if (x < gWindow.width() / 2 && y < gWindow.height() / 2) {
        gWindow.setPixel(x, y, glm::u8vec3(127, 64, 255));
      } else if (x < gWindow.width() / 2) {
        gWindow.setPixel(x, y, glm::u8vec3(0, 0, 255));
      } else if (y < gWindow.height() / 2) {
        gWindow.setPixel(x, y, glm::u8vec3(255, 0, 0));
      } else {
        gWindow.setPixel(x, y, glm::u8vec3(0, 255, 0));
      }
    }
  }

  gWindow.run();

  return 0;
}