/******************************************************************************/
/*!
\file   Main.c
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
  main loop
*/
/******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "_EntryPoint.h"
#include "graphicsManager.h"
#include "GameLogic.h"
#include "Core.h"

HDC deviceContext;
HGLRC renderingContext;

#ifdef GAMELOOP_RUN
int WINAPI WinMain(HINSTANCE instance, HINSTANCE hPreviousInstance, LPSTR command_line, int show)
#else
int falseMain2(HINSTANCE instance, HINSTANCE hPreviousInstance, LPSTR command_line, int show)
#endif
{
  //Opens a console for debugging and testing 
  AllocConsole();
  freopen("CONOUT$", "w", stdout);

  //Stores the window being created
  HWND window;
  //Stores windows messages 
  MSG msg;

  //Creates a window, saves it in hwnd, and shows on screen
  window = createWindow(instance);
  ShowWindow(window, show);
  /**************/
  CoreEngine* engine = new CoreEngine();

  engine->AddSystem(new PhysicsManager());

  Shader* basicShader = new Shader("resources/VertexShader.txt", "resources/FragmentShader.txt");
  engine->AddSystem(new GraphicsManager(*basicShader, *basicShader));
  engine->AddSystem(new GameLogic());
  engine->AddSystem(new objFactory());

  engine->Initialize();

  graphics->setDeviceContext(deviceContext);
  graphics->setRenderingContext(renderingContext);

  //Camera basicCamera = Camera();
  /******************/
  /*GameStateMgrInit(GS_GAME);
  /*while (gGameStateCurr != GS_QUIT)
  {

    // If not restarting, load the gamestate
    if (gGameStateCurr != GS_RESTART)
    {
      GameStateMgrUpdate();
      GameStateLoad();
    }
    else
      gGameStateNext = gGameStateCurr = gGameStatePrev;

    // Initialize the gamestate
    GameStateInit();

    while (gGameStateCurr == gGameStateNext)
    {

      GameStateUpdate();

      GameStateDraw();
    }

    GameStateFree();

    if (gGameStateNext != GS_RESTART)
      GameStateUnload();

    gGameStatePrev = gGameStateCurr;
    gGameStateCurr = gGameStateNext;
  }*/

  engine->LastTime = timeGetTime();
  while (engine->GameActive)
  {
    engine->GameLoop();

    if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  FACTORY->destroyAllObjects();
  engine->DestroySystems();

  delete engine;

  return 0;
}


#ifdef GAMELOOP_RUN
LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
#else
int falseCallback2(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
#endif
{
  RigidBody* body = NULL;
  Sprite* sprite = NULL;
  Transform* transform = NULL;
  RigidBody* body2 = NULL;
  Sprite* sprite2 = NULL;
  Transform* transform2 = NULL;
  if (LOGIC != NULL && LOGIC->player != NULL)
  {
    body = (LOGIC->player)->has(RigidBody);
    sprite = (LOGIC->player)->has(Sprite);
    transform = (LOGIC->player)->has(Transform);
  }
  if (LOGIC != NULL && LOGIC->player2 != NULL)
  {
	  body2 = (LOGIC->player2)->has(RigidBody);
	  sprite2 = (LOGIC->player2)->has(Sprite);
	  transform2 = (LOGIC->player2)->has(Transform);
  }
  switch (msg)
  {
  case WM_KEYDOWN:
  {
    switch (wp)
    {
    case VK_LEFT:
    {
      body->setVelocity(-1.5, body->getVelocity().y) ;
      if (sprite->texture.ID != LOGIC->textureRunBlue->ID)
      {
        sprite->texture = *(LOGIC->textureRunBlue);
        
      }
      break;
    }
    case VK_RIGHT:
    {
		body->setVelocity(1.5, body->getVelocity().y);
      break;
    }
	case 'A':
	{
		body2->setVelocity(-1.5, body2->getVelocity().y);
	}
		break;
	case 'D':
	{
		body2->setVelocity(+1.5, body2->getVelocity().y);
	}
		break;


    default:
    {
      break;
    }
   	
    }
  }
  break;

  case WM_CREATE:
  {
    deviceContext = GetDC(hWnd);
    setupPixelFormatDescriptor(deviceContext);
    HGLRC dummyContext = wglCreateContext(deviceContext);
    wglMakeCurrent(deviceContext, dummyContext);

    //Initalizes Glew
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
      std::cout << "Failed to initalize GLEW." << std::endl;
    else
      std::cout << "Glew Initalized Successfully." << std::endl;

    //Saves attributes of the real context in an array
    int contextAttributes[] =
    {
      WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
      WGL_CONTEXT_MINOR_VERSION_ARB, 3,
      WGL_CONTEXT_FLAGS_ARB,
      WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, 0
    };

    //Creates the Real context and activates it 
    renderingContext = wglCreateContextAttribsARB(deviceContext, 0, contextAttributes);
    wglMakeCurrent(deviceContext, renderingContext);

    //Deletes Dummy Context 
    wglDeleteContext(dummyContext);

    if (!renderingContext)
      std::cout << "Failed to Create Rendering Context." << std::endl;
    else
      std::cout << "Redering Context Created Successfully." << std::endl;
  }
  break;

  default:
    return DefWindowProc(hWnd, msg, wp, lp);
  }
}