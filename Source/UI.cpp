#include "pch.h"


void UIDefault::OnHoverStart(UIElement& element)
{
  element.color = Color.Red;
}

void UIDefault::OnHover(UIElement& element)
{
  element.color = Color.Blue;
}

void UIDefault::OnHoverEnd(UIElement& element)
{
  element.color = glm::vec4(0,0,0,1);
}

void UIDefault::OnClick(UIElement& element)
{
  element.tempColor = Color.Yellow;
}

void UIDefault::OnUpdate(UIElement& element)
{
  //empty so it does nothing
}

void UIJob::OnUpdate(UIElement& element)
{
  
}

void UIElementAnchor::Update()
{
  glm::vec2 position = parent->GetComponent<Transform>()->GetTranslation();
  glm::vec2 scale = parent->GetComponent<Transform>()->GetScale();

  //undo the current offset change
  position -= anchorOffset + offsetAfterAnchor;


  //update the current offset 
  if(horizontalAnchor == HorizontalAnchor::Left)
  {
    anchorOffset.x = position.x - scale.x;
  }
  else if(horizontalAnchor == HorizontalAnchor::Right)
  {
    anchorOffset.x = position.x + scale.x;
  }
  else if (horizontalAnchor == HorizontalAnchor::Center)
  {
    anchorOffset.x = position.x;
  }

  if (verticalAnchor == VerticalAnchor::Bottom)
  {
    anchorOffset.y = position.y - scale.y;
  }
  else if (verticalAnchor == VerticalAnchor::Top)
  {
    anchorOffset.y = position.y + scale.y;
  }
  else if (verticalAnchor == VerticalAnchor::Center)
  {
    anchorOffset.y = position.y;
  }

  //apply the new offset
  position += anchorOffset + offsetAfterAnchor;

}

UIElement::UIElement(glm::vec2 position_, glm::vec2 scale_, bool worldSpace) : GameObject()
{
  GetComponent<Transform>()->SetScale(scale_);
  GetComponent<Transform>()->SetTranslation(position_);
  worldSpaceObject = worldSpace;
}

bool UIElement::isHovered(glm::vec2 worldMousePosition)
{
  glm::mat4 transform = GetMatrix();
  //remember in homogeneous so need x,y,z,1


  //I have the position in world space
  //the scale in local object space
  //the position of the mouse in world space 
  glm::vec4 center = transform * (glm::vec4(GetComponent<Transform>()->GetTranslation(), 0, 1));
  glm::vec4 scale = transform * (glm::vec4(GetComponent<Transform>()->GetScale(), 0, 0));


  //this gets the world position of the center of this object and using the 
  //world position of the mouse can easily solve this

  return(PointContainment2D::AABBPointWithinSquare(center, scale, worldMousePosition));
  
}

void UIElement::Update(float dt)
{
  anchor.Update();
  GameObject::Update(dt);





  if(worldSpaceObject)
  {
    isHoveredThisFrame = isHovered(engine.GetSystem<InputManager>()->mouseWorldCoords);
  }
  else
  {
    isHoveredThisFrame = isHovered(engine.GetSystem<InputManager>()->mouseScreenCoords);
  }

  //TODO and if mouseButton is down
  //TODO actual input manager lol
  //if(isHoveredThisFrame && engine.GetSystem<InputManager>().mouse)
  //just hovered
  if(isHoveredThisFrame && !isHoveredLastFrame)
  {
    OnHoverStart(*this);
  }
  else if (isHoveredThisFrame && isHoveredLastFrame)
  {
    OnHover(*this);
  }
  else if (!isHoveredThisFrame && isHoveredLastFrame)
  {
    OnHoverEnd(*this);
  }

  isHoveredLastFrame = isHoveredThisFrame;

}
