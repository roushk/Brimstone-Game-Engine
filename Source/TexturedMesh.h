//***************************************************************************
// Filename: TexturedMesh.cpp
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#pragma once
#include "Mesh.h"


struct TexturedMesh : Mesh {
  virtual const Point* texcoordArray(void) = 0;
};
