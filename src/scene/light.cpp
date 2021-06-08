#include "light.h"


Light::Light(glm::vec3 direction) : mDirection(direction) {}
float Light::Intensity(const Triangle &triangle) const{
    return glm::dot(triangle.normal(),mDirection);
}

glm::vec3 Light::GetColor(const Triangle &triangle) const {
    float intensity = Intensity(triangle);
    return triangle.color() * intensity;
}