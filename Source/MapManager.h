//***************************************************************************
// Filename: MapManager.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include "System.h"
#include <map>
#include "Engine.h"
#include "Level.h"

//error when including Gameobject.h 
class GameObject;
class Texture;


class PrimsInProgress
{
public:
  std::vector<NodeCoord> wallList;
  std::vector<NodeCoord> mazeList;
  std::vector<NodeCoord> visited;

  std::vector<std::vector<PrimsNode>> primsMap;

};

class MapManager : public System
{
public:
  MapManager();
  ~MapManager() override;

  void Update(float dt) override;

  void GenerateMapLive(MazeGenerationMethod method);

  //returns true when finished
  bool GenerateMapUpdate();

  void GenerateMazePrimsInit();
  bool GenerateMazePrimsStep();

  static const SystemTypes type = SystemTypes::MapManager;
  

  int newWidth = 2;
  int newHeight = 2;

private:
  Map mapInProgress = Map(2,2);
  PrimsInProgress primsInProgress;
  bool mapIncomplete = false;
  bool mapFinished = true;
  MazeGenerationMethod currentMethod;

  std::vector<Map> maps;
  //std::map<std::string, Sprite*> sprites;
  //std::map<std::string, Sprite*> sprites;

};


#endif

