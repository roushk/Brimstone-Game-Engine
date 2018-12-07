//***************************************************************************
// Filename: AssetManager.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "System.h"
#include <map>
#include "Engine.h"
#include "Level.h"

//error when including Gameobject.h 
class GameObject;
class Texture;

class Sound
{

};

class AssetManager : public System
{
public:
  AssetManager();
  ~AssetManager() override;

  void Update(float dt) override;
  void LoadSprites();
  void LoadInitial();

  void AssetManager::LoadSingleTexture(std::string fileName);

  void AddGameObjectTexList(GameObject * obj);
  void RemoveGameObjectTexList(GameObject* obj);

  Texture* GetTexture(std::string spriteName);
  std::vector<std::vector<GameObject*>>& GetObjectTextureList() 
    { return objectTextures; };
  std::vector<Texture*>& GetTextureList()
  {
    return texturesBasedOnIDs;
  };

  static const int type = stAssetManager;
  
  unsigned BlankTextureID;

private:
  std::vector<Texture*> texturesBasedOnIDs;
  std::map<std::string, Texture*> textures;
  std::vector<std::vector<GameObject*>> objectTextures;
  std::map<std::string, Sound*> sounds;

  std::map<std::string, Level*> levels;
  //std::map<std::string, Sprite*> sprites;
  //std::map<std::string, Sprite*> sprites;

};


#endif

