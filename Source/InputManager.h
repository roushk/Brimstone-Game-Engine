//***************************************************************************
// Filename: InputManager.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H


#include "System.h"
#include "Engine.h"
#include <detail/type_vec2.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>




class InputManager: public System
{
public:
  InputManager();
  ~InputManager() override;

  void Update(float dt) override;
  static const int type = stInputManager;

  
  //std::queue<InputEvent> inputEvents;

  glm::vec2 screenSize;

  glm::vec2 mouseScreenCoords;
  glm::vec2 mouseWorldCoords;

  glm::mat4 scaleToWorld = glm::scale(glm::vec3(20.0f / 800.0f, 20.0f / 600.0f, 1));
  
  float aspect = screenSize.x / screenSize.y;

  bool held = false;


  glm::vec2 mouseSelectStartPos;
  glm::vec2 mouseSelectEndPos;
  std::vector<GameObject*> selected;
  Map* map;
  AStarPather pather;

};

#endif
