#include "Testing.h"

//Vars for transformation/color tests
bool testScalingGrowing = true;
bool testTranslateUp = true;
bool testColorBlue = true;


void testColor(Sprite &sprite)
{
  if (testColorBlue)
  {
    //Color is weird. It's not RGBA like you would expect. I'll look into it more later. 
    //Looks like its G, B, A, R. No freakin idea why. 
    sprite.color -= glm::vec4(0.00f, 0.00f, 0.00f, 0.01f);
    if (sprite.color.w <= 0)
      testColorBlue = false;
  }
  else
  {
    sprite.color += glm::vec4(0.0f, 0.00f, 0.0f, 0.01f);
    if (sprite.color.w >= 1.25)
      testColorBlue = true;
  }
}
