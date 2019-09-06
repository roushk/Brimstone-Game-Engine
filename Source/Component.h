//***************************************************************************
// Filename: Component.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <iostream>  
#include "PerformanceMetrics.h"


class ComponentManager;
//typename std::enable_if<std::is_base_of<Component, T>::value
//NEED to declare each component type with a static cType of the component types enum
typedef const int cType;

class GameObject;

enum ComponentTypes
{
  //ctNone,
  ctSprite,
  ctTransform,
  ctPhysics,
  ctBasicBehavior,
  ctCollider,
  ctAI,
  ctUtilityAI,
  ctParticleManager,
  ctOutOfBounds
};

class Component
{
  friend ComponentManager;
public:
  Component() { uniqueComponentID = nextUniqueComponentID++; };
  virtual ~Component() = default;
  virtual std::ostream& print(std::ostream& out) const
  {
    out << "Component Name: |" << name << "| " <<
      "ID: |" << ID << "| " << "UID: |" << uniqueComponentID << "| " << std::endl;
    return out;
  };
  //template <typename T>
  friend std::ostream& operator<<(std::ostream& os, const Component& dt);

  virtual bool IsSameClassType(cType& rhs) const
  { return rhs == type; }

  virtual void Update(float dt) {};
  void SetParent(GameObject* parent_) { parent = parent_; };
  GameObject * GetParent() const { return parent; };
  unsigned GetType() const { return type; };

  int ID = -1;
  bool active = false;
  std::string name = "Uninitialized Component";
  static cType type = ctOutOfBounds;
  unsigned uniqueComponentID;

protected:
  GameObject* parent = nullptr;
  static unsigned nextUniqueComponentID;
};

inline std::ostream& operator<<(std::ostream& os, const Component& rhs)
{
  return rhs.print(os);
}



#endif