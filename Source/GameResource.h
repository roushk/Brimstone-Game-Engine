#ifndef GAME_RESOURCE_H
#define GAME_RESOURCE_H


enum class ResourceType
{
  Wood,
  Food,
  Iron,
  Stone
};

class GameResourceObject : public GameObject
{
public:
  GameResourceObject();
  ~GameResourceObject();
  
  ResourceType type;

  float amount = 10.0f;
  float timeToUse = 5.0f;

};

#endif