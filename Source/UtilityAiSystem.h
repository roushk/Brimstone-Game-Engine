
#ifndef UTILITY_AI_SYSTEM
#define UTILITY_AI_SYSTEM


#include "System.h"
#include "Job.h"

class UtilityAiSystem : public System
{
public:
  UtilityAiSystem();
  void Update(const float dt) override;
  
  std::map<JobType, std::deque<std::shared_ptr<JobData>>> jobs;
  std::map<JobType, std::vector<GameObject*>> workers;
  
  JobType workerNum[static_cast<unsigned>(JobType::None)];

  static const SystemTypes type = SystemTypes::UtilityAiSystem;

  //std::vector<UtilityAI*> utility;
};



#endif

