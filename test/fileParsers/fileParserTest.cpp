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

// Note: I hate this code. it is only here b\c There is no way in
// std::filesystem to know the binary directory, just the working dir. Also
// std::filesystem refuses to make its way to AppleClang. Alternative is to take
// a dependency on Boost, which I refuse to do.
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <Windows.h>
std::string getDirectory() {
  char buffer[MAX_PATH];
  GetModuleFileNameA(nullptr, buffer, MAX_PATH);
  std::string fullpath(buffer);
  size_t beginIdx = fullpath.rfind('\\');
  std::string dirPath = fullpath.substr(0, beginIdx);
  beginIdx = dirPath.rfind('\\');
  dirPath = dirPath.substr(0, beginIdx + 1);
  return dirPath;
}
#elif __APPLE__
#include <mach-o/dyld.h>
std::string getDirectory() {
  uint32_t bufSize = PATH_MAX + 1;
  char dirNameBuffer[bufSize];
  if (_NSGetExecutablePath(dirNameBuffer, &bufSize) == 0) {
    // Buffer size is too small.
    std::string fullpath(dirNameBuffer);
    int beginIdx = fullpath.rfind('/');
    std::string dirPath = fullpath.substr(0, beginIdx + 1);
    return dirPath;
  }
  return "";
}
#elif __linux__
#include <unistd.h>
std::string getDirectory() {
  char abs_path[1024];
  int cnt = readlink("/proc/self/exe", abs_path, 1024);
  // Get the absolute path of the executable program
  if (cnt < 0 || cnt >= 1024) {
    return "";
  }

  // The last '/' is followed by the executable name, remove devel/lib/m100/exe,
  // and only keep the previous part of the path.
  for (int i = cnt; i >= 0; --i) {
    if (abs_path[i] == '/') {
      abs_path[i + 1] = '\0';
      break;
    }
  }

  std::string path(abs_path);

  return path;
}

#endif

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
  std::shared_ptr<PixelBuffer> pb =
      std::make_shared<PixelBuffer>(320, 240, ColorChannels::RGB);
  pathTracer.setPixelBuffer(pb);
  pathTracer.renderScene();
  ImageExport::exportAsPPM(outFileName, pb.get());
}

TEST_CASE("square Obj file Parse test", "[fileParsers][pixelBuffer]") {
  ReadObjToPixelBuffer(getDirectory() + "objFiles/square.obj",
                       "squareTest.ppm");
  REQUIRE(compare_files(getDirectory() + "sln/square.ppm", "squareTest.ppm"));
}

TEST_CASE("cube obj file parser test", "[fileParsers][pixelBuffer]") {
  ReadObjToPixelBuffer(getDirectory() + "objFiles/cube.obj", "cubeTest.ppm");
  REQUIRE(compare_files(getDirectory() + "sln/cube.ppm", "cubeTest.ppm"));
}

TEST_CASE("head obj file parser test", "[fileParsers][pixelBuffer]") {
  ReadObjToPixelBuffer(getDirectory() + "objFiles/african_head.obj",
                       "headTest.ppm");
  REQUIRE(compare_files(getDirectory() + "sln/head.ppm", "headTest.ppm"));
}

TEST_CASE("monkey obj file parser test", "[fileParsers][pixelBuffer]") {
  ReadObjToPixelBuffer(getDirectory() + "objFiles/monkey.obj",
                       "monkeyTest.ppm");
  REQUIRE(compare_files(getDirectory() + "sln/monkey.ppm", "monkeyTest.ppm"));
}

TEST_CASE("diablo obj file parser test", "[fileParsers][pixelBuffer]") {
  ReadObjToPixelBuffer(getDirectory() + "objFiles/diablo3_pose.obj",
                       "diabloTest.ppm");
  REQUIRE(compare_files(getDirectory() + "sln/diablo.ppm", "diabloTest.ppm"));
}

TEST_CASE("Pyramid obj file parser test", "[fileParsers][pixelBuffer]") {
  ReadObjToPixelBuffer(getDirectory() + "objFiles/pyramid.obj",
                       "pyramidTest.ppm");
  REQUIRE(compare_files(getDirectory() + "sln/pyramid.ppm", "pyramidTest.ppm"));
}
