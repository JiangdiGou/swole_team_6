/*****************************************************************************/
/*!
\file    Camera.cpp
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  Implementation of our game's camera
\remarks 


All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#include "Camera.h"
#include "../Editor/Defines.h"

//DO NOT USE. It was bitching at me for no default
Camera::Camera()
{
}

//**********************
//Function    : Camera
//Input       : none
//Output      : Camera - the constructed Camera
//Description : The constructor you should use to make a camera. 
//**********************
Camera::Camera(const Shader& shader)
{
  cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
  worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

  shaderID = shader.Program;

  projectionLocation = glGetUniformLocation(shaderID, "uniformProjection");

  //Gets the location of the view matrix uniform and sends it to the shader. 
  viewLocation = glGetUniformLocation(shaderID, "uniformView");

  width = (2.0f * windowWidth) / (size * zoom);
  height = (2.0f * windowHeight) / (size * zoom);
}

void Camera::Initialize()
{
  GOC* owner = GetOwner();
  pTransform = owner->has(Transform);
  pTransform->SetPosition(0.0f, 0.0f, 2.0);
}
void Camera::SerializeRead(Serializer& str)
{
  /*
  StreamRead(str, size);
  StreamRead(str, width);
  StreamRead(str, height);
  */
}
void Camera::SerializeWrite(Serializer& str)
{ 
  /*
  StreamWrite(str, (int&)TypeId);
  StreamWrite(str);
  StreamWrite(str, size);
  StreamWrite(str);
  StreamWrite(str, width);
  StreamWrite(str);
  StreamWrite(str, height);
  StreamWrite(str);
  */
}

//**********************
//Function    : ~Camera
//Input       : none
//Output      : none
//Description : Destructor for camera, does nothing 
//**********************
Camera::~Camera()
{
}

//**********************
//Function    : Camera.update
//Input       : none
//Output      : none
//Description : Sends the camera information to te shader. 
//**********************
void Camera::Update(float dt)
{
  Vector3 currentPos = pTransform->GetPosition();
  glUseProgram(shaderID);

  if (followingPlayer)
  {
    Transform* playerTransform = LOGIC->player->has(Transform);
    glm::vec3 newPosition = glm::vec3(playerTransform->GetPosition().x,
      playerTransform->GetPosition().y, currentPos.z);
    glm::vec3 newTarget = glm::vec3(playerTransform->GetPosition().x,
      playerTransform->GetPosition().y, playerTransform->GetPosition().z);

    pTransform->SetPosition(Vector3(newPosition.x, newPosition.y, newPosition.z));
    cameraTarget = newTarget;
  }

  //Gets the Aspect Ratio of the Window to set up the camera's coordinates 
  float ratio = windowWidth / windowHeight;

  //Gets the Orthographic Projection Matrix 
  glm::mat4 projectionMatrix;
  //Left, Right, Bottom, Top, Near, Far
  //This random magic 1000.0f is just to make everything have a reasonable value
  projectionMatrix = glm::ortho((float)-windowWidth / (size * zoom),
                                (float)windowWidth / (size * zoom),
                                (float)-windowHeight / (size * zoom),
                                (float)windowHeight / (size * zoom),
                                -1.0f, 5.0f);

  //Gets the view matrix 
  glm::mat4 viewMatrix;


  glm::vec3 glmCurrenPos = glm::vec3(currentPos.x, currentPos.y, currentPos.z);
  viewMatrix = glm::lookAt(glmCurrenPos, cameraTarget, worldUp);

  glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
  glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

//**********************
//Function    : Camera.move
//Input       : none
//Output      : none
//Description : moves the camera and its target so its still looking at the 
//              2d plane
//**********************
void Camera::SendMessages(Message* message)
{
  if (editorMode)
  {
    switch (message->MessageId)
    {
    case Mid::CharacterKey:
    {

      MessageCharacterKey* keyEvent = (MessageCharacterKey*)message;

      switch (keyEvent->character)
      {
      case 'W' :
      {
        pTransform->SetPosition(pTransform->GetPosition() + Vector3(0, editorMoveSpeed, 0));
        cameraTarget += glm::vec3(0, editorMoveSpeed, 0);
        break;
      }
      case 'A':
      {
        pTransform->SetPosition(pTransform->GetPosition() - Vector3(editorMoveSpeed, 0, 0));
        cameraTarget -= glm::vec3(editorMoveSpeed, 0, 0);
        break;
      }
      case 'S':
      {
        pTransform->SetPosition(pTransform->GetPosition() - Vector3(0, editorMoveSpeed, 0));
        cameraTarget -= glm::vec3(0, editorMoveSpeed, 0);
        break;
      }
      case 'D':
      {
        pTransform->SetPosition(pTransform->GetPosition() + Vector3(editorMoveSpeed, 0, 0));
        cameraTarget += glm::vec3(editorMoveSpeed, 0, 0);
        break;
      }
      }
    }
    }
  }
}

ZilchDefineType(Camera, "Camera", ZLib_Internal, builder, type)
{
  type->HandleManager = ZilchManagerId(PointerManager);
  ZilchBindConstructor(builder, type, Camera, ZilchNoNames);
  ZilchBindDestructor(builder, type, Camera);

  ZilchBindProperty(builder, type, &Camera::getSize, &Camera::setCameraSize, "CamSize");
  ZilchBindProperty(builder, type, &Camera::getPosition, &Camera::SetPosition, "Position");

  ZilchBindMethod(builder, type, &Camera::getWidth, ZilchNoOverload, "getWidth", ZilchNoNames);
  ZilchBindMethod(builder, type, &Camera::getHeight, ZilchNoOverload, "getHeight", ZilchNoNames);

  ZilchBindField(builder, type, &Camera::zoom, "zoom", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Camera::followingPlayer, "followingPlayer", PropertyBinding::GetSet);
}