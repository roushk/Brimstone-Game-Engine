#include "pch.h"
#include "Collider.h"

//basic circle circle collision
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

/*
   void ResolveCollision(Object A, Object B)
  {
    // Calculate relative velocity
    Vec2 rv = B.velocity - A.velocity

      // Calculate relative velocity in terms of the normal direction
      float velAlongNormal = DotProduct(rv, normal)

      // Do not resolve if velocities are separating
      if (velAlongNormal > 0)
        return;

    // Calculate restitution
    float e = min(A.restitution, B.restitution)

      // Calculate impulse scalar
      float j = -(1 + e) * velAlongNormal
      j /= 1 / A.mass + 1 / B.mass

      // Apply impulse
      Vec2 impulse = j * normal
      A.velocity -= 1 / A.mass * impulse
      B.velocity += 1 / B.mass * impulse
  }
   */

void Collider::resolveCollision(GameObject* obj)
{
  //glm::vec2 resolveVelocity = obj->GetComponent<Physics>()->velocity - parent->GetComponent<Physics>()->velocity;



  if(parent->HasComponent<UtilityAI>() && obj->HasComponent<UtilityAI>())
  {
    parent->GetComponent<UtilityAI>()->resolveNeed(*obj->GetComponent<UtilityAI>());
    
  }
}
