#pragma once

#include <functional>

//TODO is a variable member function even a thing without having to add each func to the class???


class UIElement : public GameObject
{
public:
  UIElement() : GameObject(){};
  ~UIElement() {};

  //assumed that a UI element exists in screen space not world space but can be changed
  UIElement(glm::vec2 position_, glm::vec2 scale_, bool worldSpace = false);;

  //assuming only square buttons
  bool isHovered(glm::vec2 worldMousePosition);

  void Update(float dt) override;

  //std::function<void()> OnClickStart;

  //called once, the frame the object is clicked
  std::function<void()> OnClick;

  //only called once
  std::function<void()> OnHoverStart;

  //called every frame after the first the object is hovered
  std::function<void()> OnHover;

  //called the frame after object is no longer hovered 
  std::function<void()> OnHoverEnd;

  bool buttom = false;
  glm::vec2 buttonClickOffset = glm::vec2(0);


  bool isHoveredThisFrame = false;
  bool isHoveredLastFrame = false;

private:



  //does the object exist in world space or exist in the UI Screen space




};



namespace UIDefault
{
  inline void _OnHoverStart(UIElement& element)
  {
    element.tempColor = Color.Red;
  }
  inline void _OnHover(UIElement& element)
  {

  }
  inline void _OnHoverEnd(UIElement& element)
  {

  }
  inline void _OnClick(UIElement& element)
  {

  }
}
