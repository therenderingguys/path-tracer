#include "hit.h"
#include <limits>

Hit::Hit()
    : mIsHit(false), mTime(std::numeric_limits<float>::infinity()),
      mColor({0, 0, 0}), mPosition({0, 0, 0}), mTriId(-1) {}
