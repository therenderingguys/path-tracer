/*
 * Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __GLFW_WINDOW_H__
#define __GLFW_WINDOW_H__

#include "renderer/shader.h"
#include "window.h"

struct GLFWwindow;
typedef std::function<void(GLFWwindow *, int, int, int, int)> keyCallBack;

class GWindowMgr : public Window {
private:
  GLFWwindow *pGlfwWindow;
  std::vector<keyCallBack> keyCallBacks;
  Shader mPlainShader;
  void glInit();
  void loadShaders();

public:
  GWindowMgr(std::string title, int width = 640, int height = 480);
  GLFWwindow *getGLFWwindow();
  const std::vector<keyCallBack> &getKeyCallBacks();
  void insertKeyCallback(keyCallBack &kb);
  virtual void init() final;
  virtual void run() final;
  virtual ~GWindowMgr();
};

#endif // __GLFW_WINDOW_H__