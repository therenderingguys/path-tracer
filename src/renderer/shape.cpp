// Copyright (c) 2021 F. Lotfi &Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "shape.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Shape::Shape(void)
    : vertexAttributes(nullptr), vertsToDraw(0), VAO(0), VBO(0), EBO(0),
      stride(0) {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
}

Shape::~Shape(void) {
  if (vertexAttributes != nullptr) {
    delete[] vertexAttributes;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
  }
}
