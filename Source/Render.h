//***************************************************************************
// Filename: Render.cpp
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef RENDER_H
#define RENDER_H

#include "Engine.h"
#include "Window.h"
#include <glew.h>
#include <glm.hpp>

#define MAXPROGRAMS 2
#define MAXVERTEXBUFFERS 3

class GameObject;
class Texture;
//uv buffer,

enum shaderSetting
{
  ssTextureShader,
  ssSelectionBoxShader,
  ssOutOfBounds
};

class Render : public System
{
public:
  Render();
  ~Render() override;

  void ClearScreen()
  {
    //glColorMask(false, false, false, true);
    //glColorMask(true, true, true, true);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  };

  void ClearColor(glm::vec4 color)
  {
    glClearColor(color.x, color.y, color.z, color.w);
  };

  void LoadAllShaders();
  void Update(const float dt) override;
  std::ostream& print(std::ostream& out) const override;

  void resize(int w, int h);

  //Load Data once
  void Load2DSquareTextureMesh();

  //Per Object
  void LoadTexture(Texture* texture) const;
  void LoadUVs(GameObject& obj);

  //Load Model per texture/object
  void BindBuffers();
  void GenBufferCamera();
  void BufferCamera();
  
  //loads different UV's per object
  void DrawGameObjects(const float dt);

  void DrawObject(GameObject& obj);
  static const SystemTypes type = SystemTypes::Render;

  //TODO: REMOVE, FOR TESTING ONLY
  std::vector<GameObject*> objects;
  Window* GetWindow() { return &window; };
  bool standardUV = false;
  glm::vec2 screenSize;
  float worldScale = 10.0f;

  glm::vec2 cameraScale{ 1.0f, 1.0f };
  glm::vec2 cameraPos;
  glm::vec2 cameraVel;
  float camMaxSpeed = 20.0f;
  

private:
  //Camera camera;
  //model to world is useless as we are using sprites and not actual 3d models
  //glm::mat4 modelView = glm::mat4(1.0f);
  //glm::mat4 modelTransform; //model transform is objects transform
  glm::mat4 worldToNDC = glm::mat4(1.0f);
  glm::mat4 cameraMatrix = glm::mat4(1.0f);
  const glm::mat4 mat4identity = glm::mat4(1.0f);
  
  //no pers proj cause 2d

  Window window;
  GLuint programs[MAXPROGRAMS];
  GLuint programID = 0;

  /*
  0 is Position (same for all objects)
  1 is UV's for texture onto face
  2 is Faces (same for all objects)
   */
  GLuint vertexbuffers[MAXVERTEXBUFFERS];
  GLuint uboCamera;

  /*UBO camera is setup as such
  Object in world transform
  World to NDC transform
  World to Camera transform (optionally can be inserted between the object to world and World to NDC for camera)
  */

  const unsigned edges[8]{ 0,1, 1,2, 2,3, 3,0 };
  const unsigned faces[6]{ 0,1,2, 0,2,3 };
  const glm::vec4 lineColor{ 1,0,0,1 };



};

#endif
