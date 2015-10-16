#include "graphicsManager.h"

GraphicsManager *graphics;

GraphicsManager::GraphicsManager(const Shader& shader)
{
  spriteAtlas = *(new TextureAtlas("resources/Textures/Atlas/testAtlas.png", 
                                  "resources/Textures/tList_testAtlas.txt"));
  Texture * courier = new Texture("resources/fonts/courier.png", 1, 43, 83, 0);

  initDebugDraw(shader);
  Sprite::initSprites(shader, spriteAtlas);
  SpriteText::initText(shader, courier);

  graphics = this;
  coreShader = shader;
  shader.Use();
}

void GraphicsManager::Update(float dt)
{
  coreShader.Use();

  glClearColor(0.2f, 0.7f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  wglMakeCurrent(deviceContext, renderingContext);
  debugDrawFrame();

  SpriteText::renderText(std::string("Frame\nTime: "), Vector3(-3.25, -1.0, 0), Vector3(0.25, 0.45, 1));
  std::string fTime = std::to_string(FramerateController::getPreviousDt());
  SpriteText::renderText(fTime, Vector3(-2, -1.45, 0), Vector3(0.25, 0.45, 1));

  Sprite::drawAllSprites();
  SpriteText::drawAllText();

  //Cleanup 
  glBindVertexArray(0);
  glUseProgram(0);
}

void GraphicsManager::Draw()
{
  SwapBuffers(deviceContext);
  //std::cout << glGetError() << std::endl;
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
  glDepthFunc(GL_ALWAYS);
}

GraphicsManager::~GraphicsManager()
{
  //wgldeletecontext of context
}
