//***************************************************************************
// Filename: SpaceTypes.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef SPACE_TYPES_H
#define SPACE_TYPES_H
enum SpaceTypesEnum
{
  steBackground, //background, floor, untouchable by player
  steFloor,      //floor background
  steWorld,      //contains player, enemies, walls, collidable's, all that stuff
  steWorldHud,
  steHud,
  steMenu,
  steOutOfBounds
};

#endif