/*********************************************************************/
//      File: SquareMesh.h
//   Authors: Coleman Jonas
//    Course: GAM250A
// Copyright: Copyright © 2018 DigiPen (USA) Corporation.
/*********************************************************************/

#include "Mesh.h"


class SquareMesh : public Mesh {
  public:
    int vertexCount(void);
    const Point* vertexArray(void);
    Vector dimensions(void);
    Point center(void);
    int faceCount(void);
    const Face* faceArray(void);
    int edgeCount(void);
    const Edge* edgeArray(void);

    int textureCount(void);
    const Point* textureArray(void);

  private:
    static const Point vertices[4];
    static const Face faces[2];
    static const Edge edges[4];
    static const Point texture[4];

};


