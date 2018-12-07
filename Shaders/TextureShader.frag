//***************************************************************************
// Filename: TextureShader.frag
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************
#version 430 core

uniform vec4 faceColor;
uniform sampler2D textureSampler;

out vec4 color;

in vec2 uvTexCoords;

void main()
{
  vec4 texColor = texture(textureSampler, uvTexCoords);
  //if(texColor.a < 0.01)
  //  texColor.a = 0;
  
  color = vec4(texColor.rgb + faceColor.rgb, texColor.a * faceColor.a);
  //this kind of fixed the transparency issue
  //the real fix is to render all alpha > 0.9 first 
  //then render all transparent objects on top of them but this will work
  //for this situation of the cursor transparency
  //ordering IS importent in this case
  //possibly use https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glAlphaFunc.xml
  if(texColor.rgb == vec3(0,0,0))
  {
    color = faceColor;
  }
  else if(texColor.a < 0.01f || faceColor.a < 0.01f)
    discard;  //https://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/discard.php
}
