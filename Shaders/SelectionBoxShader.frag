//***************************************************************************
// Filename: TextureShader.frag
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************
#version 430 core

uniform vec4 lineColor;

out vec4 color;

in vec2 uvTexCoords;

void main()
{
  color = lineColor;
}
