#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "../Engine.h"
#include "Shader.h"
#include "debugDraw.h"
#include "Graphics.h"
#include "SpriteText.h"
#include "FramerateController.h"


class GraphicsManager : public ISystem
{
  friend class Shader;
  friend class DebugDraw;

public:
  GraphicsManager(Shader& textShader, Shader& debugShader);
  ~GraphicsManager();

  void Initialize()  override;
  void Update(float dt) override;
  void Draw() override;

  void InitWMCreate(HWND window);

  void setDeviceContext(HDC& newDeviceContext);
  HDC getDeviceContext();
  void setRenderingContext(HGLRC& renderingContext);
  HGLRC getRenderingContext();
  Shader* coreShader;

private:
  HDC deviceContext;
  HGLRC renderingContext;

};

extern GraphicsManager *graphics;

#endif 