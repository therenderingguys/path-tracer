/*
 * Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <functional>
#include <string>
#include <vector>

typedef std::function<void()> drawCallBack;

class Window {
protected:
  int width, height;
  std::string title;
  std::vector<drawCallBack> drawFunctors;
  void draw();

public:
  Window(std::string title, int width, int height);
  virtual void init() = 0;
  virtual void run() = 0;
  int Width() const { return width; }
  int Height() const { return height; }
  std::string Title() const { return title; }
  void insertDrawCallback(drawCallBack &db);
  const std::vector<drawCallBack> &getDrawCallBacks();
};

#endif // __WINDOW_H__