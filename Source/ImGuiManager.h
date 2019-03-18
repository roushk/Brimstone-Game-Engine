//***************************************************************************
// Filename: GUIManager.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Window.h"
#include <vector>
#include "System.h"
#include "AssetManager.h"
#include "GUI.h"


/*create new light and set type with load and name and provide data*/
class ImGuiManager : public System
{
public:

  ImGuiManager(Window* window_) : window(window_), System() { name = "ImGui Manager"; BindImGUI(); };

  void BindImGUI()
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    io.IniFilename = NULL;  //disable imgui.ini

    ImGui_ImplSDL2_InitForOpenGL(window->gWindow, window->gContext);
    ImGui_ImplOpenGL3_Init();

    ImGui::StyleColorsDark();
    //ImFont* font0 = io.Fonts->AddFontDefault();
    //ImGui::PushFont(font0);

  };

  void RenderFrame(float dt)
  {
    ImGui_ImplOpenGL3_NewFrame();
    
    ImGui_ImplSDL2_NewFrame(window->gWindow);
    ImGui::NewFrame();
    //***************************************************************//
    //ImGui::ShowDemoWindow();

    for (auto & gui : guis)
    {
      gui.DrawGui(dt);
    }

    //***************************************************************//
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::EndFrame();
  };

  void Update(float dt = 0) override
  {
    //RenderFrame(dt);
    //render frame done in Render.cpp
  };

  ~ImGuiManager()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
  };
  Window* window;
  std::vector<GUI> guis;
  static const SystemTypes type = SystemTypes::ImGuiManager;

private:
};

#endif
