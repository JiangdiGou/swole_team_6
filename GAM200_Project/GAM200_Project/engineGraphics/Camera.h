#ifndef CAMERA_H
#define CAMERA_H

#include "Shader.h"
#include "../GameLogic.h"
#include "../Composition.h"
#include "../physicsLib/Transform.h"
#include "../initInfo.h"

class Camera : public GameComponent 
{
public:
  Camera(); 
  Camera(const Shader& shader);
  ~Camera();

  float zoom;
  void move(glm::vec3 translation);

  void Update(float dt) override;

  bool followingPlayer = true;

  void SendMessages(Message*) override {};

private:
  glm::vec3 worldUp;
  glm::vec3 cameraPosition;
  glm::vec3 cameraTarget;

  GLuint shaderID;
  GLuint viewLocation;
  GLuint projectionLocation;
};


#endif
