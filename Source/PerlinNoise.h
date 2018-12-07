#pragma once
#include <cmath>
#include "Random.h"


class SigmoidCurve
{
  //pos 0 to 1
  float getValue(float pos, float xStart, float xScale = 1.0f, float yScale = 1.0f)
  {
    //fastest func is x / (1.0f + |x|
    //https://stackoverflow.com/questions/10732027/fast-sigmoid-algorithm
    //range of s curve is -4.2 to 4.2
    //so to get a value range 0 to 1 divide by 4.2f
    //to get range [-1 to 1]
    //then + 1.0f / 2.0f to range [0,1]
    pos = pos / xScale;
    float fx = yScale * (pos / (1.0f + std::abs(pos)));
    return ((fx / 4.2f) + 1.0f) / 2.0f;
  }
};

class PerlinNoise1D
{
  int degree = 1;
public:

  PerlinNoise1D(int degree = 1): degree(degree)
  {
    
  }

  float value()
  {
    float val = std::pow(PRNG.randomDouble(), 1);
    for(unsigned i = 1; i < degree; ++i)
    {
      val += std::pow(PRNG.randomDouble(), i);
    }

    return val;
  }
};


class PerlinNoise2D
{

};

class PerlinNoise3D
{

};

