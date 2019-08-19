#include "pch.h"



void UtilityAI::addNeed(Need name, float min, float max, float start, float decay)
{

  needs.insert_or_assign(name, NeedData{ min,max,start,decay });
}

void UtilityAI::addFufillment(Need name, float fufillment_, float useTime)
{
  fufillment.insert_or_assign(name, FufillmentData{ fufillment_, useTime });

}

void UtilityAI::Update(float dt)
{
  //system("CLS");
  //std::cout << currentState << std::endl;

  //if object is moving dont do anything
  if (reinterpret_cast<AStarObject*>(parent)->moving == true)
  {
    currentState = "Moving Along Path";
    return;
    
  }

  //TODO: should put all possible needs that should be fufilled into a queue and sort them
  Need highestPriorityNeed = Need::None;
  float highestPriorityNeedCost = 0;
  canWork = true;

  currentState = "Calculating Needs";

  for(auto& need: needs)
  {
    
    need.second.currentValue -= dt * need.second.decay;
    //decrements current value by scale to simulate time passing

    need.second.currentCooldown -= dt * need.second.decay;
    //cooldown so doesn't spam the current value to like 50k in 2 seconds
    //currentCooldown can be negative, in fact will almost always be negative


    if(need.second.currentValue < need.second.min 
      && need.second.priority * (need.second.min - need.second.currentValue)> highestPriorityNeedCost )
    {
      //cost is time past min * a scaling factor of priority
      highestPriorityNeedCost = need.second.priority * (need.second.min - need.second.currentValue);
      highestPriorityNeed = need.first;
    }
  }
  if(highestPriorityNeed != Need::None)
  {
    GetClosestFufillment(highestPriorityNeed);
    canWork = false;
    currentState = "Found Need";
    if(isWorking)
    {
      ResetJob();
    }
  }

}

//sends object to closest filler for need
void UtilityAI::GetClosestFufillment(Need need)
{
  auto parentAstar = reinterpret_cast<AStarObject*>(parent);

  //if we already have a path we have planned dont make a new one
  if(parentAstar->request.computedPath)
  {
    
    return;
  }

  

  auto pos = parent->GetComponent<Transform>()->GetTranslation();

  float min = std::numeric_limits<float>::max();

  GameObject* closestNeedFiller = nullptr;
  for(auto &obj: map->objects.at(need))
  {
    float dist = glm::distance2(obj->GetComponent<Transform>()->GetTranslation(), pos);
    if(dist < min)
    {
      min = dist;
      closestNeedFiller = obj;
    }
  }
  
  parentAstar->request.start = parent->GetComponent<Transform>()->GetTranslation();
  parentAstar->request.goal = closestNeedFiller->GetComponent<Transform>()->GetTranslation();
  parentAstar->request.map = map;

  parentAstar->request.settings.debugColoring = true;
  parentAstar->request.settings.rubberBanding = true;
  parentAstar->request.settings.singleStep = false;
  parentAstar->request.settings.smoothing = true;
  parentAstar->request.settings.weight = 1.0f;
  parentAstar->request.newRequest = true;
  
  auto result = pather->compute_path(parentAstar->request);
  if(result == PathResult::IMPOSSIBLE)
  {
    currentState = "PATH IMPOSSIBLE BIG OOF";
  }
}



//applys each obj need and fufillment to each other
void UtilityAI::resolveNeed(UtilityAI& rhs)
{
  for(auto& need: needs)
  {
    auto fufill = rhs.fufillment.find(need.first);
    if(fufill != rhs.fufillment.end() && need.second.currentCooldown < 0)
    {
      need.second.currentValue += fufill->second.fulfillment;
      need.second.currentCooldown = need.second.setCooldown;
    }
  }
  for (auto& fufill : fufillment)
  {
    auto need = rhs.needs.find(fufill.first);
    if (need != rhs.needs.end() && need->second.currentCooldown < 0)
    {
      need->second.currentValue += fufill.second.fulfillment;
      need->second.currentCooldown = need->second.setCooldown;
    }
  }
}

void UtilityAI::ResetJob()
{
  currentJob = JobData_None;
  isWorking = false;
}

void UtilityAI::SetJob(std::shared_ptr<JobData>& job)
{
  currentJob = job;
  //currentJob.get()->complete = true;
  
  auto parentAstar = reinterpret_cast<AStarObject*>(parent);

  //if we already have a path we have planned dont make a new one
  if (parentAstar->request.computedPath)
  {
    return;
  }
  
  parentAstar->request.start = parent->GetComponent<Transform>()->GetTranslation();
  parentAstar->request.goal = job.get()->jobGoal->GetComponent<Transform>()->GetTranslation();
  parentAstar->request.map = map;

  parentAstar->request.settings.debugColoring = true;
  parentAstar->request.settings.rubberBanding = true;
  parentAstar->request.settings.singleStep = false;
  parentAstar->request.settings.smoothing = true;
  parentAstar->request.settings.weight = 1.0f;
  parentAstar->request.newRequest = true;

  auto result = pather->compute_path(parentAstar->request);
}
