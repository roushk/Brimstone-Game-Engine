//***************************************************************************
// Filename: Window.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef WINDOW_H
#define WINDOW_H

struct SDL_Window;
typedef void *SDL_GLContext;

class Window
{
public:
  Window();
  ~Window();

  //OpenGL window and render context
  SDL_Window* gWindow;
  SDL_GLContext* gContext;
  bool creationSuccess;
  int height = 1;
  
  //width/height, width = aspect * height
  float aspect = 1;

};

#endif
