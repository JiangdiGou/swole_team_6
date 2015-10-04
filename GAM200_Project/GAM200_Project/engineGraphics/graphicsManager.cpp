#include "graphicsManager.h"

GraphicsManager *graphics;

void GraphicsManager::InitWMCreate(HWND window)
{
  
}

GraphicsManager::GraphicsManager(Shader& textShader, Shader& debugShader)
{
  graphics = this;
  coreShader = &debugShader;
  initDebugDraw(debugShader);

  Texture * courier = new Texture("resources/courier.png", 1, 43, 83, 0);

  SpriteText::initText(&debugShader, courier);

  debugShader.Use();
}

void GraphicsManager::Update(float dt)
{
  wglMakeCurrent(deviceContext, renderingContext);
  glClearColor(0.9f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  debugDrawFrame();
  SpriteText::drawAllText();
}

void GraphicsManager::Draw()
{
  SwapBuffers(deviceContext);
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
  glDepthFunc(GL_NEVER);
}

GraphicsManager::~GraphicsManager()
{
  //wgldeletecontext of context
}
