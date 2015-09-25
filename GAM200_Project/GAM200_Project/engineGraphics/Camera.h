#ifndef CAMERA_H
#define CAMERA_H

#include "Shader.h"
#include "../Composition.h"

//This controls the coordinate range 
//Basically works the same way as zoom. 
//The purpose of this is to keep zom in reasonable values 
#define SCENESCALE 2.0f

class Camera : public GameComponent 
{
public:
  Camera();
  ~Camera();

  float zoom;
  void move(glm::vec3 translation);

  void Update() override;

private:
  glm::vec3 worldUp;
  glm::vec3 cameraPosition;
  glm::vec3 cameraTarget;
};


#endif
