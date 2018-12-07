// PointContainment.h
// -- point containment functions
// cs200 11/17

#ifndef CS200_POINTCONTAINMENT_H
#define CS200_POINTCONTAINMENT_H

#include <detail/type_vec3.hpp>


bool pointInTriangle(const glm::vec3& P, const glm::vec3& A,
                     const glm::vec3& B, const glm::vec3& C);

#endif

