#include "Camera.h"

//**********************
//Function    : Camera
//Input       : none
//Output      : Camera - the constructed Camera
//Description : Default Constructor for camera, does nothing
//**********************
Camera::Camera()
{
  std::cout << "Camera::This default constructor does nothing." << std::endl;
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
//Function    : Camera
//Input       : intendedShader - the shader you intend to use with this camera
//Output      : Camera - the constructed Camera
//Description : The constructor you should use to make a camera. 
//**********************
Camera::Camera(Shader intendedShader)
{
  zoom = 1.0f;

  cameraPosition = glm::vec3(0.0f, 0.0f, 2.0);
  cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
  worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
  shader = intendedShader;
}

//**********************
//Function    : Camera.update
//Input       : none
//Output      : none
//Description : Sends the camera information to te shader. 
//**********************
void Camera::update()
{
  //Gets the Aspect Ratio of the Window to set up the camera's coordinates 
  float ratio = (float)WINDOWWIDTH / (float)WINDOWHEIGHT;

  //Gets the Orthographic Projection Matrix 
  glm::mat4 projectionMatrix;
  projectionMatrix = glm::ortho((-ratio / zoom)*SCENESCALE, (ratio / zoom)*SCENESCALE, 
                                (-1.0f / zoom)*SCENESCALE, (1.0f / zoom)*SCENESCALE,
                                0.1f, 5.0f);

  //Gets the location of the projection matrix uniform then sends it to the shader 
  GLuint projectionLocation = glGetUniformLocation(shader.Program, "uniformProjection");
  glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
  
  //Gets the view matrix 
  glm::mat4 viewMatrix;
  viewMatrix = glm::lookAt(cameraPosition, cameraTarget, worldUp);
  
  //Gets the location of the view matrix uniform and sends it to the shader. 
  GLuint viewLocation = glGetUniformLocation(shader.Program, "uniformView");
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