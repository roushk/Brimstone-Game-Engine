//***************************************************************************
// Filename: InputManager.cpp
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#include "pch.h"


#define GLM_ENABLE_EXPERIMENTAL

#define CAMERA_ACCEL_SPEED 1000
#include <glm/gtx/transform.hpp>


InputManager::InputManager() : System()
{
  name = "Input Manager";
  screenSize = engine.GetSystem<Render>()->screenSize;
  scaleToWorld = glm::scale(glm::vec3(
    (engine.GetSystem<Render>()->worldScale) / screenSize.x, 
    (engine.GetSystem<Render>()->worldScale) / screenSize.y, 1));
  aspect = screenSize.x / screenSize.y;


  for(int i = 4; i < 285; ++i)
  {
    //initialize all values with on none
    inputMap.insert_or_assign(i, InputButtonEvent::OnNone);
  }


  AddInputEvent(SDL_SCANCODE_W, InputButtonEvent::OnHold, [](float dt)
    {
      engine.GetSystem<Render>()->cameraVel += glm::vec2(0, -CAMERA_ACCEL_SPEED * dt);
    });

  AddInputEvent(SDL_SCANCODE_S, InputButtonEvent::OnHold, [](float dt)
    {
      engine.GetSystem<Render>()->cameraVel += glm::vec2(0, CAMERA_ACCEL_SPEED * dt);
    });


  AddInputEvent(SDL_SCANCODE_A, InputButtonEvent::OnHold, [](float dt)
    {
      engine.GetSystem<Render>()->cameraVel += glm::vec2(CAMERA_ACCEL_SPEED * dt, 0);
    });


  AddInputEvent(SDL_SCANCODE_D, InputButtonEvent::OnHold, [](float dt)
    {
      engine.GetSystem<Render>()->cameraVel += glm::vec2(-CAMERA_ACCEL_SPEED * dt, 0);
    });



      
  /*
  if (event.key.keysym.scancode == SDL_SCANCODE_W)
  {
    //eventQueue.push_back(InputEvent{ InputEvents::KeyboardButton, SDLK_w });
  }
  if (event.key.keysym.scancode == SDL_SCANCODE_A)
  {
    //eventQueue.push_back(InputEvent{ InputEvents::KeyboardButton, SDLK_a });

    engine.GetSystem<Render>()->cameraVel += glm::vec2(cameraAccelSpeed, 0);
  }
  if (event.key.keysym.scancode == SDL_SCANCODE_S)
  {
    engine.GetSystem<Render>()->cameraVel += glm::vec2(0, cameraAccelSpeed);
  }
  if (event.key.keysym.scancode == SDL_SCANCODE_D)
  {
    engine.GetSystem<Render>()->cameraVel += glm::vec2(-cameraAccelSpeed, 0);
  }

  */
}

InputManager::~InputManager()
{


}

void InputManager::Update(float dt)
{
  //camera movement drag
  engine.GetSystem<Render>()->cameraVel *= 0.96f;

  //camera movement
  engine.GetSystem<Render>()->cameraPos = 
    ((dt * engine.GetSystem<Render>()->cameraVel) + engine.GetSystem<Render>()->cameraPos);
  
  if(engine.GetSystem<Render>()->cameraVel.x > engine.GetSystem<Render>()->camMaxSpeed)
  {
    engine.GetSystem<Render>()->cameraVel.x = engine.GetSystem<Render>()->camMaxSpeed;
  }
  if (engine.GetSystem<Render>()->cameraVel.x < -engine.GetSystem<Render>()->camMaxSpeed)
  {
    engine.GetSystem<Render>()->cameraVel.x = -engine.GetSystem<Render>()->camMaxSpeed;
  }
  if (engine.GetSystem<Render>()->cameraVel.y > engine.GetSystem<Render>()->camMaxSpeed)
  {
    engine.GetSystem<Render>()->cameraVel.y = engine.GetSystem<Render>()->camMaxSpeed;
  }
  if (engine.GetSystem<Render>()->cameraVel.y < -engine.GetSystem<Render>()->camMaxSpeed)
  {
    engine.GetSystem<Render>()->cameraVel.y = -engine.GetSystem<Render>()->camMaxSpeed;
  }

  //mouse world coord transformations
  mouseWorldCoords = scaleToWorld * glm::vec4(mouseNDC, 0, 0);
  //used to test
  mouseWorldCoords *= (1.0f / engine.GetSystem<Render>()->cameraScale);
  mouseScreenCoords = mouseWorldCoords;
  mouseWorldCoords -= engine.GetSystem<Render>()->cameraPos;
  //engine.GetSystem<Render>()->objects.front()->GetComponent<Transform>()->SetTranslation(mouseWorldCoords);
  engine.GetSystem<Render>()->objects.front()->GetComponent<Transform>()->SetTranslation(mouseWorldCoords);
  engine.GetSystem<Render>()->objects.front()->GetComponent<Transform>()->
  SetScale({ 0.5f * 1.0f / engine.GetSystem<Render>()->cameraScale});



  //Firstly update all the on release key's to onNone
  for (auto& val : inputMap)
  {
    if(val.second == InputButtonEvent::OnRelease)
    {
      val.second = InputButtonEvent::OnNone;
    }
    else if (val.second == InputButtonEvent::OnPress)
    {
      val.second = InputButtonEvent::OnHold;
    }
  }

  //get event
  SDL_Event event;
  //while event queue is not empty pop off and deal with
  while (SDL_PollEvent(&event)) 
  {
    switch (event.type) 
    {
  default:
    //default event
    break;
  //if you press the close button the game shutsdown the engine
  case SDL_QUIT:
    {
      engine.Stop();
    }
    break;

  case SDL_WINDOWEVENT:
  {
    if (event.window.event == SDL_WINDOWEVENT_RESIZED)
      //|| event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) //breaks everything called ALOT

    {
      
      engine.GetSystem<Render>()->resize(event.window.data1, event.window.data2);
      screenSize = engine.GetSystem<Render>()->screenSize;
      scaleToWorld = glm::scale(glm::vec3(
        (engine.GetSystem<Render>()->worldScale) / screenSize.x, 
        (engine.GetSystem<Render>()->worldScale) / screenSize.y, 1));
      aspect = screenSize.x / screenSize.y;
    }
    else if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED)
    {
      
    }
    
  }
    
    break;
/*SDL_KeyboardEvent*/
  case SDL_KEYDOWN:
    {
      //If the button was pressed last frame then it is now held
      if(inputMap.at(static_cast<unsigned>(event.key.keysym.scancode)) == InputButtonEvent::OnRelease
        || inputMap.at(static_cast<unsigned>(event.key.keysym.scancode)) == InputButtonEvent::OnNone)
      {
        inputMap.insert_or_assign(event.key.keysym.scancode, InputButtonEvent::OnPress);

      }

     
      //engine.GetSystem<Render>()->cameraPos =
      //  glm::translate(engine.GetSystem<Render>()->cameraPos, glm::vec3(cameraPos, 0));
    }
    break;
  case SDL_KEYUP:

    inputMap.insert_or_assign(event.key.keysym.scancode, InputButtonEvent::OnRelease);

    break;
    
/*SDL_MouseButtonEvent*/
  case SDL_MOUSEBUTTONDOWN:
  {


    if(event.button.button == SDL_BUTTON_RIGHT && event.button.clicks == 1)
    {
      engine.GetSystem<Render>()->objects.front()->GetComponent<Transform>()->SetTranslation(mouseWorldCoords);

      for(auto obj: selected)
      {
        if(obj->moveable)
        {
          AStarObject* objPtr = reinterpret_cast<AStarObject*>(obj);
          if(objPtr != nullptr)
          {
            objPtr->request.start = obj->GetComponent<Transform>()->GetTranslation3D();
            objPtr->request.goal = glm::vec3(mouseWorldCoords.x,mouseWorldCoords.y, 0);
            objPtr->request.map = map;


            objPtr->request.settings.debugColoring = true;
            objPtr->request.settings.rubberBanding = true;
            objPtr->request.settings.singleStep = false;
            objPtr->request.settings.smoothing = true;
            objPtr->request.settings.weight = 1.0f;
            objPtr->request.newRequest = true;
            
            pather.compute_path(objPtr->request);


          }
        }
      }

    }
      //if right button held and then released

    
    if (event.button.button == SDL_BUTTON_LEFT  && event.button.state == SDL_PRESSED)
    {
      mouseSelectStartPos = mouseWorldCoords;
      held = true;
    }
  }
    break;
  case SDL_MOUSEBUTTONUP:
  {
    //Drag select
    if (event.button.button == SDL_BUTTON_LEFT 
      && event.button.state == SDL_RELEASED)
    {
      
      selected.clear();
      glm::vec2 minPoint, maxPoint;
      mouseSelectEndPos = mouseWorldCoords;
      if (held && mouseSelectEndPos != mouseSelectStartPos)
      {
        minPoint = glm::vec2{ std::min(mouseSelectEndPos.x, mouseSelectStartPos.x),
                      std::min(mouseSelectEndPos.y, mouseSelectStartPos.y) };

        maxPoint = glm::vec2{ std::max(mouseSelectEndPos.x, mouseSelectStartPos.x),
                      std::max(mouseSelectEndPos.y, mouseSelectStartPos.y) };
      }
      else
      {
        float boxRadius = 0.5f;
        minPoint = mouseWorldCoords - glm::vec2(boxRadius);
        maxPoint = mouseWorldCoords + glm::vec2(boxRadius);
      }
      

      float dist = glm::distance(mouseWorldCoords, maxPoint);
      GameObject* object = nullptr;
      for (auto &obj : engine.GetSystem<Render>()->objects)
      {
        if (obj->layer == GameObjectLayer::Cursor)
          continue;
        auto point = obj->GetComponent<Transform>()->GetTranslation();
        //bounding box selection
        if (point.x > minPoint.x && point.x < maxPoint.x 
          && point.y > minPoint.y && point. y < maxPoint.y)
        {
          
          if(held && mouseSelectEndPos != mouseSelectStartPos)
          {
            selected.push_back(obj);
          }
          else
          {
            float newDist = glm::distance(point, mouseWorldCoords);
            if(newDist < dist)
            {
              object = obj;
              dist = newDist;
            }
          }
        }
      }
      //multiple objects
      if(held && mouseSelectEndPos != mouseSelectStartPos)
      {
        for (auto& obj : selected)
        {
          obj->color = { 1,0,0,1 };
        }
      }
      //single object
      else if(object != nullptr)
      {
        selected.push_back(object);
        object->color = { 0,1,0,1 };
      }
      held = false;
    }
  }
    break;
/*SDL_MouseWheelEvent*/
  case SDL_MOUSEWHEEL:
  {
    float scale = 1.0f;
    if (event.wheel.y > 0) // scroll up
    {
      scale = 1.1f;
      // Pull up code here!
    }
    else if (event.wheel.y < 0) // scroll down
    {
      // Pull down code here!
      scale = 0.9f;
    }
      engine.GetSystem<Render>()->cameraScale *= scale;
      //= glm::scale(engine.GetSystem<Render>()->cameraPos, glm::vec3(scale, scale, 1.0f));
  }
    break;
/*SDL_MouseMotionEvent*/
  case SDL_MOUSEMOTION:
  {
    //updates mouse world and mouse screen coords
      
    //mouseNDC = glm::vec2((-screenSize.x / 2.0f + event.motion.x) * aspect, screenSize.y / 2.0f + -event.motion.y);
    mouseNDC = glm::vec2((-screenSize.x + event.motion.x * 2.0f) * aspect, screenSize.y + -event.motion.y * 2.0f);

  }
    break;
/*SDL_AudioDeviceEvent*/
  case SDL_AUDIODEVICEADDED:
    {

    }
    break;
  case SDL_AUDIODEVICEREMOVED: //SDL_AudioDeviceEvent
    {
      
    }
    break;

      //drop file
/*SDL_DropEvent*/
  case SDL_DROPFILE:
    {
      
    char* dropped_filedir = event.drop.file;
    // Shows directory of dropped file
    std::string droppedFile = dropped_filedir;
    
    //droppedFile.erase(0, droppedFile.find_last_of('\\') + 1);
      
    std::string textureName = droppedFile;
    textureName.erase(0, textureName.find_last_of('\\') + 1);

    //erases last 4 characters in filename, aka the .DDS in filename.DDS
    textureName.erase(textureName.find_last_of('.'), 4);


    std::cout << droppedFile << std::endl;
    engine.GetSystem<AssetManager>()->LoadSingleTexture(droppedFile);
    engine.GetSystem<Render>()->objects.front()->SetLayer(GameObjectLayer::OutOfBounds);
    engine.GetSystem<Render>()->objects.front()->GetComponent<Sprite>()->SetTexure(textureName);
      /*
    SDL_ShowSimpleMessageBox(
      SDL_MESSAGEBOX_INFORMATION,
      "File dropped on window",
      dropped_filedir,
      engine.GetSystem<Render>()->GetWindow()->gWindow
    );
    */
    SDL_free(dropped_filedir);    // Free dropped_filedir memory

  }
    break;

  case SDL_DROPTEXT:
//nothing
    {
      
    }
    break;

  case SDL_DROPBEGIN:
    {
      
    std::cout << "SDL drop begin" << std::endl;

    }
    break;

  case SDL_DROPCOMPLETE:
    {
      
    std::cout << "SDL drop complete" << std::endl;

    }
    break;

    }
  }
  /*
SDL_CONTROLLERAXISMOTION

SDL_ControllerAxisEvent
SDL_CONTROLLERBUTTONDOWN
SDL_CONTROLLERBUTTONUP

SDL_ControllerButtonEvent

SDL_CONTROLLERDEVICEADDED
SDL_CONTROLLERDEVICEREMOVED
SDL_CONTROLLERDEVICEREMAPPED

SDL_ControllerDeviceEvent

SDL_DOLLARGESTURE
SDL_DOLLARRECORD

SDL_DollarGestureEvent



SDL_DropEvent

SDL_FINGERMOTION
SDL_FINGERDOWN
SDL_FINGERUP

SDL_TouchFingerEvent

tfinger

SDL_KEYDOWN
SDL_KEYUP

SDL_KeyboardEvent

key

SDL_JOYAXISMOTION

SDL_JoyAxisEvent

jaxis

SDL_JOYBALLMOTION

SDL_JoyBallEvent

jball

SDL_JOYHATMOTION

SDL_JoyHatEvent

jhat

SDL_JOYBUTTONDOWN
SDL_JOYBUTTONUP

SDL_JoyButtonEvent

jbutton

SDL_JOYDEVICEADDED
SDL_JOYDEVICEREMOVED

SDL_JoyDeviceEvent

jdevice

SDL_MOUSEMOTION

SDL_MouseMotionEvent

motion

SDL_MOUSEBUTTONDOWN
SDL_MOUSEBUTTONUP

SDL_MouseButtonEvent

button

SDL_MOUSEWHEEL

SDL_MouseWheelEvent

wheel

SDL_MULTIGESTURE

SDL_MultiGestureEvent

mgesture

SDL_QUIT

SDL_QuitEvent

quit

SDL_SYSWMEVENT

SDL_SysWMEvent

syswm

SDL_TEXTEDITING

SDL_TextEditingEvent

edit

SDL_TEXTINPUT

SDL_TextInputEvent

text

SDL_USEREVENT

SDL_UserEvent

user

SDL_WINDOWEVENT

SDL_WindowEvent

window

Other events

SDL_CommonEvent

none, use .type
   */

  //update internet settings



  for (auto& input : inputMap)
  {
    if(input.second == InputButtonEvent::OnPress)
    {
      std::cout << "Key: " << input.first << " Pressed " << std::endl;
    }
    else if (input.second == InputButtonEvent::OnRelease)
    {
      std::cout << "Key: " << input.first << " Released " << std::endl;
    }
    else if (input.second == InputButtonEvent::OnHold)
    {
      std::cout << "Key: " << input.first << " Held " << std::endl;
    }

    //If there are events to be managed for that key
    if(inputEvents.find(input.first) != inputEvents.end())
    {

      //get a ref to the vector of functions to InputButtonEvents
      auto& inputVector = inputEvents.at(input.first);

      //for every function
      for(auto& inputFunc: inputVector)
      {
        //if the input state of the key is the same as the state of the firing function
        if(input.second == inputFunc.first)
        {
          //then call the function
          inputFunc.second(dt);
        }
      }
    }
  }

}

void InputManager::AddInputEvent(int SDLScancode, InputButtonEvent eventType,  std::function<void(float)> func)
{
  //If there is no value at that location in the map
  if(inputEvents.find(SDLScancode) == inputEvents.end())
  {
    //emplaces a new vector at the scancode
    inputEvents.emplace(SDLScancode, std::vector<std::pair<InputButtonEvent, std::function<void(float)>>>());

  }

  //actually adds the value at the location with the event type and function
  inputEvents.at(SDLScancode).push_back(std::make_pair(eventType, func));

}
