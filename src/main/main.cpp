// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "window/glfwWindow.h"
#include <GLFW/glfw3.h>
#include <iostream>

class TriangleTest {
public:
  TriangleTest() : VBO(0), VAO(0) {}
  void init();
  void draw();
  static float vertices[];

private:
  unsigned int VBO, VAO;
};

float TriangleTest::vertices[] = {
    // positions         // colors
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
    0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top

};

void TriangleTest::draw() {
  // render the triangle
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void TriangleTest::init() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s),
  // and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

int main(int argc, char *argv[]) {
  GLWindow gWindow("Test");
  for (size_t y = 0; y < gWindow.height(); y++) {
    for (size_t x = 0; x < gWindow.width(); x++) {
      gWindow.setPixel(x, y, glm::u8vec3(0, 0, 255));
    }
  }
  //TriangleTest tt;
  //drawCallBack func = [&tt]() { tt.draw(); };
  //gWindow.insertDrawCallback(func);
  gWindow.init();
  // Warning tt.int() has to be called after the window init.
  // may consider adding an int functor vector if we find
  // more things have to be initialized.
  //tt.init();
  gWindow.run();

  return 0;
}