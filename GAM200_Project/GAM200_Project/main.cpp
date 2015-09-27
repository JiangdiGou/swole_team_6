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
  engine->AddSystem(new objFactory());

  engine->Initialize();

  Shader basicShader = Shader("resources/VertexShader.txt", "resources/FragmentShader.txt");
  Camera basicCamera = Camera();
  /******************/
  GameStateMgrInit(GS_GAME);
  while (gGameStateCurr != GS_QUIT)
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
  }
  FACTORY->destroyAllObjects();

  engine->DestroySystems();

  delete engine;

  return 0;
}