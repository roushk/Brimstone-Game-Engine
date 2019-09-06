#pragma once

#include <functional>

//TODO is a variable member function even a thing without having to add each func to the class???

class UIElement;
namespace UIDefault
{
  void OnHoverStart(UIElement& element);
  void OnHover(UIElement& element);
  void OnHoverEnd(UIElement& element);
  void OnClick(UIElement& element);
  void OnUpdate(UIElement& element);

}

namespace UIJob
{
  void OnUpdate(UIElement& element);
}

/*
 The goal of the anchor class is to be able to anchor the object around a position
so that when it is scaled it doesnt just shrink the object on "both" sides

for example like moving loading bars, this would allow the anchor to be set to "left"
and increasing the scale looks like the bar is increase only on the right side but
in reality its being recentered and scaled not just scaled
 */
class UIElementAnchor
{

  
public:
  enum class HorizontalAnchor
  {
    Left,
    Center,
    Right,
  };
  enum class VerticalAnchor
  {
    Top,
    Center,
    Bottom,
  };
  HorizontalAnchor horizontalAnchor = HorizontalAnchor::Center;
  VerticalAnchor verticalAnchor = VerticalAnchor::Center;

  UIElementAnchor(UIElement* parent_)
  {
    parent = parent_;
  }

  //set once for the object
  //the object's offset is take off and reapplied on a change so when the object is moved
  //the offset is kept

  //a tertiary offset vector if the anchor is not enough
  glm::vec2 offsetAfterAnchor{ 0,0 };

  //the base anchor offset that is set based off of the halfway of the size of the object
  //along with the center of it
  glm::vec2 anchorOffset{ 0,0 };

  void Update();
  UIElement * parent = nullptr;

};


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

  /*
   TODO:
  Preferably want to send in data as variadic or using std::forward
  the goal is to pass any number of arguments to the OnX functions
  and based on the function it will take the data that it needs.
  
  template<class ArgumentData>
  void foo(ArgumentData&& arg)
  {
    OnClick(std::forward<ArgumentData>(arg));
  }


   */
  //called once, the frame the object is clicked
  


  std::function<void(UIElement&)> OnClick = UIDefault::OnClick;

  //only called once
  std::function<void(UIElement&)> OnHoverStart = UIDefault::OnHoverStart;

  //called every frame after the first the object is hovered
  std::function<void(UIElement&)> OnHover = UIDefault::OnHover;

  //called the frame after object is no longer hovered 
  std::function<void(UIElement&)> OnHoverEnd = UIDefault::OnHoverEnd;


  //called once, the frame the object is clicked
  std::function<void(UIElement&)> OnUpdate = UIDefault::OnUpdate;

  bool buttom = false;
  glm::vec2 buttonClickOffset = glm::vec2(0);


  bool isHoveredThisFrame = false;
  bool isHoveredLastFrame = false;

  //is an offset for the object
  //can anchor it to an offset of its current position 
  //not quite an anchor where it stays but close, more like an offset
  //to the current position
  UIElementAnchor anchor = UIElementAnchor(this);

  
  
  
private:



  //does the object exist in world space or exist in the UI Screen space


  

};


