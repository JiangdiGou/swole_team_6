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

  void setMainCamera(const Camera& camera);
  Camera* getCamera();
  void setCoreShader(const Shader& shader);
  Shader* getCoreShader();
  void setSpriteAtlas(const TextureAtlas& atlas);
  TextureAtlas* getSpriteAtlas();

private:
  HDC deviceContext;
  HGLRC renderingContext;
  Camera mainCamera;
  TextureAtlas spriteAtlas;
  Shader coreShader;

};

extern GraphicsManager *GRAPHICS;

#endif 