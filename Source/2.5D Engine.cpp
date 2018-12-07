//***************************************************************************
// Filename: 2.5D Engine.cpp
// Author  : Coleman Jonas
// Description: Defines the entry point for the console application
//***************************************************************************

#include "pch.h"



unsigned System::nextSystemID = 0;
unsigned Component::nextUniqueComponentID = 0;

unsigned AI::nextComponentID = 0;
unsigned BasicBehavior::nextComponentID = 0;
unsigned Collider::nextComponentID = 0;
unsigned ParticleManager::nextComponentID = 0;
unsigned Physics::nextComponentID = 0;
unsigned Sprite::nextComponentID = 0;
unsigned Transform::nextComponentID = 0;

unsigned Texture::nextTexID = 0;
unsigned GameObject::NextGameObjectID = 0;
unsigned Space::nextUniqueComponentID = 0;

Engine engine;



int main(const int argc, char** argv)
{
  //use getop or something to readin args
  
  UNREFERENCED_PARAMETER(argc);
  UNREFERENCED_PARAMETER(argv);

  float dt = 0.0f;

  PerformanceMetrics perf;
  perf.StartFrameTimer();
  RandomInit();

  Render render;  //calls Window()
  engine.AddSystem<Render>(&render);
  render.LoadAllShaders();
  //render initial

  AssetManager assetManager;  
  engine.AddSystem<AssetManager>(&assetManager);
  //Asset manager needs to load initial blank texture before component Manager 
  //because the blank tex needs to exists for sprites ctor
  assetManager.LoadInitial();

  ComponentManager componentManager;
  engine.AddSystem<ComponentManager>(&componentManager);
  assetManager.LoadSprites();

  ImGuiManager imGuiManager(render.GetWindow());
  engine.AddSystem<ImGuiManager>(&imGuiManager);

  InputManager inputManager;
  engine.AddSystem<InputManager>(&inputManager);

  GUI editorGui;

  imGuiManager.guis.push_back(editorGui);


  std::cout << engine;
  std::string mapStr = "map2.txt";
  Map map(mapStr);
  map.setOffset(-10, -10);
  //Map map = GenerateEmptyMap(50,50);
  inputManager.map = &map;
 

  GameObject cursor;
  engine.GetSystem<Render>()->objects.push_back(&cursor);
  cursor.GetComponent<Sprite>()->SetTexure("cursor1"); //cursor1
  cursor.SetLayer(golCursor);
  cursor.drawEdges = true;

  //testObj.GetComponent<Transform>()->SetScale({ 0.5f,0.5f });
  //testObj.GetComponent<Transform>()->SetTranslation({ -1.0f,0 ,-1.0f});


  AStarObject worker;
  engine.GetSystem<Render>()->objects.push_back(&worker);
  worker.GetComponent<Sprite>()->SetTexure("worker");
  worker.GetComponent<Transform>()->SetScale({0.5f, 0.5f});
  worker.GetComponent<Transform>()->SetTranslation({0.0f, 0.0f}); 
  worker.SetLayer(golPlayers);

  /*
  GameObject testObj3;
  testObj3.GetComponent<Sprite>()->SetTexure("Wall1");
  testObj3.SetLayer(golFloor);
  testObj3.color.a = 0.5f;
  */

  /*
  for(unsigned i = 0; i < 400; ++i)
  {
    GameObject* obj = new GameObject;
    obj->GetComponent<Sprite>()->SetTexure("Wall1");
    obj->color.a = 0.5f;
    engine.GetSystem<Render>()->objects.push_back(obj);
    obj->GetComponent<Transform>()->SetTranslation({ RandomValue(-10, 10), RandomValue(-10, 10) });
    obj->GetComponent<Transform>()->SetRotation(RandomValue(0, 2 * M_PI));
  }
  */
  
  //testObj.removeComponent
  //std::cout << *testObj.GetComponent<Sprite>();
  //1 millisecond = 1 nanosecond x 10^6
  std::cout << "Initialization took |" << perf.EndFrameTimer() / 1000000.0f << "|ms" << std::endl;
  while (engine.IsRunning())
  {
    perf.StartFrameTimer();

    engine.Update(dt / 1000000000.0f);  //nanoseconds to seconds
    
    dt = perf.EndFrameTimer();

    float fps = 1.0f / (dt / 1000000000.0f);
    
    std::string fpsTitle = " FPS = |";
    fpsTitle += std::to_string(static_cast<int>(fps));

    fpsTitle += "| Screen Size |X ";
    fpsTitle += std::to_string(static_cast<int>(engine.GetSystem<InputManager>()->screenSize.x));
    fpsTitle += " , Y ";
    fpsTitle += std::to_string(static_cast<int>(engine.GetSystem<InputManager>()->screenSize.y));
    
    fpsTitle += "| Mouse Pos World |X ";
    fpsTitle += std::to_string(engine.GetSystem<InputManager>()->mouseWorldCoords.x);
    fpsTitle += " , Y ";
    fpsTitle += std::to_string(engine.GetSystem<InputManager>()->mouseWorldCoords.y);
    fpsTitle += " |";

    SDL_SetWindowTitle(engine.GetSystem<Render>()->GetWindow()->gWindow, fpsTitle.c_str());
    
    //std::cout <<  std::endl;
    /*while (dt < minFrameTime)
    {
      dt = perf.EndFrameTimer();
      if (dt < minFrameTime)
        //delays smallest of 60 miliseconds or frame time left so fps is capped at 60 ms
        SDL_Delay(Uint32(std::min((minFrameTime - dt), 60.0f)));
    }*/
    //std::cout << engine;  //uncomment for printing of performance metrics for engine and engine subsystems
  }
  std::cout << "Shutting Down" << std::endl;
  return 0;
}

