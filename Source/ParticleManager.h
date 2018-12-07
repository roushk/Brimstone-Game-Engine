//***************************************************************************
// Filename: ParticleManager.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

#include "Component.h"

class ParticleManager : public Component
{
public:

  ParticleManager() : Component()
  {
    ID = nextComponentID++;

  };

private:
  static unsigned nextComponentID;
};

#endif
