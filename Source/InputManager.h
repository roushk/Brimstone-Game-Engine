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
#include "InputEvent.h"
#include <functional>


class InputManager: public System
{
public:
  InputManager();
  ~InputManager() override;

  void Update(float dt) override;
  static const SystemTypes type = SystemTypes::InputManager;

  //SDL_SCANCODE_KEY to current status of the key
  //saves the key so to check the input only need to access the SDL_SCANCODE
  //of the key into the map and check the value
  //ranged 4 to 284
  std::map<int, InputButtonEvent> inputMapKeyboard;


  //value 1 = mouse button left
  //value 2 = mouse button right
  //value 3 = mouse button middle
  std::map<int, InputMouseButtonEvent> inputMapMouse;

  //map of keycodes to a vector of events which are a pair of button event type to function
  std::map<int, std::vector<std::pair<InputButtonEvent, std::function<void(float)>>>> inputKeyboardEvents;
  void AddKeyboardInputEvent(int SDLScancode, InputButtonEvent eventType, std::function<void(float)> func);

  std::map<int, std::vector<std::pair<InputMouseButtonEvent, std::function<void(float)>>>> inputMouseEvents;
  void AddMouseInputEvent(int SDLScancode, InputMouseButtonEvent eventType, std::function<void(float)> func);

  glm::vec2 screenSize;
  glm::vec2 mouseNDC;
  glm::vec2 mouseScreenCoords;
  glm::vec2 mouseWorldCoords;

  glm::mat4 scaleToWorld = glm::scale(glm::vec3(10.0f / 800.0f, 10.0f / 600.0f, 1));
  
  float aspect = screenSize.x / screenSize.y;

  bool held = false;


  glm::vec2 mouseSelectStartPos;
  glm::vec2 mouseSelectEndPos;
  std::vector<GameObject*> selected;
  Map* map;
  AStarPather pather;
  float cameraAccelSpeed = 10.0f;

};

#endif
