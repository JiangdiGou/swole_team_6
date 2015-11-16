/*****************************************************************************/
/*!
\file    graphicsManager.h
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  Interface of the graphics manager, which is in charge of handling most main
  graphical systems
\remarks 
  

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H


#include "../Engine.h"
#include "Shader.h"
#include "debugDraw.h"
#include "Graphics.h"
#include "SpriteText.h"
#include "FramerateController.h"
#include "Sprite.h"
#include "textureAtlas.h"
#include "../logger/logger.h"
#include "Camera.h"
#include "../GameLogic.h"
#include "../initInfo.h"

class GraphicsManager : public ISystem
{
  friend class Shader;

public:
  GraphicsManager(const Shader& coreShader);
  ~GraphicsManager();

  void Initialize()  override;
  void Update(float dt) override;
  void Draw() override;

  void setDeviceContext(HDC& newDeviceContext);
  HDC getDeviceContext();
  void setRenderingContext(HGLRC& renderingContext);
  HGLRC getRenderingContext();

  void setMainCamera(Camera* camera){ mainCamera = camera; }
  Camera* getCamera(){ return mainCamera; }
  void setCoreShader(const Shader& shader) { coreShader = shader; }
  Shader* getCoreShader() { return &coreShader; }
  void setSpriteAtlas(TextureAtlas* atlas) { spriteAtlas = atlas; }
  TextureAtlas* getSpriteAtlas() { return spriteAtlas; }
	void setWindow(GLFWwindow* inputWindow) { pWindow = inputWindow; }

  Vector2 screenToWorld(Vector2 screenCoords);

private:
  HDC deviceContext;
  HGLRC renderingContext;
	GLFWwindow* pWindow;
  Camera* mainCamera;
  TextureAtlas* spriteAtlas;
  Shader coreShader;

};

extern GraphicsManager *GRAPHICS;

#endif 
