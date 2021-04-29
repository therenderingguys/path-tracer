// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <algorithm>
#include <catch2/catch.hpp>
#include <fstream>
#include <glm/glm.hpp>

#include "fileParsers/imageExporter.h"
#include "fileParsers/model.h"
#include "raycast/camera.h"
#include "renderer/pathTracer.h"
#include "scene/scene.h"

// Note: We really just want to do a file hash here, but there is no built in
// library.
// TODO find a portable hashing library.
bool compare_files(const std::string &filename1, const std::string &filename2) {
  std::ifstream file1(filename1,
                      std::ifstream::ate |
                          std::ifstream::binary); // open file at the end
  std::ifstream file2(filename2,
                      std::ifstream::ate |
                          std::ifstream::binary); // open file at the end
  const std::ifstream::pos_type fileSize = file1.tellg();

  if (fileSize != file2.tellg()) {
    return false; // different file size
  }

  file1.seekg(0); // rewind
  file2.seekg(0); // rewind

  std::istreambuf_iterator<char> begin1(file1);
  std::istreambuf_iterator<char> begin2(file2);

  return std::equal(begin1, std::istreambuf_iterator<char>(),
                    begin2); // Second argument is end-of-range iterator
}

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

void ReadObjToPixelBuffer(std::string filename,
                          std::string outFileName = "test.ppm") {
  Model model(filename.c_str());

  glm::vec3 camOrign({0, 0, 2});
  glm::vec3 camDir({0, 0, -1});
  Camera cam;
  cam.setOrigin(camOrign);
  cam.setDirection(camDir);
  cam.setFOV(90.0f);
  Scene scene(cam);

  for (int i = 0; i < model.nfaces(); i++) {
    std::vector<int> face = model.face(i);
    if (face.size() == 3) {
      glm::vec3 v1 = model.vert(face[0]);
      glm::vec3 v2 = model.vert(face[1]);
      glm::vec3 v3 = model.vert(face[2]);
      scene.addTriangle(v1, v2, v3, getColor(i));
    }
  }

  PathTracer pathTracer;
  pathTracer.setScene(std::make_unique<Scene>(scene));
  PixelBuffer pb(320, 240, ColorChannels::RGB);
  pathTracer.setPixelBuffer(&pb);
  pathTracer.renderScene();
  ImageExport::exportAsPPM(outFileName, &pb);
}

TEST_CASE("square Obj file Parse test", "[fileParsers pixelBuffer]") {

  ReadObjToPixelBuffer("objFiles/square.obj");
  REQUIRE(compare_files("sln/square.ppm", "test.ppm"));
}

TEST_CASE("cube obj file parser test", "[fileParsers pixelBuffer]") {
  ReadObjToPixelBuffer("objFiles/cube.obj");
  REQUIRE(compare_files("sln/cube.ppm", "test.ppm"));
}

TEST_CASE("head obj file parser test", "[fileParsers pixelBuffer]") {
  ReadObjToPixelBuffer("objFiles/african_head.obj");
  REQUIRE(compare_files("sln/head.ppm", "test.ppm"));
}

TEST_CASE("monkey obj file parser test", "[fileParsers pixelBuffer]") {
  ReadObjToPixelBuffer("objFiles/monkey.obj");
  REQUIRE(compare_files("sln/monkey.ppm", "test.ppm"));
}

TEST_CASE("diablo obj file parser test", "[fileParsers pixelBuffer]") {
  ReadObjToPixelBuffer("objFiles/diablo3_pose.obj");
  REQUIRE(compare_files("sln/diablo.ppm", "test.ppm"));
}

TEST_CASE("Pyramid obj file parser test", "[fileParsers pixelBuffer]") {
  ReadObjToPixelBuffer("objFiles/pyramid.obj");
  REQUIRE(compare_files("sln/pyramid.ppm", "test.ppm"));
}