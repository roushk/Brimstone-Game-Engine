//***************************************************************************
// Filename: TextureShader.vert
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************
#version 430 core

//uniform mat4  modelView;

layout (std140, binding = 0) uniform CameraData
{
  mat4  modelTransform;
  mat4  worldToNDC;
  mat4  camera;
};
layout(location = 0) in vec3  vertexPosition;
layout(location = 1) in vec2  texCoords;

out vec2 uvTexCoords;

void main()
{
  uvTexCoords = texCoords; 
  //worldToNDC * modelTransform * modelView *
  vec4 pos = worldToNDC * camera * modelTransform * vec4(vertexPosition, 1);
  gl_Position = vec4(pos.xyz,1);
}
