//***************************************************************************
// Filename: AssetManager.cpp
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************
#include "pch.h"

AssetManager::AssetManager() : System()
{
  name = "Asset Manager";
}

AssetManager::~AssetManager()
{

}

void AssetManager::LoadInitial()
{
  /*
  std::string fileName = "./Art/DDS/ INITIAL LOGO";

  Texture * texture = new Texture(fileName);
  textures._Insert_or_assign("INITIAL LOGO", texture);
  */
  //BlankTexture
  std::string fileName = "./Art/DDS/BlankTexture.DDS";

  Texture * texture = new Texture(fileName);
  textures.insert_or_assign("BlankTexture", texture);
  
  BlankTextureID = texture->ID;

  texturesBasedOnIDs.push_back(texture);

  std::vector<GameObject*> objectVector;
  objectTextures.push_back(objectVector);
}

//to support dragging and dropping textures into engine too test them
void AssetManager::LoadSingleTexture(std::string fileName)
{
  Texture * texture = new Texture(fileName, false);
  std::string textureName = fileName;
  textureName.erase(0, textureName.find_last_of('\\') + 1);

  //erases last 4 characters in filename, aka the .DDS in filename.DDS
  textureName.erase(textureName.find_last_of('.'), 4);

  std::cout << "Loading singleton texture |" << textureName << "|" << std::endl;
  textures.insert_or_assign(textureName, texture);

  BlankTextureID = texture->ID;

  texturesBasedOnIDs.push_back(texture);

  std::vector<GameObject*> objectVector;
  objectTextures.push_back(objectVector);
}

void AssetManager::Update(float dt)
{
  UNREFERENCED_PARAMETER(dt);
}

//do not change texture before calling this
void AssetManager::RemoveGameObjectTexList(GameObject* obj)
{
  auto it = std::find(objectTextures.at(obj->GetComponent<Sprite>()->GetTexure()->ID).begin(), 
    objectTextures.at(obj->GetComponent<Sprite>()->GetTexure()->ID).end(), obj);
  
  if (it != objectTextures.at(obj->GetComponent<Sprite>()->GetTexure()->ID).end())
    objectTextures.at(obj->GetComponent<Sprite>()->GetTexure()->ID).erase(it);
  //if here didnt find object
}

//adds game object to texture list to render
void AssetManager::AddGameObjectTexList(GameObject* obj)
{
  objectTextures.at(obj->GetComponent<Sprite>()->GetTexure()->ID).push_back(obj);
}

//make sure to remove initial sprites from sprite list
void AssetManager::LoadSprites()
{
  std::vector<std::string> spriteString;

  std::string filetoload = "sprites.txt";
  std::ifstream readfile(filetoload.c_str(), std::ios::in | std::ios::binary);

  if (!readfile.is_open())
  {
    //trace.FileLoad(fileTag, filetoload);
  }
  else
  {
    std::string buffer;
    while (readfile >> buffer)
    {
      spriteString.push_back(buffer); //Push back files
    }
  }
  readfile.close();
  //get all art
  for (unsigned i = 0; i < spriteString.size(); ++i)
  {
    size_t dot = spriteString.at(i).find_last_of(".");
    //break out of not found
    std::string nameTitle = spriteString.at(i);

    std::string dotname = spriteString.at(i).substr(dot + 1);


    nameTitle = nameTitle.substr(0, nameTitle.size() - dotname.size() - 1);

    std::string fileName;

    fileName += "./Art/DDS/";
    fileName += spriteString.at(i);

    Texture * sprite = new Texture(fileName);
    textures.insert_or_assign(nameTitle, sprite);
    texturesBasedOnIDs.push_back(sprite);
    std::vector<GameObject*> objectVector;
    objectTextures.push_back(objectVector);
  }

  //objectTextures.resize(textures.size()); //allocs objectTextures array to be size of ALL textures
  //No more textures loaded in after this point into asset manager guarenteed
}

Texture* AssetManager::GetTexture(std::string spriteName)
{
  Texture* texture;
  try
  {
    texture = textures.at(spriteName);
  }
  catch (...)
  {
    std::string error = "\n\n!!!!ERROR LOADING SPRITE \"";
    error += spriteName;
    error += "\" Check sprites.txt to make sure the name has the correct capital letters and is spelled correctly!!!!\n\n";
    throw(error);
    //print error
  }

  return texture;
}

