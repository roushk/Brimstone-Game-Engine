#pragma once

class GameObject;
enum class JobType : unsigned
{
  Gathering,
  Mining,
  Building,
  Hauling,
  Idle,
  None
};

struct JobData
{
  JobData(JobType type, GameObject* jobGoal, float timeToFinish, float totalTimeToFinish)
    : type(type), jobGoal(jobGoal), timeToFinish(timeToFinish), totalTimeToFinish(totalTimeToFinish){};
  
  JobData(JobType type, GameObject* jobGoal, float timeToFinish)
    : type(type), jobGoal(jobGoal), timeToFinish(timeToFinish), totalTimeToFinish(timeToFinish){};

  JobType type = JobType::None;
  GameObject* jobGoal = nullptr;
  float timeToFinish = 1.0f;
  float totalTimeToFinish = 1.0f;
  float percentage = 0.0f;
  bool complete = false;

  /*
  std::vector<Resource> resourcesNeeded;
  the amount of resources needed to complete the goal
  */
};

static std::shared_ptr<JobData> JobData_None(std::make_shared<JobData>(JobData{ JobType::Idle, nullptr, 0.0f }));

