/*****************************************************************************/
/*!
\file       Camera.h
\author  Conor Lavelle
\par        Contact: c.lavelle@digipen.edu
\brief 
     Interface of our game's camera
\remarks 
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
/*****************************************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#include "Shader.h"
#include "../GameLogic.h"
#include "../Composition.h"
#include "../physicsLib/Transform.h"
#include "../initInfo.h" //W and H
#include "../WindowsSystem.h" //Messages 

class Camera : public GameComponent 
{
public:
  Camera(); 
  Camera(const Shader& shader);
  ~Camera();

  float zoom = 0.25f;
  void move(glm::vec3 translation);

  void Update(float dt) override;

  void SerializeRead(Serializer& str) override;

  void SerializeWrite(Serializer& str) override;

  void SendMessages(Message* message) override;

  bool followingPlayer = true;
  bool editorMode = false;

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
  float editorMoveSpeed = 0.15;

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
