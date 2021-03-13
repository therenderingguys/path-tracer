// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "ray.h"

Ray::Ray(glm::vec3 &o, glm::vec3 &d)
    : mOrigin(o), mDirection(glm::normalize(d)) {}
Ray::Ray() : mOrigin(glm::vec3(0.0f)), mDirection(glm::vec3(0.0f)) {}

glm::vec3 Ray::point_at_dt(float dt) const { return mOrigin + dt * mDirection; }