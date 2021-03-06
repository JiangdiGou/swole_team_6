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
#include "../GameLogic/GameLogic.h"
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

  Vector2 screenToWorld(const Vector2& screenCoords);
  void toggleBackground(bool gameBackground)
  {
    usingGameBackground = gameBackground;
  }


private:
  HDC deviceContext;
  HGLRC renderingContext;
	GLFWwindow* pWindow;
  Camera* mainCamera;
  TextureAtlas* spriteAtlas;
  Shader coreShader;

  bool usingGameBackground = true;

  glm::vec4 menuColor = glm::vec4(0.15f, 0.15f, 0.15f, 1.0f);
  glm::vec4 backgroundColor = glm::vec4(0.3f, 0.1f, 0.3f, 1.0f);

};

extern GraphicsManager *GRAPHICS;

#endif 
