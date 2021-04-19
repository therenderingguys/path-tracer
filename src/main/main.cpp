// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "renderer/pathTracer.h"
#include "scene/scene.h"
#include "window/glfwWindow.h"
#include <GLFW/glfw3.h>
#include <iostream>

int main(int argc, char *argv[]) {
  glm::vec3 camOrign({0, 0, 2});
  glm::vec3 camDir({0, 0, -1});
  Camera cam;
  cam.setOrigin(camOrign);
  cam.setDirection(camDir);
  cam.setFOV(90.0f);
  Scene scene(cam);

  glm::vec3 red(1, 0.701, 0.729);
  glm::vec3 green(0.729, 1, 0.788);
  glm::vec3 blue(0.729, 1, 1);
  glm::vec3 purple(0.945, 0.835, 0.976);

  float z = -1;
  glm::vec3 ulp(-1, 1, z);
  glm::vec3 urp(1, 1, z);
  glm::vec3 brp(1, -1, z);
  glm::vec3 blp(-1, -1, z);
  glm::vec3 cp(0, 0, z);

  scene.addTriangle(ulp, urp, cp, red);
  scene.addTriangle(urp, brp, cp, green);
  scene.addTriangle(brp, blp, cp, blue);
  scene.addTriangle(blp, ulp, cp, purple);

  glm::vec3 pCenterUp   (0,  1, -0.5);
  glm::vec3 pRightBottom(2,  0, -1.5);
  glm::vec3 pLeftBottom(-2,  0, -1.5);
  scene.addTriangle(pCenterUp, pRightBottom, pLeftBottom, green);

  GLWindow gWindow("Test");
  gWindow.init();

  PathTracer pathTracer(gWindow.width(), gWindow.height());
  pathTracer.setScene(scene);

  PixelBuffer *pb = gWindow.getPixelBuffer();
  pathTracer.setPixelBuffer(pb);

  gWindow.insertDrawCallback(pathTracer.getDrawCallBack());

  gWindow.run();

  return 0;
}