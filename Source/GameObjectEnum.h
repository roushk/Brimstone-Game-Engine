//***************************************************************************
// Filename: Stub.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef GAMEOBJECTENUM_H
#define GAMEOBJECTENUM_H

namespace GameObjectLayer
{
 
  //TODO remove the namespace shit and do this enum correctly
  enum GameObjectLayer : unsigned
  {
    Background,
    BackgroundEffects,
    Floor,
    FloorEffects,
    Obstacles,
    ObstacleEffects,
    Enemies,
    Players,
    Projectiles,
    GeneralEffects,
    Hud,
    HudEffects,
    Menu,
    MenuEffects,
    Cursor,
    OutOfBounds

  };
}


#endif