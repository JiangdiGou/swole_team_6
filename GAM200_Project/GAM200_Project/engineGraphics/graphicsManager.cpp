#include "graphicsManager.h"

GraphicsManager *graphics = nullptr;

void GraphicsManager::InitWMCreate(HWND window)
{
  
}

GraphicsManager::GraphicsManager(Shader textShader, Shader debugShader)
{
  Text::initText(textShader);
  initDebugDraw(debugShader);

  debugShader.Use();
}

void GraphicsManager::Update(float dt)
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsManager::Draw()
{
  SwapBuffers(deviceContext);
}

void GraphicsManager::setDeviceContext(HDC newDeviceContext)
{
  deviceContext = newDeviceContext;
}

HDC GraphicsManager::getDeviceContext()
{
  return deviceContext;
}

void GraphicsManager::setRenderingContext(HGLRC newRenderingContext)
{
  renderingContext = newRenderingContext;
}

HGLRC GraphicsManager::getRenderingContext()
{
  return renderingContext;
}

void GraphicsManager::Initialize()
{

}

GraphicsManager::~GraphicsManager()
{
  //wgldeletecontext of context
}
