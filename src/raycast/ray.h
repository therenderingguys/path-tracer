
#ifndef __RAY_H__
#define __RAY_H__

#include <glm/glm.hpp>


class Ray {
    glm::vec3 mOrigin, mDirection;
    public:
        Ray();
        Ray(glm::vec3 &o, glm::vec3 &d);
        glm::vec3 point_at_dt(float dt);
        const glm::vec3& direction() const { return mDirection; }
        const glm::vec3& origin() const { return mOrigin; }
};

#endif // __RAY_H__
