//***************************************************************************
// Filename: Remap.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef RANDOM_H
#define RANDOM_H
#include <cstdlib>
#include <ctime>


class PseudoRandomNumberGenerator
{
  const int randMax = 0x7fffffff; //32767
  long holdRand = 0;
public:

  PseudoRandomNumberGenerator(int seed = 618294512)
  {
    holdRand = (long)seed;
  }
  PseudoRandomNumberGenerator(const PseudoRandomNumberGenerator& rhs);
  void operator=(const PseudoRandomNumberGenerator& rhs);


  int randomInt()
  {
    return(((holdRand = std::abs(holdRand * 214013L + 2531011L) >> 16) & randMax));
  }

  int randomRange(int low, int high)
  {
    return low + (randomInt() % (abs(low) + high + 1));
  }

  //returns 0 to 1
  double randomDouble()
  {
    return (double(randomInt() % 0x7fffffff) / 0x7fffffff);
  }

  //range -1 to 1 
  double randomGaussian()
  {
    return (randomDouble() + randomDouble() + randomDouble()) / 3.0f;
  }

};
extern PseudoRandomNumberGenerator PRNG;


#endif