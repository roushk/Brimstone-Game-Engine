//***************************************************************************
// Filename: ShaderLoader.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H
#include <glew.h>
#include "FileLoad.h"
#include <string>
#include <vector>
#include <iostream>

//Takes vertex and fragment shader filenames and returns programID of both linked
inline GLuint LoadShaders(const std::string& vertexFilename, const std::string& fragmentFilename)
{
  GLint success = GL_FALSE;

  /*******************************************************/
  //Vertex Shader
  GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);
  std::string vertFile = GetFile(vertexFilename);
  GLchar const* vertFileGLchar = vertFile.c_str();   //cast because glShaderSource is pedantic

  glShaderSource(vertShaderID, 1, &vertFileGLchar, NULL);
  glCompileShader(vertShaderID);

  int length;
  //check shader
  glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
  glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &length);
  if (length > 0) {
    std::vector<char> ErrorMessage(length + 1);
    glGetShaderInfoLog(vertShaderID, length, NULL, &ErrorMessage[0]);
    printf("%s\n", &ErrorMessage[0]);
  }

  /*******************************************************/
  //Fragment Shader
  GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  std::string fragFile = GetFile(fragmentFilename);
  GLchar const* fragFileGLchar = fragFile.c_str(); //cast because glShaderSource is pedantic

  glShaderSource(fragShaderID, 1, &fragFileGLchar, NULL);
  glCompileShader(fragShaderID);

  //check shader
  glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &success);
  glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &length);
  if (length > 0) {
    std::vector<char> ErrorMessage(length + 1);
    glGetShaderInfoLog(fragShaderID, length, NULL, &ErrorMessage[0]);
    printf("%s\n", &ErrorMessage[0]);
  }

  //Link Program
  printf("Linking Shaders into program\n");
  GLuint programID = glCreateProgram();
  glAttachShader(programID, vertShaderID);
  glAttachShader(programID, fragShaderID);
  glLinkProgram(programID);



  //check for errors
  GLenum error;
  while ((error = glGetError()) != GL_NO_ERROR)
  {
    std::cout << "ShaderLoader: There was an OPENGL Error: " << error << std::endl;
  }

  glUseProgram(programID);
  glDeleteShader(vertShaderID);
  glDeleteShader(fragShaderID);

  return programID;
}

#endif