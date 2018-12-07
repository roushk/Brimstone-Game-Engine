//***************************************************************************
// Filename: InputEvent.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

enum InputEvents
{
  ieMouseButtonDown,  //clicking down button
  ieMouseButtonUp,    //clicking up button
  ieButtonDown,       //keyboard/controller down
  ieButtonUp,         //keyboard/controller up
  ieMouseMovement,    //mousemovement
  ieOutOfBounds
};

class InputEvent
{
  
};


#endif