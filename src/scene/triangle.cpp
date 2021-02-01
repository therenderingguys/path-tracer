#include "triangle.h"

Triangle::Triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2) 
	: mP0(p0), mP1(p1), mP2(p2) 
{
  this->mNormal = glm::normalize(glm::cross(mP1 - mP0, mP2 - mP0));
}
