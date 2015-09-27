#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "../Engine.h"
#include "Shader.h"
#include "debugDraw.h"
#include "text.h"
#include "Graphics.h"


class GraphicsManager : public ISystem
{
  friend class Shader;
  friend class DebugDraw;

public:
  GraphicsManager(Shader textShader, Shader debugShader);
  ~GraphicsManager();

  void Initialize()  override;
  void Update(float dt) override;
  void Draw();

  void InitWMCreate(HWND window);

  void setDeviceContext(HDC newDeviceContext);
  HDC getDeviceContext();
  void setRenderingContext(HGLRC renderingContext);
  HGLRC getRenderingContext();

private:
  HDC deviceContext;
  HGLRC renderingContext;

  Shader* coreShader;

};

extern GraphicsManager *graphics;

#endif 