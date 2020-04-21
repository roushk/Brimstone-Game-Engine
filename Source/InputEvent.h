//***************************************************************************
// Filename: InputEvent.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H


enum class InputButtonEvent
{
  OnNone,       //Key is untouched this frame or last frame, default state
  OnPress,      //Key Pressed (Pressed this frame)
  OnRelease,    //Key Released (Released this frame)
  OnHold,       //Key Held (Pressed last frame)
  OutOfBounds
};


enum class InputMouseButtonEvent
{
  OnNone,             //Mouse button is untouched this frame or last frame, default state
  OnPress,            //Mouse button is clicked
  OnHold,             //Mouse button is held down
  OnRelease,          //Mouse button is released
  OnDoubleClick,      //Mouse button is double clicked
  OnDoubleClickHold,  //Mouse button is double clicked and held down
  OutOfBounds
};


/*

class InputEvent
{
public:
  InputEvent(InputEventType eventType_, InputButtonEvent buttonEvent_) :
  eventType(eventType_), buttonEvent(buttonEvent_) {}

  InputEvent(InputEventType eventType_, int keycode_) : 
  eventType(eventType_), keycode(keycode_) {}

  InputEventType eventType = InputEventType::OutOfBounds;

  //mouse event if using mouse
  InputButtonEvent buttonEvent = InputButtonEvent::OutOfBounds;

  //keycode if using key
  int keycode = 0;  //Using SDKL_KEY NOT SDL_SCANCODE_KEY
};
*/


#endif