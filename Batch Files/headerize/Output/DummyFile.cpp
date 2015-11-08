/*****************************************************************************/
/*!
\file    DummyFile.cpp
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  The quick brown fox jumped over the lazy dog. The quick brown fox jumped
  over the lazy dog. The quick brown fox jumped over the lazy dog. The
  quick brown fox jumped over the lazy dog. The quick brown fox jumped
  over the lazy dog. The quick brown fox jumped over the lazy dog. The
  quick brown fox jumped over the lazy dog. 
\remarks 
  I'm gonna throw in some extra words here to offset the remarks section from
  the other section to test more The quick brown fox jumped over the lazy
  dog. The quick brown fox jumped over the lazy dog. The quick brown fox
  jumped over the lazy dog. The quick brown fox jumped over the lazy dog.
  The quick brown fox jumped over the lazy dog. The quick brown fox jumped
  over the lazy dog. The quick brown fox jumped over the lazy dog. 

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~

#include "Camera.h"

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
  cameraPosition = glm::vec3(0.0f, 0.0f, 2.0);
  cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
  worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

  shaderID = shader.Program;

  projectionLocation = glGetUniformLocation(shaderID, "uniformProjection");

  //Gets the location of the view matrix uniform and sends it to the shader. 
  viewLocation = glGetUniformLocation(shaderID, "uniformView");

  width = (2.0f * INITINFO->clientWidth) / (size * zoom);
  height = (2.0f * INITINFO->clientHeight) / (size * zoom);
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
  glUseProgram(shaderID);

  if (followingPlayer)
  {
    Transform* playerTransform = LOGIC->player->has(Transform);
    glm::vec3 newPosition = glm::vec3(playerTransform->GetPosition().x,
      playerTransform->GetPosition().y, cameraPosition.z);
    glm::vec3 newTarget = glm::vec3(playerTransform->GetPosition().x,
      playerTransform->GetPosition().y, playerTransform->GetPosition().z);

    cameraPosition = newPosition;
    cameraTarget = newTarget;
  }

  //Gets the Aspect Ratio of the Window to set up the camera's coordinates 
  float ratio = (float)INITINFO->clientWidth / (float)INITINFO->clientWidth;

  //Gets the Orthographic Projection Matrix 
  glm::mat4 projectionMatrix;
  //Left, Right, Bottom, Top, Near, Far
  //This random magic 1000.0f is just to make everything have a reasonable value
  projectionMatrix = glm::ortho((float)-INITINFO->clientWidth / (size * zoom),
                                (float)INITINFO->clientWidth / (size * zoom),
                                (float)-INITINFO->clientHeight / (size * zoom),
                                (float)INITINFO->clientHeight / (size * zoom),
                                0.1f, 5.0f);

  //Gets the view matrix 
  glm::mat4 viewMatrix;
  viewMatrix = glm::lookAt(cameraPosition, cameraTarget, worldUp);

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
void Camera::move(glm::vec3 translation)
{
  cameraPosition += translation;
  cameraTarget += translation;
}
