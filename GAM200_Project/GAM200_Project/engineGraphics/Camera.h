#include "Shader.h"

//This controls the coordinate range 
//Basically works the same way as zoom. 
//The purpose of this is to keep zom in reasonable values 
#define SCENESCALE 2.0f

class Camera
{
public:
  Camera();
  Camera(Shader intendedShader);
  ~Camera();

  float zoom;
  void move(glm::vec3 translation);

  void update();

private:
  Shader shader;
  glm::vec3 worldUp;
  glm::vec3 cameraPosition;
  glm::vec3 cameraTarget;
};

