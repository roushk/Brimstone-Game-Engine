/*********************************************************************/
//      File: Mesh.h
//   Authors: Coleman Jonas
//    Course: GAM250A
// Copyright: Copyright © 2018 DigiPen (USA) Corporation.
/*********************************************************************/

#pragma once


struct Mesh {

  struct Face {
    unsigned index1, index2, index3;
    Face(int i=0, int j=0, int k=0)
      : index1(i), index2(j), index3(k) {}
  };

  struct Edge {
    unsigned index1, index2;
    Edge(int i=0, int j=0)
      : index1(i), index2(j) {}
  };


  virtual ~Mesh(void) {}
  virtual int vertexCount(void) = 0;
  virtual const Point* vertexArray(void) = 0;
  virtual Vector dimensions(void) = 0;
  virtual Point center(void) = 0;
  virtual int faceCount(void) = 0;
  virtual const Face* faceArray(void) = 0;
  virtual int edgeCount(void) = 0;
  virtual const Edge* edgeArray(void) = 0;

};
