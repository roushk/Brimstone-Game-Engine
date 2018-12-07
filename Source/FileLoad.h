//***************************************************************************
// Filename: Stub.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef FILE_LOAD_H
#define FILE_LOAD_H
#include <string>
#include <fstream>

inline std::string GetFile(std::string filename)
{
  std::ifstream file(filename); 
  if (file.is_open() == false)
    throw (std::string("Cannot Load File ") + filename);
  std::string data;
  file.seekg(0, std::ios::end);
  data.reserve(static_cast<const unsigned>(file.tellg()));  //allocated all memory for it
  file.seekg(0, std::ios::beg);
  data.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  file.close();
  return data;
}

#endif