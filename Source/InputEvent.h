//***************************************************************************
// Filename: InputEvent.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H


enum class InputEvents
{
  MouseButton,    //clicking button
  KeyboardButton,         //keyboard/controller down
  MouseMovement,  //mouse movement
  OutOfBounds
};


enum class InputMouseButtonEvents
{
  OnPress,      //Key Pressed
  OnRelease,    //Key Released
  OnHold,       //Key Held (Pressed last frame)
  OutOfBounds
};


class InputEvent
{
public:
  InputEvent(InputEvents eventType_, InputMouseButtonEvents buttonEvent_) :
  eventType(eventType_), buttonEvent(buttonEvent_) {}

  InputEvent(InputEvents eventType_, int keycode_) : 
  eventType(eventType_), keycode(keycode_) {}

  InputEvents eventType = InputEvents::OutOfBounds;

  //mouse event if using mouse
  InputMouseButtonEvents buttonEvent = InputMouseButtonEvents::OutOfBounds;

  //keycode if using key
  int keycode = 0;  //Using SDKL_KEY NOT SDL_SCANCODE_KEY
};


#endif