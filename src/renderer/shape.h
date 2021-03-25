/*
 * Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include <glm/glm.hpp>
#include <glm/gtc/type_precision.hpp>

class Shape {
public:
  Shape(void);
  virtual ~Shape(void);
  float *getAttributes() { return vertexAttributes; }
  int getVertsToDraw() { return vertsToDraw; }
  int getStride() { return stride; }

protected:
  float *vertexAttributes;
  int vertsToDraw;
  int stride;
  unsigned int VBO, VAO, EBO;
};

#endif //__SHAPE_HPP__
