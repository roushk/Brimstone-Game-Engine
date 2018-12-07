//***************************************************************************
// Filename: Texture.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef TEXTURE_H
#define TEXTURE_H
#include <glew.h>
#include <string>
#include <SOIL.h>
#include  <fstream>

class Texture
{
public:
  GLuint GetTexture() const { return textureID; };

  ~Texture() { glDeleteTextures(1, &textureID); };
  Texture(std::string& filename, bool DDS = true)
  {
    ID = nextTexID++;
    //New way inverts Y axis
    unsigned FileLoadFlags = 0;
    if(DDS)
    {
      FileLoadFlags = SOIL_FLAG_DDS_LOAD_DIRECT;
    }
    else
    {
      FileLoadFlags = SOIL_FLAG_INVERT_Y;
    }

    textureID = SOIL_load_OGL_texture //generates new textureID in openGL
    (
      filename.c_str(),
      SOIL_LOAD_RGBA,
      SOIL_CREATE_NEW_ID,
      FileLoadFlags
    );

    if (textureID == NULL)
    {
      printf("SOIL loading error: '%s', File'%s'\n", SOIL_last_result(), filename.c_str());
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //glGenerateMipmap(GL_TEXTURE_2D);


    if (textureID == NULL)
    {
      printf("SOIL loading error: '%s', File'%s'\n", SOIL_last_result(), filename.c_str());
    }

    if (textureID == -1) {
      throw("Texture ID -1");
    }
  }


  unsigned ID = 0;
  
private:
  GLuint textureID;
  static unsigned nextTexID;

};

#endif