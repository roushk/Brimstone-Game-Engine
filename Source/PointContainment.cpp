// PointContainment.cpp
// -- test of point containment functions
// cs200 11/17
// Coleman Jonas
#include "pch.h"

#include "PointContainment.h"
#include "HalfPlane.h"
#include <iostream>
#include <detail/type_vec3.hpp>


/* | returns true if the point P is inside of the triangle with
vertices A, B, and C. It returns false if P is outside of the triangle. It is assumed
that the points A;B;C are non{colinear.*/
bool pointInTriangle(const glm::vec3& P, const glm::vec3& A,
                     const glm::vec3& B, const glm::vec3& C)
{
  HalfPlane tri1(A,B,C);
  HalfPlane tri2(B,C,A);
  HalfPlane tri3(C,A,B);

  return (dot(tri1, P) <= 0) && (dot(tri2, P) <= 0) && (dot(tri3, P) <= 0);
}
