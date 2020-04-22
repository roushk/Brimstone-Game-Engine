//***************************************************************************
// Filename: Engine.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef ENGINE_H
#define ENGINE_H
#include <vector>
#include "System.h"


enum class SystemTypes
{
  //ctNone,
  Render,
  AssetManager,
  ComponentManager,
  ImGuiManager,
  InputManager,
  CollisionManager,
  UtilityAiSystem,
  MapManager,
  OutOfBounds
};

class Engine : public System
{
public:
  Engine() : System() {};
  ~Engine() override
  {
    for (auto & system : systems)
    {
      //systems not allocated with new, references are passed
      //delete system;
    }
  };

  void Update(const float dt) override
  {
    perf.StartFrameTimer(); //starts timer for entire engine
    for(auto & system : systems)
    {
      //due to system array being static and noy dynamic need to check if each system exists
      if (system == NULL) 
        continue;
      system->perf.StartFrameTimer(); //starts timer per system
      system->Update(dt);
      system->perf.EndFrameTimer(); //ends timer per system
    }
    perf.EndFrameTimer();  //ends timer for entire engine
  };

  bool IsRunning() const
  {
    return isRunning;
  };

  void Stop()
  {
    isRunning = false;
  }

  //adds a system to the engine
  template <class SystemType>
  void AddSystem(System* system)
  {
    systems[static_cast<unsigned>(SystemType::type)] = system;
  };


  //gets the system
  template <class SystemType>
  inline typename std::enable_if<std::is_base_of<System, SystemType>::value,
    SystemType*>::type GetSystem()
  {
    return dynamic_cast<SystemType*>(systems[static_cast<unsigned>(SystemType::type)]);
  }

  //free memory
  friend std::ostream& operator<<(std::ostream& os, const Engine& dt);
  PerformanceMetrics perf;

private:
  //HAS to be pointer due to the System class being a pure virtual class
  //b/c it has size of 0 and pts have size of 8 
  System* systems[static_cast<unsigned>(SystemTypes::OutOfBounds)];
  bool isRunning = true;
};

//print out engine which in turn prints all subsystems
inline std::ostream& operator<<(std::ostream& os, const Engine& rhs)
{
  os << "+------------------------------------------------------------+" << std::endl;
  for (auto & system : rhs.systems)
  {
    if (system == NULL)
      continue;
    //prints system ID and them system info
    os << "System Name: |" << system->name << "| " <<
    "ID: |" << system->ID << "| " << " System Frame took |" << 
      system->perf.GetFrameTime() << "|s" << std::endl;
    system->print(os);
  }
  os << "Total Engine Frame took |" <<
    rhs.perf.GetFrameTime() << "|s" << std::endl;
  os << "+------------------------------------------------------------+" << std::endl;
  return os;
}

extern Engine engine;


#endif
