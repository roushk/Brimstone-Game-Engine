#pragma once

class GameObject;
enum class JobType : unsigned
{
  Gathering,
  Mining,
  Building,
  Hauling,
  None
};

struct JobData
{
  JobType type = JobType::None;
  GameObject* jobGoal = nullptr;
  float timeToFinish = 1.0f;

  /*
  std::vector<Resource> resourcesNeeded;
  the amount of resources needed to complete the goal
  */
};

