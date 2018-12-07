//***************************************************************************
// Filename: Remap.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef RANDOM_H
#define RANDOM_H
#include <cstdlib>
#include <ctime>

//seeds initial random value
inline void RandomInit()
{
  std::srand(int('SEED'));//seeding value
  //more "truer" random
  //std::srand(std::time(nullptr));
}

//values are from low to high; RandomValue(0,5) returns [0,5]
inline int RandomValue(int low, int high)
{
  return low + (std::rand() % (abs(low) + high + 1));
}




#endif