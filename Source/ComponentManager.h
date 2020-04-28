//***************************************************************************
// Filename: ComponentManager.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <vector>
#include "System.h"
#include "Component.h"
#include "Sprite.h"
#include "Transform.h"
#include "BasicBehavior.h"
#include "Physics.h"
#include "Collider.h"
#include "AI.h"
#include "ParticleManager.h"
#include "Engine.h"
#include <queue>
#include "UtilityAi.h"

#define MAXOBJECTS 250000
#define MAXCOMPLEXOBJECTS 1000


#define UNREFERENCED_PARAMETER(P) (P)




class ComponentManager : public System
{
  friend Component;
public:
  ComponentManager() : System(), components(ctOutOfBounds), availibleComponents(ctOutOfBounds)
  {
    name = "Component Manager";
    //components.reserve(ctOutOfBounds);  //reserve size of all component types

    for (unsigned i = 0; i < ctOutOfBounds; ++i)
    {
      if(i == ctSprite || i == ctTransform)
      components[i].resize(MAXOBJECTS);
      else
      {
        components[i].resize(MAXCOMPLEXOBJECTS);
      }
    

      availibleComponents[i].resize(MAXOBJECTS);

      for (unsigned j = 0; j < MAXOBJECTS; ++j)
      {
        availibleComponents[i][j] = j;
        if (i == ctSprite && j < MAXOBJECTS)
          components[i][j] = new Sprite;          
        if (i == ctTransform && j < MAXOBJECTS)
          components[i][j] = new Transform;
        if (i == ctPhysics && j < MAXCOMPLEXOBJECTS)
          components[i][j] = new Physics;
        if (i == ctBasicBehavior && j < MAXCOMPLEXOBJECTS)
          components[i][j] = new BasicBehavior;
        if (i == ctCollider && j < MAXCOMPLEXOBJECTS)
          components[i][j] = new Collider;
        if (i == ctAI && j < MAXCOMPLEXOBJECTS)
          components[i][j] = new AI;
        if (i == ctUtilityAI && j < MAXCOMPLEXOBJECTS)
          components[i][j] = new UtilityAI;
        if (i == ctParticleManager && j < MAXCOMPLEXOBJECTS)
          components[i][j] = new ParticleManager;
      }
    }
    /*
    for(auto & queue: availibleComponents)
    {
      std::cout << "front " << queue.front();
      for(auto & num: queue)
      {
        std::cout << " " << num;
      }
      std::cout << std::endl;
    }
    */
  };

  //removes component type
  template <typename ComponentType>
  void RemoveComponent(GameObject* obj)
  {
    for (auto & component : obj->components)
    {
      if (component->IsSameClassType(ComponentType::type))
      {
        component->parent = nullptr;
        component->active = false;
        obj->componentIDs[ComponentType::type] = 0;
        //TODO call reset on component that calls derived classes "reset" function
        //pushes compnent onto stack to be used when new game object is created to increase mem locality
        availibleComponents[ComponentType::type].push_front(component->ID);
      }
    }
  }

  //returns ID of component type
  template <typename ComponentType>
  bool AddComponentFromManager(GameObject* obj) // N(O) runtime
  {
    unsigned i = 0;
    
    //Old method to get component N time
    //while(components[ComponentType::type][i]->active)
    //{ ++i; }  //iterate i looking for not active component

    //new method to get component O time
    //more overhead (component number of queues and more memory but worth it

    //we have created a queue that holds each and every location (0 to maxcomponents)
    //of each component thats availible to make creating game objects O and not N time
    //the cost is in the deletion of the component you then need to pop that location onto 
    //the front of the deque of that component type
    i = availibleComponents[ComponentType::type].front();
    availibleComponents[ComponentType::type].pop_front();

    if(availibleComponents[ComponentType::type].empty())
    {
      std::string maxObjectsExceded = "Max Object Count exceeded, please increase";
      throw(maxObjectsExceded);

    }

    components[ComponentType::type][i]->active = true;
    components[ComponentType::type][i]->parent = obj;
    obj->components[ComponentType::type] = std::unique_ptr<Component>(components[ComponentType::type][i]);
    obj->componentIDs[ComponentType::type] = components[ComponentType::type][i]->ID;
    if (i == MAXOBJECTS)
      return false;
    
    return true;
  }

  Component* GetComponent(unsigned type_, unsigned pos) // N runtime
  {
    return components[type_][pos];
  }

  ~ComponentManager()
  {
    for (unsigned i = 0; i < ctOutOfBounds; ++i)
    {
      for (unsigned j = 0; j < MAXOBJECTS; ++j)
      {
        //delete components[i][j];
      }
    }
  };

  void Update(float dt) override
  {
    UNREFERENCED_PARAMETER(dt);
  }

  static const SystemTypes type = SystemTypes::ComponentManager;
private:
  std::vector<std::vector<Component*>> components;
  std::vector<std::deque<int>> availibleComponents;
};

#endif