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
#include "extraLogger/extraLogger.h"
#include "engineGraphics/graphicsManager.h"
#include "GameLogic\GameLogic.h"
#include "Core.h"
#include "engineGraphics/Graphics.h"
#include "WindowsSystem.h"
#include "runLua/luaTranslate.h"
#include "runLua/luaRunner.h"
#include "Utilities.h"
//#include "ActionSystem\ActionSequence.h"
#include "glfwMessages.h"
#include "initInfo.h"
#include "Editor\imGuiManager.h"
#include "Zilch\Zilch.hpp"
#include "Zilch\ZilchInterface.hpp"
#include "Zilch\ZilchManager.h"
#include "Zilch\ZilchBind.h"
#include "GameLogic\PauseMenu.h"

initInfo * INITINFO;

using namespace Zilch;
//HDC deviceContext;
//HGLRC renderingContext;

int main(void)
{
  luaInitFile();
  //Do init stuff from ini file here. currently, we do nothing.

  //coloured_console.cprintf(CConsoleLoggerEx::COLOR_RED | CConsoleLoggerEx::COLOR_BACKGROUND_BLACK, "Another console");
  //coloured_console.printf("Rip C++ piping.");
  //Opens a console for debugging and testing 
  /*
  if (INITINFO->showConsole)
  {
	  AllocConsole();
	  AttachConsole(GetCurrentProcessId());
	  freopen("CONIN$", "r", stdin);
	  freopen("CONOUT$", "w", stdout);
	  freopen("CONOUT$", "w", stderr);
  }*/

  //Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  //Create a Window 
	GLFWwindow* window = glfwCreateWindow(INITINFO->clientWidth, INITINFO->clientHeight, "NinjaCade", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

  //Makes the created window the current window for openGL
	glfwMakeContextCurrent(window);

  //Inits glew, fectching openGL function pointers(i think?)
	glewExperimental = GL_TRUE;
	if (int error = glewInit())
	{
		std::cout << "Failed to initialize GLEW. Error: " << error << std::endl;
		return -1;
	}

  //Sets glfw callbacks, which hook up our messaging system through glfw. see glfwmessage.h
	glfwSetKeyCallback(window, glfwKeyCallback);
	glfwSetMouseButtonCallback(window, glfwMouseButtonCallback);
	glfwSetCursorPosCallback(window, glfwMousePosCallback);

  CoreEngine* engine = new CoreEngine();
  //Create Systems and add them to engine
  engine->AddSystem(new Physics());
  engine->AddSystem(new SoundManager());
  engine->AddSystem(new PauseMenu());

  //Zilch Compilation
  //ZilchInterface *zilch = new ZilchInterface();
  /*zilch->IncludeScriptFile(FilePaths::GetBasePath("PlayerJump.z"));
  zilch->IncludeScriptFile(FilePaths::GetBasePath("PlayerMovement.z"));
  zilch->IncludeScriptFile(FilePaths::GetBasePath("PlayerSlashAttack.z"));
  zilch->IncludeScriptFile(FilePaths::GetBasePath("PlayerStats.z"));
  zilch->IncludeScriptFile(FilePaths::GetBasePath("Trigger.z"));
  zilch->IncludeScriptFile(FilePaths::GetBasePath("TutorialTriggerPosition.z"));*/
  //zilch->Init();
  //ZilchInterface *zilch = new ZilchInterface();
  //zilch->IncludeScriptFile(FilePaths::GetBasePath("Example.zilch"));
  //zilch->Init();
  
  ZilchSetup setup(StartupFlags::None);
  /*Project project;
  project.AddCodeFromFile("Player.zilch");
  project.AddCodeFromFile("Scripts/Example.zilch");
  Module dependencies;
  dependencies.push_back(ZLib_Internal::GetLibrary());

  LibraryRef library = project.Compile("Test", dependencies, EvaluationMode::Project);
  ErrorIf(library == nullptr, "Failed to compile library");

  dependencies.push_back(library);

  ExecutableState* state = dependencies.Link();
  ErrorIf(state == nullptr, "Failed to link libraries together");*/
  ZilchBinder binders(true);



#ifdef EDITOR
  engine->AddSystem(new ImGuiManager(window));
#endif

  Shader* pBasicShader = new Shader("resources/shaders/VertexShader.txt", "resources/shaders/FragmentShader.txt");
  const Shader &basicShader = *pBasicShader;
  engine->AddSystem(new GraphicsManager(basicShader));
  
  //engine->AddSystem(new ActionSystem::ActionSequence());
  objFactory* factory = new objFactory();
  engine->AddSystem(factory);
  engine->AddSystem(new ZilchManager(&binders.mDependencies, binders.mLibrary, &binders.mProject, binders.mState));
  engine->AddSystem(new GameLogic());

  //Initialize all systems in engine
  engine->Initialize();
  //This should be a part of the constructor when I have less important things to do.
	GRAPHICS->setWindow(window);

  //I think this is testing nolan's debug console type thing but
  /*Vector3D dumbVector(1.2, 1.2, 1.2);
  CConsoleLoggerEx coloured_console;
  coloured_console.Create("Debug Console");
  coloured_console.printf("LOL C++.\n");
  coloured_console << 213213 << "\n";
  coloured_console << "candy" << "\n";
  coloured_console << "la di da vector: " << dumbVector << "\n";*/
  engine->GameLoop();
  
  glfwTerminate();

  FACTORY->destroyAllObjects(true);
  engine->DestroySystems();

  delete engine;
  return 0;
}