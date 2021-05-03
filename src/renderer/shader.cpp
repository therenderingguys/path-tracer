// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "shader.h"
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <unordered_map>

std::unordered_map<int, std::string> mapShaderType = {

    {GL_VERTEX_SHADER, "GL_VERTEX_SHADER"},
    {GL_FRAGMENT_SHADER, "GL_FRAGMENT_SHADER"}};

using std::ifstream;

//-----------------------------------------------------------------------------

Shader::Shader(void) : program(0) {}

//-----------------------------------------------------------------------------

Shader::Shader(const std::string &vertexShaderPath,
               const std::string &fragmentShaderPath)
    : program(0) {
  loadShaders(vertexShaderPath, fragmentShaderPath);
}

//-----------------------------------------------------------------------------

Shader::~Shader(void) {
  if (program != 0) {
    glDeleteProgram(program);
    program = 0;
  }
}

//-----------------------------------------------------------------------------

int Shader::getAttribLocation(const std::string &name) const {
  if (program == 0) {
    return -1;
  }

  glUseProgram(program);
  int attribute = glGetAttribLocation(program, name.c_str());
  glUseProgram(0); // Todo change back to active program

  return attribute;
}

//-----------------------------------------------------------------------------

int Shader::getUniformLocation(const std::string &name) const {
  if (program == 0) {
    return -1;
  }

  glUseProgram(program);
  int uniform = glGetUniformLocation(program, name.c_str());
  glUseProgram(0); // Todo change back to active program

  return uniform;
}

//-----------------------------------------------------------------------------

void Shader::loadShaders(const std::string &vsPath, const std::string &fsPath) {
  if (program != 0) {
    glDeleteProgram(program);
    program = 0;
  }

  ifstream vs(vsPath);
  if (!vs.good()) {
    throw std::runtime_error("Failed to open vertex shader");
  }

  ifstream fs(fsPath);
  if (!fs.good()) {
    vs.close();
    throw std::runtime_error("Failed to open fragment shader");
  }

  vs.seekg(0, std::ios::end);
  std::streamoff size = vs.tellg();
  vs.seekg(0, std::ios::beg);

  char *vertexSource = new char[static_cast<unsigned int>(size)];
  memset(vertexSource, 0, size_t(size));
  vs.read(vertexSource, size);

  if (vs.bad()) {
    throw std::runtime_error("Error reading vertex shader source");
  }

  fs.seekg(0, std::ios::end);
  size = fs.tellg();
  fs.seekg(0, std::ios::beg);

  char *fragmentSource = new char[static_cast<unsigned int>(size)];
  memset(fragmentSource, 0, size_t(size));
  fs.read(fragmentSource, size);

  if (fs.bad()) {
    throw std::runtime_error("Error reading fragment shader source");
  }
  int vShaderId = createShader(GL_VERTEX_SHADER, vertexSource);
  int fShaderId = createShader(GL_FRAGMENT_SHADER, fragmentSource);

  program = createProgram(vShaderId, fShaderId);
}

//-----------------------------------------------------------------------------

GLuint Shader::createShader(int shaderType, const char *source) {
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  GLint compileStatus;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
  if (compileStatus == GL_FALSE) {
    GLint infoLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
    char *log = new char[infoLength + 1];
    glGetShaderInfoLog(shader, infoLength, NULL, log);

    std::string error = std::string(log);
    delete[] log;
    std::cerr << "Error creating: " << mapShaderType[shaderType] << " shader."
              << std::endl;
    throw std::runtime_error(error.c_str());
  }

  return shader;
}

//-----------------------------------------------------------------------------

GLuint Shader::createProgram(int vShader, int fShader) {
  GLuint program = glCreateProgram();
  glAttachShader(program, vShader);
  glAttachShader(program, fShader);
  glLinkProgram(program);

  GLint linkStatus;
  glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
  if (linkStatus == GL_FALSE) {
    GLint infoLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
    char *log = new char[infoLength + 1];
    glGetProgramInfoLog(program, infoLength, NULL, log);

    std::string error = std::string(log);
    delete[] log;

    throw std::runtime_error(error.c_str());
  }
  glDeleteShader(vShader);
  glDeleteShader(fShader);
  return program;
}

//-----------------------------------------------------------------------------