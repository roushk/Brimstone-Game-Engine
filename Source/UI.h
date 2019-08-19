#pragma once

#include "GameObject.h"

class UIElement : GameObject
{
public:
  UIElement() : GameObject(){};
  ~UIElement() {};

  //assumed that a UI element exists in screen space not world space but can be changed
  UIElement(glm::vec2 position_, glm::vec2 scale_, bool worldSpace = false) : GameObject()
  {
    GetComponent<Transform>()->SetScale(scale_);
    GetComponent<Transform>()->SetTranslation(position_);
    worldSpaceObject = worldSpace;


  };

 
private:



  //does the object exist in world space or exist in the UI Screen space




};