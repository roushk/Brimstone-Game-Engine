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
  JobType type = JobType::None;
  GameObject* jobGoal = nullptr;
  float timeToFinish = 1.0f;
  bool complete = false;

  /*
  std::vector<Resource> resourcesNeeded;
  the amount of resources needed to complete the goal
  */
};

static JobData JobData_None{ JobType::Idle, nullptr, 0.0f };

