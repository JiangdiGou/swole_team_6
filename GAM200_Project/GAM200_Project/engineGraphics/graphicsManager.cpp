#include "graphicsManager.h"

GraphicsManager *graphics;

GraphicsManager::GraphicsManager(const Shader& shader)
{
#ifdef GFXLOG
  gfxErrorLog = new txtlog("graphicsLog.txt");
  gfxErrorLog->write("STARTLOG -- GRAPHICS MANAGER CONSTRUCTED -- STARTLOG");
#endif

  //Flush out the error
  glGetError();
  spriteAtlas = *(new TextureAtlas("resources/Textures/Atlas/testAtlas.png", 
                                  "resources/Textures/tList_testAtlas.txt"));
#ifdef GFXLOG
  logGfxError("TEXTUREATLAS:: Error in texture Atlas construction. ");
#endif

  Texture * courier = new Texture("resources/fonts/courier.png", 1, 43, 83, 0);

  initDebugDraw(shader);

#ifdef GFXLOG
  logGfxError("DEBUGDRAW:: Error in initialization. ");
#endif

  Sprite::initSprites(shader, spriteAtlas);


#ifdef GFXLOG
  logGfxError("SPRITE:: Error in initialization. ");
#endif

  SpriteText::initText(shader, courier);

#ifdef GFXLOG
  logGfxError("SPRITETEXT:: Error in initialization. ");
#endif

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

  SpriteText::renderText(std::string("FPS:"), Vector3(-4.5, -2.5, 0), Vector3(0.15, 0.25, 1));
  std::string fTime = std::to_string((int)(1000.0f / (float)FramerateController::getPreviousDt()));
  SpriteText::renderText(fTime, Vector3(-3.75, -2.5, 0), Vector3(0.15, 0.25, 1));

  debugDrawFrame();
#ifdef GFXLOG
  logGfxError("DEBUGDRAW:: Error in drawing. ");
#endif

  Sprite::drawAllSprites();
#ifdef GFXLOG
  logGfxError("SPRITE:: Error in drawing. ");
#endif

  SpriteText::drawAllText();
#ifdef GFXLOG
  logGfxError("SPRITETEXT:: Error in drawing. ");
#endif

  //Cleanup 
  glBindVertexArray(0);
  glUseProgram(0);
}

void GraphicsManager::Draw()
{
  SwapBuffers(deviceContext);
  FramerateController::frameEnd();

#ifdef GFXLOG
  ++frameNumber;
  if (FramerateController::getPreviousDt() > WARNINGFRAMETIME && frameNumber > STARTUPFRAMES)
  {
    std::string dt = std::to_string(FramerateController::getPreviousDt());
    std::string message = std::string("FRAMERATECONTROLLER:: Abnormally high frame time ");
    message.append(dt); 
    gfxErrorLog->write(message);
  }

  if (frameNumber > STARTUPFRAMES)
    logGfxError("Uncaught Error. ");

  //Clears errors out, handles some edge cases and otherwise has no effect on functionality
  glGetError(); 
#endif
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
