// HalfPlane.cpp
// -- utilities for half-planes
// cs200 11/17
// Coleman Jonas
#include "pch.h"

#include "HalfPlane.h"


 /*| (constructor) creates the half{plane with outwardly pointing sur-
face normal vector ~n and whose boundary contains the point C.*/
HalfPlane::HalfPlane(const glm::vec3& n, const glm::vec3& C)
{
  x = n.x;
  y = n.y;
  w = -((x * C.x) + (y * C.y));
}

/* | (constructor) creates the half-plane h whose boundary contains
the points A;B, and whose interior contains the point P. Note that h should be
such that h * A = 0, h * B = 0, and h * P < 0. you are to assume that the points
A,B, P are non-colinear.*/
HalfPlane::HalfPlane(const glm::vec3& A, const glm::vec3& B, const glm::vec3& P)
{
  y = -(B.x - A.x);
  x = (B.y - A.y);
  w = -((x * A.x) + (y * A.y));

  if(dot(*this, P) > 0)
  {
    x = -x;
    y = -y;
    w = -w;
  }
}

/* | computes the dot product of the half{plane h, which specied by its ho-
mogeneous coordinate representation, and the point Q. In particular, the function
returns a positive value if Q is outside of h, a negative value if Q is interior to h,
and zero if Q is on the boundary of h.*/
float dot(const HalfPlane& h, const glm::vec3& Q)
{
  return h.x * Q.x + h.y * Q.y + h.w;
}

/*| computes the intersection interval I = [a; b] that corresponds to
the intersection of the half{plane h and the line segment PQ with endpoints P;Q.
If the intersection is empty, then I = ;; i.e., a > b. If the I is not empty, then the
intersection of h and PQ is the line segment P0Q0, where P0 = P + a(Q 􀀀 P) and
Q0 = P + b(Q 􀀀 P).*/
Interval intersect(const HalfPlane& h, const glm::vec3& P, const glm::vec3& Q)
{
  float tPQ;
  bool Ph = true;
  bool Qh = true;
  Interval interval;

  if(dot(h,P) < 0)  //P e h
  {
    Ph = true;
  }
  else if( dot(h, P) > 0) //P /e h
  {
    Ph = false;
  }
  if(dot(h,Q) < 0)  //Q e h
  {
    Qh = true;
  }
  else if( dot(h, Q) > 0) //Q /e H
  {
    Qh = false;
  }

  tPQ = dot(h,P) / ( dot(h,P) - dot(h,Q) );

  if(Ph == false && Qh == true)
  {
    interval.bgn = tPQ;
    interval.end = 1;
  }
  else if(Ph == true && Qh == false)
  {
    interval.bgn = 0;
    interval.end = tPQ;
  }
  else if(Ph == true && Qh == true)
  {
    interval.bgn = 0;
    interval.end = 1;
  }
  else if(Ph == false && Qh == false)
  {
    interval.bgn = 1;
    interval.end = 0;
  }

  return interval;
}

