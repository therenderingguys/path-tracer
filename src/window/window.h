#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <functional>
#include <string>
#include <vector>

class Window {
protected:
  int width, height;
  std::string title;
  std::vector<std::function<void()>> drawFunctors;
  void draw();

public:
  Window(std::string title, int width, int height);
  virtual void init() = 0;
  virtual void run() = 0;
  int Width() const { return width; }
  int Height() const { return height; }
  std::string Title() const { return title; }
};

#endif // __WINDOW_H__