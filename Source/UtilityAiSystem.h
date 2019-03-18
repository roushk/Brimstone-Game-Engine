
#ifndef UTILITY_AI_SYSTEM
#define UTILITY_AI_SYSTEM


#include "System.h"
#include "Job.h"

class UtilityAiSystem : public System
{
  void Update(const float dt) override;
  
  std::map<JobType, std::list<JobData>> jobs;
  std::map<JobType, std::vector<GameObject*>> workers;
  
  JobType workerNum[static_cast<unsigned>(JobType::None)];
  //std::vector<UtilityAI*> utility;
};



#endif

