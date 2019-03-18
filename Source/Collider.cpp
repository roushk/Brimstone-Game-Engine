#include "pch.h"
#include "Collider.h"

bool Collider::isColliding(const Collider& rhs)
{
  auto parentTrans = GetParent()->GetComponent<Transform>()->GetTranslation();
  auto rhsTrans = rhs.GetParent()->GetComponent<Transform>()->GetTranslation();

  //if distancesq less than radius sq
  if((rhsTrans.x - parentTrans.x) * (rhsTrans.x - parentTrans.x) + 
    (rhsTrans.y - parentTrans.y) * (rhsTrans.y - parentTrans.y) 
    <= (radius * radius + rhs.radius * rhs.radius))
  {
    /*
    rhs.GetParent()->GetComponent<Physics>()->SetAcceleration({ 0,0 });
    rhs.GetParent()->GetComponent<Physics>()->velocity = glm::vec2{ 0,0 };

    GetParent()->GetComponent<Physics>()->SetAcceleration({ 0,0 });
    GetParent()->GetComponent<Physics>()->velocity = glm::vec2{ 0,0 };
    */
    return true;
  }
  return false;
}

void Collider::resolveCollision(GameObject* obj)
{
  if(parent->HasComponent<UtilityAI>() && obj->HasComponent<UtilityAI>())
  {
    parent->GetComponent<UtilityAI>()->resolveNeed(*obj->GetComponent<UtilityAI>());
    
  }
}
