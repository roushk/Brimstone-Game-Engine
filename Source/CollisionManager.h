#pragma once
#include "System.h"
class CollisionManager : public System
{
public:
  CollisionManager();
  ~CollisionManager() override;

  void Update(float dt) override;
  static const SystemTypes type = SystemTypes::CollisionManager;

};
