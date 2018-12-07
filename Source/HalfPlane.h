// HalfPlane.h
// -- utilities for half-planes
// cs200 11/17

#ifndef CS200_HALFPLANE_H
#define CS200_HALFPLANE_H
#include <detail/type_vec4.hpp>


struct HalfPlane : glm::vec4 {
  HalfPlane(float X=0, float Y=0, float W=0) : glm::vec4(X,Y,W,1) { }
  HalfPlane(const glm::vec3& n, const glm::vec3& C);
  HalfPlane(const glm::vec3& A, const glm::vec3& B, const glm::vec3& P);
};


struct Interval {
  float bgn, end;
  Interval(float a=0, float b=1) : bgn(a), end(b) { }
  bool isEmpty(void) const { return bgn > end; }
};


float dot(const HalfPlane& h, const glm::vec3& Q);
Interval intersect(const HalfPlane& h, const glm::vec3& P, const glm::vec3& Q);


#endif

