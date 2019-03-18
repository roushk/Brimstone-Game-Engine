#include "pch.h"
#include "UtilityAiSystem.h"

UtilityAiSystem::UtilityAiSystem() : System()
{
  jobs.insert_or_assign(JobType::Gathering, std::deque<JobData>());
  jobs.insert_or_assign(JobType::Mining, std::deque<JobData>());
  jobs.insert_or_assign(JobType::Building, std::deque<JobData>());
  jobs.insert_or_assign(JobType::Hauling, std::deque<JobData>());

  //jobs.insert_or_assign(JobType::Mining, std::list<JobData>());

}

void UtilityAiSystem::Update(const float dt)
{
  //while jobs are still available
  //try to give jobs to workers while still jobs
  
  for(auto &obj: engine.GetSystem<Render>()->objects)
  {
    if(!obj->HasComponent<UtilityAI>() && !obj->HasComponent<Collider>())
      continue;
    auto* utility = obj->GetComponent<UtilityAI>();
    auto* collider = obj->GetComponent<Collider>();
    if(utility->canWork
      && !utility->isWorking)
    {
      //obj->GetComponent<UtilityAI>()->canWork
      //need better way to find the jobs
      for(auto& job: jobs)
      {
        //update jobs and remove jobs that are finished
        for (unsigned i = 0; i < job.second.size(); ++i)
        {
          if (job.second[i].complete)
            job.second.erase(job.second.begin() + i);
        }

        if(!job.second.empty())
        {
          
          utility->SetJob(job.second.front());
          
          utility->isWorking = true;
        }
      }
    }

    else if(utility->isWorking)
    {

      if (utility->currentJob.jobGoal->HasComponent<Collider>() &&
        collider->isColliding(*utility->currentJob.jobGoal->GetComponent<Collider>()))
      {
        utility->currentJob.timeToFinish -= utility->skill * dt;
        if(utility->currentJob.timeToFinish <= 0)
        {
          //set state to not working to accept new job
          utility->isWorking = false;
          //set current job to finished
          utility->currentJob.complete = true;

          //set new job to none
          utility->ResetJob();
        }
      }
    }
  }
}

