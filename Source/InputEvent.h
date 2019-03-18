//***************************************************************************
// Filename: InputEvent.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

enum class InputEvents
{
  MouseButton,  //clicking button
  ButtonDown,       //keyboard/controller down
  ButtonUp,         //keyboard/controller up
  MouseMovement,    //mousemovement
  OutOfBounds
};

enum class InputMouseButtonEvents
{
  OnPress,
  OnRelease,
  OnHold
};

class InputEvent
{
  
};


#endif