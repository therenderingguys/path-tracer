/*
 * Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __GLFW_WINDOW_H__
#define __GLFW_WINDOW_H__

#include "renderer/rectangle.h"
#include "renderer/shader.h"
#include "window.h"

struct RectangleLayout {
  int Rows;
  int Cols;
};

struct ShaderProperties {
  int uiPositionHandle;
  int uiTextureHandle;
  int uiTextureSampler;
  ShaderProperties();
  void init(Shader &uiShader);
};

struct GLFWwindow;
typedef std::function<void(GLFWwindow *, int, int, int, int)> keyCallBack;

class GLWindow : public Window {
private:
  GLFWwindow *pGlfwWindow;
  std::vector<keyCallBack> keyCallBacks;
  std::vector<std::unique_ptr<Rectangle>> mRectangles;
  Shader mPlainShader;
  ShaderProperties mShaderProperties;
  RectangleLayout mLayout;
  void glInit();
  void loadShaders();
#if DEBUG
  void queryGPU();
#endif

public:
  GLWindow(std::string title, int width = 640, int height = 480,
           RectangleLayout layout = {1, 1});
  GLFWwindow *getGLFWwindow();
  const std::vector<keyCallBack> &getKeyCallBacks();
  void insertKeyCallback(keyCallBack &kb);
  virtual void init() final;
  virtual void run() final;
  virtual ~GLWindow();
  std::shared_ptr<PixelBuffer> getPixelBuffer();
  void setPixel(size_t x, size_t y, uint8_t color);
  void setPixel(size_t x, size_t y, glm::u8vec4 color);
  void setPixel(size_t x, size_t y, glm::u8vec3 color);
  void windowResized(int width, int height);
};

#endif // __GLFW_WINDOW_H__