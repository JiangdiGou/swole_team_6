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

  void setMainCamera(Camera* camera){ mainCamera = *camera; }
  Camera* getCamera(){ return &mainCamera; }
  void setCoreShader(const Shader& shader) { coreShader = shader; }
  Shader* getCoreShader() { return &coreShader; }
  void setSpriteAtlas(const TextureAtlas& atlas) { spriteAtlas = atlas; }
  TextureAtlas* getSpriteAtlas() { return &spriteAtlas; }

private:
  HDC deviceContext;
  HGLRC renderingContext;
  Camera mainCamera;
  TextureAtlas spriteAtlas;
  Shader coreShader;

};

extern GraphicsManager *GRAPHICS;

#endif 