//***************************************************************************
// Filename: PerformanceMetrics.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef PERFORMANCEMETRICS_H
#define PERFORMANCEMETRICS_H
#include <chrono>

class PerformanceMetrics
{
public:
  void StartFrameTimer()
  {
    start = std::chrono::system_clock::now();
  };

  float EndFrameTimer()
  {
    end = std::chrono::system_clock::now();
    auto chronoDt = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    frameTime = static_cast<float>(chronoDt.count());
    return frameTime;
  };

  float GetFrameTime() const
  { return frameTime; };
private:
  std::chrono::time_point<std::chrono::system_clock> start;
  std::chrono::time_point<std::chrono::system_clock> end;

  float frameTime = 0.0f;
};

#endif
