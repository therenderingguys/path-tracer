// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "hit.h"
#include <limits>

Hit::Hit()
    : mIsHit(false), mTime(std::numeric_limits<float>::infinity()),
      mColor({0, 0, 0}), mPosition({0, 0, 0}), mTriId(-1) {}
