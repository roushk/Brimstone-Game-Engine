//***************************************************************************
// Filename: GUI.cpp
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************
#include "pch.h"

void GUI::DrawGui(float dt)
{
  UNREFERENCED_PARAMETER(dt);

  
  ImGui::Begin("Editor", nullptr); // ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
  ImGui::Spacing();
  static ImVec2 windowScale = { 350.0f, static_cast<float>(engine.GetSystem<ImGuiManager>()->window->height) };
  static ImVec2 windowPosition{0.0f,0.0f};
  ImGui::SetWindowPos(windowPosition); //top left
  ImGui::SetWindowSize(windowScale);


  if(ImGui::Button("GenerateMap"))
  {
    engine.GetSystem<MapManager>()->GenerateMapLive(MazeGenerationMethod::RandomizedPrims);
  }
  //swap width and height
  ImGui::SliderInt("Map Dimensions", &engine.GetSystem<MapManager>()->newWidth, 1, 250);
  engine.GetSystem<MapManager>()->newHeight = engine.GetSystem<MapManager>()->newWidth;

  ImGui::PushItemWidth(-1);
  ImGui::Text("ObjectList");



  //Temp code until gamespaces are completed
  //static glm::vec2 objPos = engine.GetSystem<Render>()->objects.front()->GetComponent<Transform>()->GetTranslation();
  //ImGui::SliderFloat3("ObjPos", glm::value_ptr(objPos), -1, 1);
  //engine.GetSystem<Render>()->objects.front()->GetComponent<Transform>()->SetTranslation(objPos);
  
  static int currentObject;
  const char* objectsREMOVETHIS[] = { "first", "second", "third" };
  ImGui::Combo("ObjectComboList", &currentObject, objectsREMOVETHIS,3);
  ImGui::PopItemWidth();
  ImGui::End();
}
