#pragma once

enum class Need
{
  Hunger,
  Sleep,
  Work,
  Joy
};

/*
 The goal is that while the utility object doesn't have needs to be met and 
isnt currently moving to meet those needs the object is working and doing something
else but when it needs to fufill its needs it instantly (or finishes a task and then)
goes to fufill the need then back to work.

jobs should have a priority and workers should have jobs
such as mining, building, crafting, etc

what if they are given a task by the game of stuff asked to do and if its
their type of job they work on that thing next until its done then proceed
down the list.

if they work on a job they take it "off the list" so other workers dont do it OR
other works can help them on it? (maybe make it recurring job until its complete. 
 */
/*
enum class Work
{
  Mine,
  YourJobHere,
};
*/

struct NeedData
{
  float min = 0;
  float max = 1;
  float currentValue = 1;
  float decay = 0.001f; //on each update currentValue -= dt * speed
  float setCooldown = 10.0f;
  float currentCooldown = 0.0;
};

struct FufillmentData
{
  float fulfillment = 1;
  float useTime = 0;
};