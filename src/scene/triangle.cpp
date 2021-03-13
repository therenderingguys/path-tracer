// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "triangle.h"

Triangle::Triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 color,
                   size_t id)
    : mP0(p0), mP1(p1), mP2(p2), mColor(color), mId(id) {
  this->mNormal = glm::normalize(glm::cross(mP1 - mP0, mP2 - mP0));
}

Triangle::Triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2)
    : Triangle(p0, p1, p2, glm::vec3(0.78, 0.15, 0.7)) {}

Triangle::Triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 color)
    : mP0(p0), mP1(p1), mP2(p2), mColor(color), mId(-1) {
  this->mNormal = glm::normalize(glm::cross(mP1 - mP0, mP2 - mP0));
}

// Möller–Trumbore intersection algorithm
// https://w.wiki/y6d
Hit Triangle::getRayIntersection(const Ray &ray) const {

  // Hit is initalized to false
  Hit hit;

  // find vectors for two edges sharing p0
  glm::vec3 e1 = mP1 - mP0;
  glm::vec3 e2 = mP2 - mP0;

  // calculating determinant - also used to calculate u parameter
  glm::vec3 h = glm::cross(ray.direction(), e2);

  // check if determinate is near 0;
  float det = glm::dot(e1, h);

  if (det > -EPSILON && det < EPSILON) {
    return hit;
  }

  // used to normalize in relation to det
  float invDet = 1.0f / det;

  // calculate distance from p0 to ray origin
  glm::vec3 p0ToRayDist = ray.origin() - mP0;
  float u = glm::dot(p0ToRayDist, h) * invDet;
  // check if the intersection lies outside the bounds
  // of the triangle
  if (u < 0.0f || u > 1.0f) {
    return hit;
  }

  // get the perpendicular vector to both p0->r and p0->p1
  glm::vec3 q = glm::cross(p0ToRayDist, e1);
  float v = glm::dot(ray.direction(), q) * invDet;

  if (v < 0.0 || (u + v) > 1.0f) {
    return hit;
  }

  float t = glm::dot(e2, q) * invDet;

  if (t > EPSILON) {
    hit.isHit() = true;
    hit.setPosition(ray.point_at_dt(t));
    hit.setColor(this->mColor);
    hit.setTime(t);
    hit.setTriId(mId);
  }

  return hit;
}