/*********************************************************************/
//      File: SquareTexturedMesh.cpp
//   Authors: Coleman Jonas
//    Course: GAM200A
// Copyright: Copyright © 2017 DigiPen (USA) Corporation.
/*********************************************************************/
#include "SquareTexturedMesh.h"


const Point SquareTexturedMesh::vertices[4]
  = { Point(-1,-1),  // 0
      Point(1,-1),   // 1
      Point(1,1),    // 2
      Point(-1,1)    // 3
    };


const Point SquareTexturedMesh::texcoords[4]
  = { Point(0,0), // 0
      Point(1,0), // 1
      Point(1,1), // 2
      Point(0,1)  // 3
    };


const Mesh::Face SquareTexturedMesh::faces[2]
  = { Face(0,1,2),  Face(0,2,3) };


const Mesh::Edge SquareTexturedMesh::edges[4]
  = { Edge(0,1),  Edge(1,2),  Edge(2,3),  Edge(3,0) };

