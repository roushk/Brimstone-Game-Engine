#include "pch.h"

/*
void GameObject::DestroyGameObject()
{
  if (HasComponent<Sprite>()) //std::unique_ptr operator bool returns if object
  {
    RemoveComponent<Sprite>();
  }
  if (HasComponent<Transform>()) //std::unique_ptr operator bool returns if object
  {
    RemoveComponent<Transform>();
  }
  if (HasComponent<Physics>()) //std::unique_ptr operator bool returns if object
  {
    RemoveComponent<Physics>();
  }
  if (HasComponent<BasicBehavior>()) //std::unique_ptr operator bool returns if object
  {
    RemoveComponent<BasicBehavior>();
  }
  if (HasComponent<Collider>()) //std::unique_ptr operator bool returns if object
  {
    RemoveComponent<Collider>();
  }
  if (HasComponent<AI>()) //std::unique_ptr operator bool returns if object
  {
    RemoveComponent<AI>();
  }
  if (HasComponent<UtilityAI>()) //std::unique_ptr operator bool returns if object
  {
    RemoveComponent<UtilityAI>();
  }
  if (HasComponent<ParticleManager>()) //std::unique_ptr operator bool returns if object
  {
    RemoveComponent<ParticleManager>();
  }
  
}
*/

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

void GameObject::Update(float dt)
{
  if(HasComponent<UtilityAI>())
  {
    GetComponent<UtilityAI>()->Update(dt);
  }

}
