/*****************************************************************************/
/*!
\file    graphicsManager.cpp
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  Implementation of the graphics manager, which is in charge of handling most
  main graphical systems
\remarks 
  

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#include "graphicsManager.h"'
#include "../Editor/Defines.h"

GraphicsManager *GRAPHICS;

GraphicsManager::GraphicsManager(const Shader& shader)
{
#ifdef GFXLOG
  gfxErrorLog = new txtlog("graphicsLog.txt");
  gfxErrorLog->write("STARTLOG -- GRAPHICS MANAGER CONSTRUCTED -- STARTLOG");
#endif

  //Flush out the error
  glGetError();
  spriteAtlas = new TextureAtlas("resources/Textures/Atlas/testAtlas.png",
    ("resources/Textures/tList_testAtlas.txt"));
#ifdef GFXLOG
  logGfxError("TEXTUREATLAS:: Error in texture Atlas construction. ");
#endif

  Texture * courier = new Texture("resources/fonts/courier.png", 1, 43, 83, 0);

  initDebugDraw(shader);

#ifdef GFXLOG
  logGfxError("DEBUGDRAW:: Error in initialization. ");
#endif

  Sprite::initSprites(shader, spriteAtlas);


#ifdef GFXLOG
  logGfxError("SPRITE:: Error in initialization. ");
#endif

  SpriteText::initText(shader, courier);

#ifdef GFXLOG
  logGfxError("SPRITETEXT:: Error in initialization. ");
#endif

  GRAPHICS = this;
  coreShader = shader;
  shader.Use();

}

void GraphicsManager::Update(float dt)
{
#ifndef EDITOR
  glfwPollEvents();
#endif

  coreShader.Use();


  if (usingGameBackground)
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
  else
    glClearColor(menuColor.x, menuColor.y, menuColor.z, menuColor.w);

  glClear(GL_COLOR_BUFFER_BIT);

  //wglMakeCurrent(deviceContext, renderingContext);
	glfwMakeContextCurrent(pWindow);

  //std::string fTime = std::to_string((int)(1000.0f / (float)FramerateController::getPreviousDt()));
  //SpriteText::renderText(fTime, Vector3(0, 0, 0), Vector3(0.15, 0.25, 1));

  //Transform* playerTransform = LOGIC->player->has(Transform)
  //if (playerTransform)
	//  debugDrawCircle(playerTransform->GetPosition(), 1, Vector3(), 100);

  debugDrawFrame();
#ifdef GFXLOG
  logGfxError("DEBUGDRAW:: Error in drawing. ");
#endif


  Sprite::drawAllSprites();
#ifdef GFXLOG
  logGfxError("SPRITE:: Error in drawing. ");
#endif

  SpriteText::drawAllText();
#ifdef GFXLOG
  logGfxError("SPRITETEXT:: Error in drawing. ");
#endif


  //Cleanup 
  glBindVertexArray(0);
  glUseProgram(0);
}

void GraphicsManager::Draw()
{
  glfwSwapBuffers(pWindow);
  FramerateController::frameEnd();

#ifdef GFXLOG
  ++frameNumber;
  if (FramerateController::getPreviousDt() > WARNINGFRAMETIME && frameNumber > STARTUPFRAMES)
  {
    std::string dt = std::to_string(FramerateController::getPreviousDt());
    std::string message = std::string("FRAMERATECONTROLLER:: Abnormally high frame time ");
    message.append(dt); 
    gfxErrorLog->write(message);
  }

  if (frameNumber > STARTUPFRAMES)
    logGfxError("Uncaught Error. ");

  //Clears errors out, handles some edge cases and otherwise has no effect on functionality
  glGetError(); 
#endif
}

void GraphicsManager::setDeviceContext(HDC& newDeviceContext)
{
  deviceContext = newDeviceContext;
}

HDC GraphicsManager::getDeviceContext()
{
  return deviceContext;
}

void GraphicsManager::setRenderingContext(HGLRC& newRenderingContext)
{
  renderingContext = newRenderingContext;
}

HGLRC GraphicsManager::getRenderingContext()
{
  return renderingContext;
}

void GraphicsManager::Initialize()
{
  glDepthFunc(GL_ALWAYS);
}

GraphicsManager::~GraphicsManager()
{
  //wgldeletecontext of context
}

Vector2 GraphicsManager::screenToWorld(const Vector2& screenCoords)
{
  Vector2 worldCoords = screenCoords;

  worldCoords.x = worldCoords.x - 0.5*windowWidth;
  worldCoords.y = 0.5*windowHeight - worldCoords.y;

  //x2 here because the camera is -initInfo to initInfo, so its really like 2 initInfo
  worldCoords.x = worldCoords.x * (mainCamera->getWidth() / windowWidth);
  worldCoords.y = worldCoords.y * (mainCamera->getHeight() / windowHeight);

  //Player transform cause thats where the camera is centered
  Vector2 cameraXY = Vector2(mainCamera->getPosition().x, mainCamera->getPosition().y);
  return worldCoords + cameraXY;
}
