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

  float zoom = 0.25f;
  void move(glm::vec3 translation);

  void Update(float dt) override;

  bool followingPlayer = true;

  void SendMessages(Message*) override {};

  glm::vec3 getPosition() { return cameraPosition; }

  float getSize() { return size; }

  void setCameraSize(float newSize)
  {
    size = newSize;
    Update(0.0f);
  }

  float getWidth() { return width; }
  float getHeight() { return height; }

private:
  float size = 1000.0f;

  float width;
  float height;

  glm::vec3 worldUp;
  glm::vec3 cameraPosition;
  glm::vec3 cameraTarget;

  GLuint shaderID;
  GLuint viewLocation;
  GLuint projectionLocation;
};

#endif
