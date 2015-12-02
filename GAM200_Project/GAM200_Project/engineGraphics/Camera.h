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
#include "../GameLogic/GameLogic.h"
#include "../Composition.h"
#include "../physicsLib/Transform.h"
#include "../initInfo.h" //W and H
#include "../WindowsSystem.h" //Messages 
#include "../Zilch/BindInternal.hpp"
#include "../Zilch/Zilch.hpp"

using namespace Zilch;

class Camera : public GameComponent
{
public:
  ZilchDeclareDerivedType(Camera, GameComponent);
  Camera(); 
  Camera(const Shader& shader);
  ~Camera();

  float zoom = 0.1f;
  void move(glm::vec3 translation);

  void Initialize() override;
  void Update(float dt) override;
  void SendMessages(Message* message) override;

  void SerializeRead(Serializer& str) override;
  void SerializeWrite(Serializer& str) override;

  bool followingPlayer = true;
  bool editorMode = false;

  float getSize() { return size; }

  void setCameraSize(float newSize)
  {
    size = newSize;
    Update(0.0f);
  }

  float getWidth() { return width; }
  float getHeight() { return height; }

  Vector3 getPosition()
  {
    return pTransform->GetPosition();
  }

  void SetPosition(Vector3 in)
  {
    pTransform->SetPosition(in);
  }

private:
  Transform* pTransform;

  float size = 1000.0f;
  float editorMoveSpeed = 0.15;

  float width;
  float height;

  glm::vec3 worldUp;
  glm::vec3 cameraTarget;

  GLuint shaderID;
  GLuint viewLocation;
  GLuint projectionLocation;
};

#endif
