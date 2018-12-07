//***************************************************************************
// Filename: System.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <iostream>  
#include "PerformanceMetrics.h"

class Engine;

class System
{
public:
  //sets system dtor to default to use dtor for derived class
  //https://wiki.sei.cmu.edu/confluence/display/cplusplus/OOP52-CPP.+Do+not+delete+a+polymorphic+object+without+a+virtual+destructor
  virtual ~System() = default;

  //set system ID and increment counter
  //this allows systems to be accesed with their ID
  System() { ID = nextSystemID++; };

  virtual void Update(const float dt) = 0;
  //virtual print to overload to print each system differerntly
  //based on https://stackoverflow.com/questions/7690807/overloading-operators-and-inherited-classes
  virtual std::ostream& print(std::ostream& out) const { return out << name << std::endl; };
  friend std::ostream& operator<<(std::ostream& os, const System& dt);
  
  std::string name;
  unsigned ID;
  PerformanceMetrics perf;
protected:
  static unsigned nextSystemID;
};

//prints out the custom print ostream operator to allow derived classes
//to have different print functions
inline std::ostream& operator<<(std::ostream& os, const System& rhs)
{
  return rhs.print(os);
}

/*
MAKE SURE FOR EVERY SYSTEM
top of update loop call 
perf.StartFrameTimer();
bottom of update loop call
perf.EndFrameTimer();
 */
#endif
