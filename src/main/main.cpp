// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "fileParsers/model.h"
#include "renderer/pathTracer.h"
#include "scene/scene.h"
#include "window/glfwWindow.h"
#include <GLFW/glfw3.h>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
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

  glm::vec3 gray(0.31, 0.31, 0.31);
  for (int i = 0; i < model.nfaces(); i++) {
    std::vector<int> face = model.face(i);
    if (face.size() == 3) {
      glm::vec3 v1 = model.vert(face[0]);
      glm::vec3 v2 = model.vert(face[1]);
      glm::vec3 v3 = model.vert(face[2]);
      scene.addTriangle(v1, v2, v3, gray);
    }
  }

  GLWindow gWindow("Test");
  gWindow.init();

  PathTracer pathTracer;
  pathTracer.setScene(std::make_unique<Scene>(scene));

  pathTracer.setPixelBuffer(gWindow.getPixelBuffer());
  pathTracer.renderScene();

  gWindow.run();

  return 0;
}