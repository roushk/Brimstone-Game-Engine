//***************************************************************************
// Filename: FpsLimiter.cpp
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************
#include "pch.h"


Window::Window()
{
  //initialise openGL window and context using SDL
  gWindow = NULL;
  gContext = new SDL_GLContext;

  //Initialization flag
  creationSuccess = false;

  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "SDL could not initialize the window! SDL_Error: %s\n" << SDL_GetError() << std::endl;
    creationSuccess = false;
    return;
  }
  else
  {
    std::string programName = "2DEngine";
    int screenWidth = 800;
    int screenHeight = 600;

    //creates window and sets window flags
    gWindow = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (gWindow == NULL)
    {
      std::cout << "Window could not be created! SDL_Error: %s\n" << SDL_GetError() << std::endl;

      creationSuccess = false;
      return;
    }

    // Load and set the window icon
    /*SDL_Surface * icon = SDL_LoadBMP("icon.bmp");
    if (icon == NULL)
    {
      std::cout << "Window Icon could not be opened. SDL_Error: %s\n" << SDL_GetError() << std::endl;
    }
    else
    {
      SDL_SetWindowIcon(gWindow, icon);
    }*/

    *gContext = SDL_GL_CreateContext(gWindow);

    //~~~~~~~~~~~~~~~~~~~~~//
    //SET OPENGL ATTRIBUTES//
    //~~~~~~~~~~~~~~~~~~~~~//

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    //sets OpenGL context version of the SDL window
    //set to OpenGL 4.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    //enableing double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  //may need to be 16 or 32
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    //~~~~~~~~~~~~~~~~~~//
    //INITIALIZEING GLEW//
    //~~~~~~~~~~~~~~~~~~//

    //sets us to use newest versions of functions
    glewExperimental = GL_TRUE;

    glewInit();

    //sets refresh rate to the monitors refresh rate
    SDL_GL_SetSwapInterval(1);
  }
}

Window::~Window()
{
  //Destroy window
  SDL_DestroyWindow(gWindow);  

  //destroy context
  SDL_GL_DeleteContext(gContext);
  
  //Quit SDL
  SDL_Quit();

}