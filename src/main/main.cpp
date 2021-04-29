// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "renderer/pathTracer.h"
#include "scene/scene.h"
#include "window/glfwWindow.h"
#include "fileParsers/model.h"
#include <GLFW/glfw3.h>
#include <iostream>

glm::vec3 getColor(int index) {
  glm::vec3 red(1, 0.701, 0.729);
  glm::vec3 green(0.729, 1, 0.788);
  glm::vec3 blue(0.729, 1, 1);
  glm::vec3 purple(0.945, 0.835, 0.976);
  glm::vec3 gray(0.31, 0.31, 0.31);
  if (index % 2 == 0) {
    return red;
  }
  if (index % 3 == 0) {
    return green;
  }
  if (index % 5 == 0) {
    return blue;
  }
  if (index % 7 == 0) {
    return purple;
  }
  return gray;
}

int main(int argc, char *argv[]) {
  if( argc != 2) {
        std::cout << "usage ./exec <wavefront_obj_file>.obj" << std::endl;
        return 0;
  }
  Model model(argv[1]);

  glm::vec3 camOrign({0, 0, 2});
  glm::vec3 camDir({0, 0, -1});
  Camera cam;
  cam.setOrigin(camOrign);
  cam.setDirection(camDir);
  cam.setFOV(90.0f);
  Scene scene(cam);

  //glm::vec3 gray(0.31, 0.31, 0.31);
  for (int i = 0; i < model.nfaces(); i++) {
    std::vector<int> face = model.face(i);
    if (face.size() == 3) {
      glm::vec3 v1 = model.vert(face[0]);
      glm::vec3 v2 = model.vert(face[1]);
      glm::vec3 v3 = model.vert(face[2]);
      scene.addTriangle(v1, v2, v3, getColor(i));
    }
  }

  GLWindow gWindow("Test");
  gWindow.init();

  PathTracer pathTracer;
  pathTracer.setScene(std::make_unique<Scene>(scene));

  PixelBuffer *pb = gWindow.getPixelBuffer();
  pathTracer.setPixelBuffer(pb);
  pathTracer.renderScene();
  //gWindow.insertDrawCallback(pathTracer.getDrawCallBack());

  gWindow.run();

  return 0;
}