//***************************************************************************
// Filename: Render.cpp
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************
#include "pch.h"


Render::Render() : System()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //calls Window() in ctor 
  name = "Render System";
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  //sets GL_COLOR_BUFFER_BIT to the clear color
  glClear(GL_COLOR_BUFFER_BIT);

  glGenBuffers(MAXVERTEXBUFFERS, vertexbuffers);
  resize(800, 600); //sets initial size
  Load2DSquareTextureMesh();
  GenBufferCamera();
}

void Render::LoadAllShaders()
{
  // do NOT | these arent flags!!!
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  
  glDepthFunc(GL_LEQUAL);
  glDepthMask(GL_TRUE);
  glClearDepth(1.0f);
  //glDepthRange(1,0);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  programs[0] = LoadShaders(std::string("Shaders/TextureShader.vert"), std::string("Shaders/TextureShader.frag"));
  programs[1] = LoadShaders(std::string("Shaders/SelectionBoxShader.vert"), std::string("Shaders/SelectionBoxShader.frag"));

  programID = programs[0];
}

Render::~Render()
{
  glDeleteBuffers(MAXPROGRAMS, vertexbuffers);
  //window dtor calls SDL Quit
}


void Render::resize(int w, int h)
{
  screenSize = glm::vec2(w, h);

  window.height = h;
  SDL_SetWindowSize(window.gWindow, w, window.height);
  glViewport(0, 0, w, window.height);
  window.aspect = float(w) / float(window.height);

  glm::mat4 aspectRatioMatrix{
    1.0f / window.aspect, 0, 0, 0,
    0, 1.0f , 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1 };

  glm::mat4 objectToWorld{
    1.0f / worldScale, 0, 0, 0,
    0, 1.0f / worldScale , 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1 };

  worldToNDC = aspectRatioMatrix * objectToWorld;

}

void Render::DrawGameObjects(const float dt)
{
  
  for (auto & texture : engine.GetSystem<AssetManager>()->GetTextureList())
  {

    LoadTexture(texture);
    //indexes into the vector of vectors and draws each object
    for (auto & object : engine.GetSystem<AssetManager>()->GetObjectTextureList().at(texture->ID))
    {
      if (object->HasComponent<Sprite>() == false)
        continue;
      if (standardUV == false && object->GetComponent<Sprite>()->standardUV == true)
      {
        LoadUVs(*object);
        standardUV = true;
      }
      else if (object->GetComponent<Sprite>()->standardUV == false)
      {
        LoadUVs(*object);
        standardUV = false;
      }
      //else if standardUV of sprite is true and of render is true dont load anything


      DrawObject(*object);
    }
  }
}



void Render::Update(const float dt)
{
  for(auto& obj: objects)
  {
    obj->Update(dt);
  }
  for (auto& obj : objects)
  {
    if(obj->HasComponent<Collider>())
    {
      for (auto& obj2 : objects)
      {
        if (obj->ID == obj2->ID)
          continue;
        if (obj2->HasComponent<Collider>())
        {
          if(obj->GetComponent<Collider>()->isColliding(*obj2->GetComponent<Collider>()))
          {
            obj->GetComponent<Collider>()->resolveCollision(obj2);
          }
        }
      }
      
    }
  }

  UNREFERENCED_PARAMETER(dt);
  
  ClearScreen();
  /***********************************************/
  //Loads the texture mesh for all models
  glUseProgram(programID);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  BindBuffers();
  //create map of <texture*, obj*> of all active objects (Done when textures are loaded)
  //iterate through asset manager's textures map
   //load tex
     //render objects in textures key

  //WARNING IF YOU YOU USE OTHER SHADERS MAKE SURE TO BUFFER THE WORLDTONDC MATRIX FOR THEM
  //WILL CAUSE ERROR IF MULTIPLE SHADERS USED
  glUseProgram(programID);
  
  cameraMatrix = glm::translate(glm::scale(  glm::mat4(1.0f), glm::vec3(cameraScale, 1.0f)), glm::vec3(cameraPos, 0)) ;
  
  
  //glUniformMatrix4fv(glGetUniformLocation(programID, "worldToNDC"), 1, GL_FALSE, glm::value_ptr(worldToNDC));
  //glUniformMatrix4fv(glGetUniformLocation(programID, "camera"), 1, GL_FALSE, glm::value_ptr(matrix));

  //bind world to NDC transform once
  glBindBuffer(GL_UNIFORM_BUFFER, uboCamera);
  glBufferSubData(GL_UNIFORM_BUFFER, sizeof glm::mat4, sizeof glm::mat4, glm::value_ptr(worldToNDC));
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  //DrawMap(dt);
  DrawGameObjects(dt);

  //glDisable(GL_TEXTURE_2D);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  /***********************************************/
  //Swap frame buffer

  engine.GetSystem<ImGuiManager>()->RenderFrame(dt);
  SDL_GL_SwapWindow(window.gWindow);
}

void Render::LoadUVs(GameObject& obj)
{
  /**********************************************************************************/
  //Load UV's for object
  UVRender uv = obj.GetComponent<Sprite>()->GetUVs();
  float uvArray[8]{ uv.lowerLeft.x,uv.lowerLeft.y, uv.lowerRight.x,uv.lowerRight.y,
  uv.upperRight.x, uv.upperRight.y, uv.upperLeft.x, uv.upperLeft.y };
  
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffers[1]);
  glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), uvArray, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  /**********************************************************************************/
}
//loads UV's and model transform
void Render::DrawObject(GameObject& obj)
{
  glUniform4fv(glGetUniformLocation(programID, "faceColor"),1, glm::value_ptr(obj.color));

  //glUniformMatrix4fv(glGetUniformLocation(programID, "modelView"), 1, GL_FALSE, glm::value_ptr(modelView));
  //glUniformMatrix4fv(glGetUniformLocation(programID, "modelTransform"), 1, GL_FALSE, glm::value_ptr(obj.GetComponent<Transform>()->GetMatrix()));

  //buffering at size of matrix * 1 for the world to NDC matrix and matrix * 2 for the NDC to Camera Matrix
  glBindBuffer(GL_UNIFORM_BUFFER, uboCamera);

  //buffer object transform
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof glm::mat4, glm::value_ptr(obj.GetMatrix()));
  
  //if object is a world space object then buffer the camera transform (which moves the object based on the camera)
  if(obj.worldSpaceObject)
  {
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof glm::mat4 * 2, sizeof glm::mat4, glm::value_ptr(cameraMatrix));
    
  }
  else
  {
    //if not then buffer the identity matrix so the object does not move
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof glm::mat4 * 2, sizeof glm::mat4, glm::value_ptr(mat4identity));

  }
  //buffering at 0 for the object in world space transform
  
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  //Draw verts * faces which happens to be 3 verts times 2 faces for a total of 1 quad
  glDrawElements(GL_TRIANGLES, 3 * 2, GL_UNSIGNED_INT, 0);

  //TODO fix draw edges to be selection box
  if(obj.drawEdges)
  {
    glUseProgram(programs[ssSelectionBoxShader]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexbuffers[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 8 * sizeof(unsigned), edges, GL_STATIC_DRAW);

    glUniform4fv(glGetUniformLocation(programs[ssSelectionBoxShader], 
      "lineColor"), 1, glm::value_ptr(lineColor));

    glLineWidth(1);
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned),  faces, GL_STATIC_DRAW);

    glUseProgram(programs[ssTextureShader]);
  }
}

std::ostream& Render::print(std::ostream& out) const
{
  out << name << std::endl;
  return out;
}


void Render::Load2DSquareTextureMesh()
{
  std::vector<glm::vec3> points{ 
    glm::vec3{-1,-1, 0 },glm::vec3{ 1,-1, 0 },glm::vec3{ 1, 1, 0 },glm::vec3{-1, 1, 0 } };

  std::vector<glm::uvec3> faces{glm::uvec3{ 0,1,2 }, glm::uvec3{ 0,2,3 } };

  glUseProgram(programID);

  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffers[0]);
  glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);


  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexbuffers[2]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(glm::uvec3), faces.data(), GL_STATIC_DRAW);
}


void Render::LoadTexture(Texture* texture) const
{
  glUseProgram(programID);
  //glActiveTexture(GL_TEXTURE);  //only loading 1 texture at a time
  glBindTexture(GL_TEXTURE_2D, texture->GetTexture());
  //glBindBuffer(GL_TEXTURE_2D, texture_buffer);

}

void Render::BindBuffers()  //binds position buffer, binds UV buffer
{
  glUseProgram(programID);
  // Use our shader

  // 1st attribute buffer : vertex positions (model space)
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffers[0]);
  glVertexAttribPointer(
    0,                  // attribute 0. MUST match the layout in the shader.
    3,                  // size of each datatype
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
  );


}

void Render::GenBufferCamera()
{
  glGenBuffers(1, &uboCamera);

  glBindBuffer(GL_UNIFORM_BUFFER, uboCamera);
  glBufferData(GL_UNIFORM_BUFFER, sizeof glm::mat4 * 3, nullptr, GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboCamera, 0, sizeof glm::mat4 * 3);
}

void Render::BufferCamera()
{
  //glBindBuffer(GL_UNIFORM_BUFFER, uboCamera);
  //glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof glm::mat4, &cameraData);
  //glBindBuffer(GL_UNIFORM_BUFFER, 0);
}




