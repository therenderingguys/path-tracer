#include "camera.h"

Camera::Camera(glm::vec3 o, glm::vec3 d) : mOrigin(o){
    this->mDirection = glm::normalize(d);
}

Ray Camera::generate_ray(float x, float y) {

    glm::vec3 dir(x - mOrigin.x, y - mOrigin.y, 0);
    
    return Ray(this->mOrigin, dir);
}