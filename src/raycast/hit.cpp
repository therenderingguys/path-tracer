#include "hit.h"
#include <limits>

Hit::Hit() : mIsHit(false), mTime(std::numeric_limits<float>::infinity()) {}
