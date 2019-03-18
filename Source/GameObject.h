//***************************************************************************
// Filename: GameObject.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Component.h"
#include <type_traits>
#include "ComponentManager.h"
//#include "glm.hpp"
#include "GameObjectEnum.h"

//will be layered in opengl with z = golOutOfbounds - layer
//in dtor make sure to reset the component ids into the id queue and reset their data
class GameObject
{
  friend ComponentManager;
public:
  virtual ~GameObject() = default;
  //Automatically adds Sprite and Transform to GameObject
  GameObject(): ID(NextGameObjectID++) 
  { AddComponent<Sprite>(); AddComponent<Transform>(); };

  GameObject& operator=(const GameObject & rhs);

  virtual void Update(float dt);

  //needs to return ptr as we don't know the size of each component
  template <class ComponentType>
  inline typename std::enable_if<std::is_base_of<Component, ComponentType>::value, 
    ComponentType*>::type GetComponent() const
  {
    if (dynamic_cast<ComponentType*>(components[ComponentType::type].get()) == nullptr)
    {
      std::string throwmsg = "Component Type";
      throwmsg += std::to_string(ComponentType::type);
      throwmsg += "Is nullptr. Make sure object has the component added";
      throw(throwmsg);
    }
    return dynamic_cast<ComponentType*>(components[ComponentType::type].get());
  }
  
  template <typename ComponentType>
  bool AddComponent()
  {
    return engine.GetSystem<ComponentManager>()->AddComponentFromManager<ComponentType>(this);
  }

  template <typename ComponentType>
  bool HasComponent()
  {
    return dynamic_cast<ComponentType*>(components[ComponentType::type].get()) != nullptr;
  }

  template <typename ComponentType>
  void RemoveComponent() const
  {
    engine.GetSystem<ComponentManager>()->RemoveComponent<ComponentType>(this);

  }
  //sets up so that everything is -z
  void SetLayer(const unsigned& layer_)
  {
    layer = layer_;
    GetComponent<Transform>()->translation.z = -(float(layer_) / float(GameObjectLayer::OutOfBounds));
  }
  
  unsigned GetLayer() const
  {
    return layer;
  }

  glm::vec4 color{0,0,0,1};
  glm::vec4 tempColor{0,0,0,1};
  unsigned layer = GameObjectLayer::OutOfBounds;
  unsigned ID;
  bool drawEdges = false;
  bool moveable = false;
private:

  static unsigned NextGameObjectID;
  std::unique_ptr<Component> components[ctOutOfBounds];
  unsigned componentIDs[ctOutOfBounds];
};
#endif
