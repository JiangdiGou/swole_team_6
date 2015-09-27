#include "Testing.h"

//Vars for transformation/color tests
bool testScalingGrowing = true;
bool testTranslateUp = true;
bool testColorBlue = true;
//
//void testScaling(Sprite &sprite)
//{
//  if (testScalingGrowing)
//  {
//    sprite.scale += glm::vec3(0.01f, 0.01f, 0.01f);
//    if (sprite.scale.x > 1.5f)
//      testScalingGrowing = false;
//  }
//  else
//  {
//    sprite.scale -= glm::vec3(0.01f, 0.01f, 0.01f);
//    if (sprite.scale.x < 0.025f)
//      testScalingGrowing = true;
//  }
//}
//
//void testRotation(Sprite &sprite)
//{
//  sprite.rotation += .05;
//}
//
//void testTranslate(Sprite &sprite)
//{
//  if (testTranslateUp)
//  {
//    sprite.translation += glm::vec3(0.0f, 0.005f, 0.0f);
//    if (sprite.translation.y > 0.75)
//      testTranslateUp = false;
//  }
//  else
//  {
//    sprite.translation -= glm::vec3(0.0f, 0.005f, 0.0f);
//    if (sprite.translation.y < -0.75)
//      testTranslateUp = true;
//  }
//
//}
//
//void testColor(Sprite &sprite)
//{
//  if (testColorBlue)
//  {
//    //Color is weird. It's not RGBA like you would expect. I'll look into it more later. 
//    //Looks like its G, B, A, R. No freakin idea why. 
//    sprite.color -= glm::vec4(0.00f, 0.00f, 0.00f, 0.01f);
//    if (sprite.color.w <= 0)
//      testColorBlue = false;
//  }
//  else
//  {
//    sprite.color += glm::vec4(0.0f, 0.00f, 0.0f, 0.01f);
//    if (sprite.color.w >= 1.25)
//      testColorBlue = true;
//  }
//}
