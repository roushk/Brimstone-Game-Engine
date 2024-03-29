//***************************************************************************
// Filename: BrimstoneGE.cpp
// Author  : Coleman Jonas
// Description: Defines the entry point for the console application
//***************************************************************************

#include "pch.h"
#include "UtilityAi.h"
#include "UtilityAiSystem.h"


unsigned System::nextSystemID = 0;
unsigned Component::nextUniqueComponentID = 0;

unsigned AI::nextComponentID = 0;
unsigned BasicBehavior::nextComponentID = 0;
unsigned Collider::nextComponentID = 0;
unsigned ParticleManager::nextComponentID = 0;
unsigned Physics::nextComponentID = 0;
unsigned Sprite::nextComponentID = 0;
unsigned Transform::nextComponentID = 0;
unsigned UtilityAI::nextComponentID = 0;

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

  UtilityAiSystem utilityAiSystem;
  engine.AddSystem<UtilityAiSystem>(&utilityAiSystem);


  GUI editorGui;

  imGuiManager.guis.push_back(editorGui);

  std::cout << engine;
  std::string mapStr = "map2.txt";
  Map map(mapStr);
  map.setOffset(-10, -10);
  //Map map = GenerateEmptyMap(50,50);
  inputManager.map = &map;

  AStarPather pather;


  //GameObject cursorChild;
  //cursorChild.GetComponent<Sprite>()->SetTexure("cursor1"); //cursor1
  //cursorChild.SetLayer(GameObjectLayer::Cursor);
  //cursorChild.GetComponent<Transform>()->SetTranslation(1, 1);

  GameObject cursor;
  engine.GetSystem<Render>()->objects.push_back(&cursor);
  cursor.GetComponent<Sprite>()->SetTexure("cursor1"); //cursor1
  cursor.SetLayer(GameObjectLayer::Cursor);
  cursor.drawEdges = true;
  //cursor.AddChild(cursorChild);
  //causes stack overflow because GetMatrix() is recursive and never finishes lmao
  //cursorChild.AddChild(cursor);

  //testObj.GetComponent<Transform>()->SetScale({ 0.5f,0.5f });
  //testObj.GetComponent<Transform>()->SetTranslation({ -1.0f,0 ,-1.0f});

  //UIElement testUI;
  //engine.GetSystem<Render>()->objects.push_back(&testUI);
  //testUI.GetComponent<Sprite>()->SetTexure("worker");
  //testUI.SetLayer(GameObjectLayer::Hud);
  //testUI.worldSpaceObject = false;


  AStarObject worker;
  engine.GetSystem<Render>()->objects.push_back(&worker);
  worker.GetComponent<Sprite>()->SetTexure("worker");
  worker.GetComponent<Transform>()->SetScale({0.25f, 0.25f});
  worker.GetComponent<Transform>()->SetTranslation({0.0f, 0.0f}); 
  worker.SetLayer(GameObjectLayer::Players);
  worker.AddComponent<UtilityAI>();
  worker.AddComponent<Collider>();
  worker.GetComponent<UtilityAI>()->addNeed(Need::Hunger, 0, 20, 20,1);
  worker.GetComponent<UtilityAI>()->addNeed(Need::Joy, 0, 20, 15,1);
  worker.GetComponent<UtilityAI>()->addNeed(Need::Work, 0, 20, 10, 1);
  worker.GetComponent<UtilityAI>()->pather = &pather;
  worker.GetComponent<UtilityAI>()->map = &map;
  worker.movementSpeed = 400.0f;

  AStarObject worker2;
  engine.GetSystem<Render>()->objects.push_back(&worker2);
  worker2.GetComponent<Sprite>()->SetTexure("worker");
  worker2.GetComponent<Transform>()->SetScale({ 0.25f, 0.25f });
  worker2.GetComponent<Transform>()->SetTranslation({ 0.0f, 0.0f });
  worker2.SetLayer(GameObjectLayer::Players);
  worker2.AddComponent<UtilityAI>();
  worker2.AddComponent<Collider>();
  worker2.GetComponent<UtilityAI>()->addNeed(Need::Hunger, 0, 20, 5, 1);
  worker2.GetComponent<UtilityAI>()->addNeed(Need::Joy, 0, 20, 15, 1);
  worker2.GetComponent<UtilityAI>()->addNeed(Need::Work, 0, 20, 10, 1);
  worker2.GetComponent<UtilityAI>()->pather = &pather;
  worker2.GetComponent<UtilityAI>()->map = &map;
  worker2.movementSpeed = 400.0f;

  AStarObject worker3;
  engine.GetSystem<Render>()->objects.push_back(&worker3);
  worker3.GetComponent<Sprite>()->SetTexure("worker");
  worker3.GetComponent<Transform>()->SetScale({ 0.25f, 0.25f });
  worker3.GetComponent<Transform>()->SetTranslation({ 0.0f, 0.0f });
  worker3.SetLayer(GameObjectLayer::Players);
  worker3.AddComponent<UtilityAI>();
  worker3.AddComponent<Collider>();
  worker3.GetComponent<UtilityAI>()->addNeed(Need::Hunger, 0, 20, 20, 1);
  worker3.GetComponent<UtilityAI>()->addNeed(Need::Joy, 0, 20, 5, 1);
  worker3.GetComponent<UtilityAI>()->addNeed(Need::Work, 0, 20, 5, 1);
  worker3.GetComponent<UtilityAI>()->pather = &pather;
  worker3.GetComponent<UtilityAI>()->map = &map;
  worker3.movementSpeed = 400.0f;


  GameObject testNeedHunger;
  engine.GetSystem<Render>()->objects.push_back(&testNeedHunger);
  testNeedHunger.GetComponent<Sprite>()->SetTexure("testneed1");
  testNeedHunger.GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });
  testNeedHunger.GetComponent<Transform>()->SetTranslation({ 5.0f, 5.0f });
  testNeedHunger.SetLayer(GameObjectLayer::Obstacles);
  testNeedHunger.AddComponent<UtilityAI>();
  testNeedHunger.AddComponent<Collider>();
  testNeedHunger.GetComponent<UtilityAI>()->addFufillment(Need::Hunger, 30, 0);

  GameObject testNeedJoy;
  engine.GetSystem<Render>()->objects.push_back(&testNeedJoy);
  testNeedJoy.GetComponent<Sprite>()->SetTexure("testneed2");
  testNeedJoy.GetComponent<Transform>()->SetScale({ 0.2f, 0.5f });
  testNeedJoy.GetComponent<Transform>()->SetTranslation({ -2.0f, -3.0f });
  testNeedJoy.SetLayer(GameObjectLayer::Obstacles);
  testNeedJoy.AddComponent<UtilityAI>();
  testNeedJoy.AddComponent<Collider>();
  testNeedJoy.GetComponent<UtilityAI>()->addFufillment(Need::Joy, 30, 0);

  GameObject testNeedWork;
  engine.GetSystem<Render>()->objects.push_back(&testNeedWork);
  testNeedWork.GetComponent<Sprite>()->SetTexure("testneed3");
  testNeedWork.GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });
  testNeedWork.GetComponent<Transform>()->SetTranslation({ -2.0f, 9.0f });
  testNeedWork.SetLayer(GameObjectLayer::Obstacles);
  testNeedWork.AddComponent<UtilityAI>();
  testNeedWork.AddComponent<Collider>();
  testNeedWork.GetComponent<UtilityAI>()->addFufillment(Need::Work, 30, 0);

  GameObject testJob1;
  engine.GetSystem<Render>()->objects.push_back(&testJob1);
  testJob1.GetComponent<Sprite>()->SetTexure("testjob1");
  testJob1.GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });
  testJob1.GetComponent<Transform>()->SetTranslation({ 0.0f, 5.0f });
  testJob1.SetLayer(GameObjectLayer::Obstacles);
  testJob1.AddComponent<UtilityAI>();
  testJob1.AddComponent<Collider>();
  //testJob1.GetComponent<UtilityAI>()->addFufillment(Need::Work, 20, 0);


  UIElement testJob1ui;
  testJob1ui.anchor.horizontalAnchor = UIElementAnchor::HorizontalAnchor::Center;
  testJob1ui.GetComponent<Transform>()->SetTranslation(testJob1.GetComponent<Transform>()->GetTranslation());
  testJob1ui.GetComponent<Transform>()->SetScale(glm::vec2(0.5, 0.1));
  testJob1ui.anchor.offsetAfterAnchor = glm::vec2(0, 0.1f);
  testJob1ui.GetComponent<Sprite>()->SetTexure("BlankTexture");
  testJob1ui.SetLayer(GameObjectLayer::Hud);


  testJob1.AddChild(testJob1ui);



  GameObject testJob2;
  engine.GetSystem<Render>()->objects.push_back(&testJob2);
  testJob2.GetComponent<Sprite>()->SetTexure("testjob2");
  testJob2.GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });
  testJob2.GetComponent<Transform>()->SetTranslation({ 4.0f, 0.0f });
  testJob2.SetLayer(GameObjectLayer::Obstacles);
  testJob2.AddComponent<UtilityAI>();
  testJob2.AddComponent<Collider>();
  //testJob2.GetComponent<UtilityAI>()->addFufillment(Need::Work, 20, 0);

  GameObject testJob3;
  engine.GetSystem<Render>()->objects.push_back(&testJob3);
  testJob3.GetComponent<Sprite>()->SetTexure("testjob3");
  testJob3.GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });
  testJob3.GetComponent<Transform>()->SetTranslation({ -3.0f, 2.0f });
  testJob3.SetLayer(GameObjectLayer::Obstacles);
  testJob3.AddComponent<UtilityAI>();
  testJob3.AddComponent<Collider>();
  //testJob3.GetComponent<UtilityAI>()->addFufillment(Need::Work, 20, 0);

  
  utilityAiSystem.jobs.at(JobType::Hauling).push_back(std::make_shared<JobData>(JobData{ JobType::Hauling, &testJob3, 10.0f }));
  utilityAiSystem.jobs.at(JobType::Building).push_back(std::make_shared<JobData>(JobData{ JobType::Building, &testJob2, 10.0f }));
  utilityAiSystem.jobs.at(JobType::Gathering).push_back(std::make_shared<JobData>(JobData{ JobType::Gathering, &testJob1, 10.0f }));


  std::vector<GameObject*> hungerObj;
  hungerObj.push_back(&testNeedHunger);

  std::vector<GameObject*> joyObj;
  joyObj.push_back(&testNeedJoy);

  std::vector<GameObject*> workObj;
  workObj.push_back(&testNeedWork);


  map.objects.insert_or_assign(Need::Hunger, hungerObj);
  map.objects.insert_or_assign(Need::Joy, joyObj);
  map.objects.insert_or_assign(Need::Work, workObj);


  /*
  GameObject testObj3;
  testObj3.GetComponent<Sprite>()->SetTexure("Wall1");
  testObj3.SetLayer(GameObjectLayer::Floor);
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

