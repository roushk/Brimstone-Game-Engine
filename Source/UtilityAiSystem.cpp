#include "pch.h"
#include "UtilityAiSystem.h"

UtilityAiSystem::UtilityAiSystem() : System()
{
  jobs.insert_or_assign(JobType::Gathering, std::deque<std::shared_ptr<JobData>>());
  jobs.insert_or_assign(JobType::Mining, std::deque<std::shared_ptr<JobData>>());
  jobs.insert_or_assign(JobType::Building, std::deque<std::shared_ptr<JobData>>());
  jobs.insert_or_assign(JobType::Hauling, std::deque<std::shared_ptr<JobData>>());

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
          if (job.second[i].get()->complete)
            job.second.erase(job.second.begin() + i);
        }

        if(!job.second.empty() && !utility->isWorking)
        {
          
          utility->currentState = "Set New Job";

          auto& job2 = job.second.front();
          utility->SetJob(job.second.front());

          //utility->currentJob.get()->complete = true;
          utility->isWorking = true;
        }
      }
    }

    else if(utility->isWorking)
    {


      utility->currentState = "Is working";


      if(utility->currentJob.get()->type == JobType::Idle)
      {
        continue;
      }
      if (utility->currentJob.get()->jobGoal->HasComponent<Collider>() &&
        collider->isColliding(*utility->currentJob.get()->jobGoal->GetComponent<Collider>()))
      {
        utility->currentJob.get()->timeToFinish -= utility->skill * dt;
        utility->currentJob.get()->jobGoal->GetComponent<Transform>()->SetScale(utility->currentJob.get()->timeToFinish);


        if(utility->currentJob.get()->timeToFinish <= 0)
        {
          //set state to not working to accept new job
          utility->isWorking = false;
          //set current job to finished
          utility->currentJob.get()->complete = true;
          utility->currentJob.get()->jobGoal->GetComponent<Transform>()->SetRotation(3.14f/4.0f);
          auto* transform = utility->currentJob.get()->jobGoal->GetComponent<Transform>();
          transform->SetScale(transform->GetScale() / 2.0f);
          utility->currentState = "Reset Job";


          //set new job to none
          utility->ResetJob();
        }
      }
    }
  }
}

