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
  coreShader->Use();
  wglMakeCurrent(deviceContext, renderingContext);
  glClearColor(0.9f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  debugDrawFrame();
  SpriteText::renderText(std::string("Frame\nTime: "), Vector3(-3.25, -1.0, 0), Vector3(0.25, 0.45, 1));
  std::string fTime = std::to_string(FramerateController::getPreviousDt());
  SpriteText::renderText(fTime, Vector3(-2, -1.45, 0), Vector3(0.25, 0.45, 1));

  SpriteText::drawAllText();
  glBindVertexArray(0);
  glUseProgram(0);
}

void GraphicsManager::Draw()
{
  SwapBuffers(deviceContext);
  FramerateController::frameEnd();
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
