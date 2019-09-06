#pragma once

#define UNREFERENCED_PARAMETER(P) (P)
#define GLM_ENABLE_EXPERIMENTAL
#pragma warning(disable : 4201)

//STL
#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <cmath>
//SDL
#include "SDL.h"

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <gtx/transform.hpp>
#include <gtx/norm.hpp>


//Imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

//glew
#include "glew.h"

//Engine
#include "AssetManager.h"
#include "AStarObject.h"
#include "Component.h"
#include "ComponentManager.h"
#include "Engine.h"
#include "FileLoad.h"
#include "GameObject.h"
#include "ImGuiManager.h"
#include "InputManager.h"
#include "ShaderLoader.h"
#include "Map.h"
#include "PerformanceMetrics.h"
#include "Physics.h"
#include "Random.h"
#include "Render.h"
#include "Space.h"
#include "SpaceManager.h"
#include "Sprite.h"
#include "Transform.h"
#include "Level.h"
#include "Window.h"

#include "Color.h"
#include "UI.h"
#include "PointContainment2D.h"
#include "UtilityAi.h"
#include "Job.h"

