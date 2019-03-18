#include "pch.h"
#include "UtilityAi.h"
#include <gtx/norm.inl>


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
  //TODO: should put all possible needs that should be fufilled into a queue and sort them
  for(auto& need: needs)
  {
    need.second.currentValue -= dt * need.second.decay;
    //cooldown so doesn't spam the current value to like 50k in 2 seconds
    //currentCooldown can be negative, in fact will almost always be negative
    need.second.currentCooldown -= dt * need.second.decay;
    if(need.second.currentValue < need.second.min && reinterpret_cast<AStarObject*>(parent)->moving == false)
    {
      GetClosestFufillment(need.first, *map);
    }
  }
}

//sends object to closest filler for need
void UtilityAI::GetClosestFufillment(Need need, Map& map)
{
  auto parentAstar = reinterpret_cast<AStarObject*>(parent);
  if(parentAstar->request.computedPath == true)
  {
    return;
  }

  auto pos = parent->GetComponent<Transform>()->GetTranslation();

  float min = std::numeric_limits<float>::max();

  GameObject* closestNeedFiller = nullptr;
  for(auto &obj: map.objects.at(need))
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
  parentAstar->request.map = &map;

  parentAstar->request.settings.debugColoring = true;
  parentAstar->request.settings.rubberBanding = true;
  parentAstar->request.settings.singleStep = false;
  parentAstar->request.settings.smoothing = true;
  parentAstar->request.settings.weight = 1.0f;
  parentAstar->request.newRequest = true;
  
  auto result = pather->compute_path(parentAstar->request);
  if(result == PathResult::IMPOSSIBLE)
  {
    throw("Path Impossible");
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
