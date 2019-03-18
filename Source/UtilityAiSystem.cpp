#include "pch.h"
#include "UtilityAiSystem.h"

void UtilityAiSystem::Update(const float dt)
{
  //while jobs are still available
  //try to give jobs to workers while still jobs

  for(auto &obj: engine.GetSystem<Render>()->objects)
  {
    if(obj->HasComponent<UtilityAI>() && obj->GetComponent<UtilityAI>()->canWork)
    {
      auto* utility = obj->GetComponent<UtilityAI>();
      //obj->GetComponent<UtilityAI>()->canWork
      
      utility->SetJob(jobs.at(JobType::Gathering).front());
    }
  }
}

