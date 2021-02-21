#include "window.h"

Window::Window(std::string title, int w, int h)
    : width(w), height(h), title(title) {}

void Window::draw() {
  for (const std::function<void()> &df : drawFunctors) {
    df();
  }
}