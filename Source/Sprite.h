//***************************************************************************
// Filename: Sprite.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef SPRITE_H
#define SPRITE_H

#include "Component.h"
#include "Texture.h"
#include <vector>
#include <detail/type_vec2.hpp>
#include "Engine.h"
#include "AssetManager.h"


struct UVRender
{
  glm::vec2 lowerLeft{ -1,-1 };
  glm::vec2 upperRight{ -1,-1 };
  glm::vec2 lowerRight{ -1,-1 };
  glm::vec2 upperLeft{ -1,-1 };
};

struct UV
{
  glm::vec2 lowerLeft{0,0};
  glm::vec2 upperRight{1,1};
};

/*Sprites are initialized with the OutOfBounds texture*/
class Sprite : public Component
{
public:
  Sprite() : Component(), texture(engine.GetSystem<AssetManager>()->GetTexture("BlankTexture"))
  {
    name = "Sprite";
    ID = nextComponentID++;
    UV newUV;
    uv.push_back(newUV);
  };
  Sprite& operator=(const Sprite& rhs)
  {
    name = rhs.name;
    ID = nextComponentID++;
    uv = rhs.uv;
    texture = rhs.texture;
    return *this;
  }
  ~Sprite() {};

  //gets texture from asset manager
  void SetTexure(std::string textureName)
  {
    //if no tex 
    /*set to BlankTextureID because BlankTextureID is blank texture ID and all 
    sprites are initialzied with this texture and because they are not attached 
    to any object the object count in the asset manager will be wrong so to 
    circumvent this we have the id as 2*/
    if(texture == nullptr || texture->ID == engine.GetSystem<AssetManager>()->BlankTextureID)
    {
      texture = engine.GetSystem<AssetManager>()->GetTexture(textureName);
      //sets texture then adds obj to texture's list of objects
      engine.GetSystem<AssetManager>()->AddGameObjectTexList(parent);
    }
    //if changing texture
    else
    {
      engine.GetSystem<AssetManager>()->RemoveGameObjectTexList(parent);
      texture = engine.GetSystem<AssetManager>()->GetTexture(textureName);
      //sets texture then adds obj to texture's list of objects
      engine.GetSystem<AssetManager>()->AddGameObjectTexList(parent);
    }
  };

  //used for rendering 
  UVRender GetUVs() const
  {
    UV curr = uv[currentFrame];
    UVRender uvs;
    uvs.lowerLeft = curr.lowerLeft;
    uvs.lowerRight = glm::vec2(curr.upperRight.x, curr.lowerLeft.y );
    uvs.upperLeft = glm::vec2( curr.lowerLeft.x, curr.upperRight.y );
    uvs.upperRight = curr.upperRight;
    return uvs;
  };
  Texture * GetTexure() const { return texture; };

  bool IsSameClassType(cType& rhs) const override
  { return rhs == type; };

  static cType type = ctSprite;
  unsigned currentFrame = 0;
  std::vector<UV> uv;
  bool standardUV = true;
private:
  Texture * texture;

  static unsigned nextComponentID;
  
};

#endif
