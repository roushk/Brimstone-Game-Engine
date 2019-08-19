#include "pch.h"



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
  GameObject::Update(dt);
  
  isHoveredThisFrame = isHovered(engine.GetSystem<InputManager>()->mouseWorldCoords);


  //TODO and if mouseButton is down
  //TODO actual input manager lol
  //if(isHoveredThisFrame && engine.GetSystem<InputManager>().mouse)
  //just hovered
  if(isHoveredThisFrame && !isHoveredLastFrame)
  {
    OnHoverStart();
  }
  else if (isHoveredThisFrame && isHoveredLastFrame)
  {
    OnHover();
  }
  else if (!isHoveredThisFrame && isHoveredLastFrame)
  {
    OnHoverEnd();
  }

  isHoveredLastFrame = isHoveredThisFrame;
}
