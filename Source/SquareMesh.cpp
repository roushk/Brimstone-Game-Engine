/*********************************************************************/
//      File: SquareMesh.cpp
//   Authors: Coleman Jonas
//    Course: GAM200A
// Copyright: Copyright © 2017 DigiPen (USA) Corporation.
/*********************************************************************/

#pragma once

#include "SquareMesh.h"


const Point SquareMesh::vertices[4]
  = { Point(-1,-1),  // 0
      Point( 1,-1),  // 1
      Point( 1, 1),  // 2
      Point(-1, 1)   // 3
    };

const Point SquareMesh::texture[4]
  = { Point(0,0),    // 0
      Point(1,0),    // 1
      Point(1,1),    // 2
      Point(0,1)     // 3
    };

const Mesh::Face SquareMesh::faces[2]
  = { Face(0,1,2),  Face(0,2,3) };


const Mesh::Edge SquareMesh::edges[4]
  = { Edge(0,1),  Edge(1,2),  Edge(2,3),  Edge(3,0) };


int SquareMesh::textureCount(void)
{
  return 4;
}

const Point* SquareMesh::textureArray(void)
{
  return texture;
}

int SquareMesh::vertexCount(void) {
  return 4;
}

const Point* SquareMesh::vertexArray(void) {
  return vertices;
}

Vector SquareMesh::dimensions(void) {
  return Vector(2, 2);
}

Point SquareMesh::center(void) {
  return Point(0, 0);
}

int SquareMesh::faceCount(void) {
  return 2;
}

const Mesh::Face* SquareMesh::faceArray(void) {
  return faces;
}

int SquareMesh::edgeCount(void) {
  return 4;
}

const Mesh::Edge* SquareMesh::edgeArray(void) {
  return edges;
}