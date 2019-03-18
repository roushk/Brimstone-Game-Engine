
#ifndef UTILITY_AI_H
#define UTILITY_AI_H

#include "Component.h"
#include <map>
#include "Need.h"

class Map;
class AStarPather;

class UtilityAI : public Component
{
public:

  UtilityAI() : Component() { ID = nextComponentID++; };
  void addNeed(Need name, float min, float max, float start, float decay = 0.001f);
  void addFufillment(Need name, float fufillment, float useTime);
  void Update(float dt) override;
  void GetClosestFufillment(Need need, Map& map);
  void resolveNeed(UtilityAI& rhs);
  
  AStarPather* pather = nullptr;
  Map* map = nullptr;
  static cType type = ctUtilityAI;

private:
  static unsigned nextComponentID;
  static const int max_recursions_closest_need_filler = 5;

  std::map< Need, NeedData> needs;
  std::map < Need, FufillmentData > fufillment;
};

#endif