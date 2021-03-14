// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "window.h"

Window::Window(std::string title, int w, int h)
    : width(w), height(h), title(title) {}

void Window::draw() {
  for (const std::function<void()> &df : drawFunctors) {
    df();
  }
}

void Window::insertDrawCallback(drawCallBack &db) {
  this->drawFunctors.push_back(db);
}

const std::vector<drawCallBack> &Window::getDrawCallBacks() {
  return drawFunctors;
}