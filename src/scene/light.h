/*
 * Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <glm/glm.hpp>

#include "triangle.h"

class Light {
private:
  glm::vec3 mDirection;

public:
  Light(glm::vec3 direction);
  float Intensity(const Triangle &triangle) const;
  glm::vec3 Direction() const { return mDirection; }
  glm::vec3 GetColor(const Triangle &triangle) const;
};

#endif // __LIGHT_H__