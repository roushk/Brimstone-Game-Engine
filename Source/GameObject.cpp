#include "pch.h"

GameObject& GameObject::operator=(const GameObject & rhs) 
{
  ID = NextGameObjectID++;
  if (rhs.components[ctSprite]) //std::unique_ptr operator bool returns if object
  {
    AddComponent<Sprite>();
    *GetComponent<Sprite>() = *dynamic_cast<Sprite*>(rhs.components[ctSprite].get());
  }
  if (rhs.components[ctTransform]) //std::unique_ptr operator bool returns if object
  {
    AddComponent<Transform>();
    *GetComponent<Transform>() = *dynamic_cast<Transform*>(rhs.components[ctTransform].get());
  }
  return *this;
  //continue for all until ctOutOfBounds
}
