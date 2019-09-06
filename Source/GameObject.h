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
  //Automatically adds Sprite and Transform to GameObject because every object needs these two
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

  float GetLayerZValue() const
  {
    return -(float(layer) / float(GameObjectLayer::OutOfBounds));
  }
  
  unsigned GetLayer() const
  {
    return layer;
  }

  void AddChild(GameObject& child)
  {
    child.parent = this;
    children.insert_or_assign(child.ID, &child);
  }

  void RemoveChild(GameObject& child)
  {
    //reset parent pointer for child
    child.parent = nullptr;
    //make sure that is how to remove objects from map
    children.erase(child.ID);
  }
  
  

  GameObject* GetParent() const
  {
    return parent;
  }

  //gets all the matrices through to the parents one in a recursive function
  //that goes up through the matrices to get the total matrix
  //technically (untested) you should be able to multiply the transform of the object up this chain
  //of matrices to get the actual world space of the object and not just the local to parent transform
  glm::mat4 GetMatrix() const
  { 
    //the negative parent get z is to undo the layering that is introduces when setting the layer of the object
    //this layering works perfectly for a single object but if you want to concat the matrices you need
    //to undo the layer of the parent so that the layer of the child is correct
    if(parent != nullptr)
      return GetComponent<Transform>()->GetMatrix() * glm::translate(glm::vec3(0,0,-parent->GetLayerZValue())) *  parent->GetMatrix();

    //if this is the only object up the parent chain then we don't need to do anything
    return GetComponent<Transform>()->GetMatrix();
  };


  glm::vec4 color{0,0,0,1};
  glm::vec4 tempColor{0,0,0,1};

  //layer that the object exists for rendering purposes
  unsigned layer = GameObjectLayer::OutOfBounds;

  //unique ID of the current game object
  unsigned ID;

  //draw edges of the mesh Not the sprite
  bool drawEdges = false;

  //if the object moves inside the world or not (used for AStarPathing right now????)
  bool moveable = false;


  //TODO: double check that if a parent is world space and a child isn't that it works as expected 
  //though i don't think we need to care if someone uses the system like that as it still
  //works properly technically
  //does the game object exist in world space or camera/screen space
  bool worldSpaceObject = true;

  //children objects based on the object ID's so no duplicates
private:


  //TODO add error checking if child and parent loop???
  //use Add Child not set parent
  void SetParent(GameObject& parent_)
  {
    parent = &parent_;

  }
  std::map<unsigned, GameObject*> children;
  GameObject* parent = nullptr;
  static unsigned NextGameObjectID;
  std::unique_ptr<Component> components[ctOutOfBounds];
  unsigned componentIDs[ctOutOfBounds];
};
#endif
