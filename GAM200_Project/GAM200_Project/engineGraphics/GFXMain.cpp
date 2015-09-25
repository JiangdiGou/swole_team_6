//Conor Lavelle
//Gam 200 Graphics Prototype
//Swole Team 6
//7-11-15

#define _CRT_SECURE_NO_WARNINGS
#include "Sprite.h"
#include "Camera.h"
#include "Testing.h"
#include "debugDraw.h"
#include "../_EntryPoint.h"
#include <Windows.h>
#include "instancedSprite.h"
#include "FramerateController.h"

#include <ft2build.h>
#include FT_FREETYPE_H

HDC deviceContext;
HGLRC renderingContext;

Sprite* pPlayer;
Texture* pTexturePlayerRun;
Texture* pTexturePlayerIdle;

bool shouldQuit = false;

//Entry point of the application
#ifdef GFX_RUN
int WINAPI WinMain(HINSTANCE instance, HINSTANCE hPreviousInstance, LPSTR command_line, int show)
#else
int falseMain1(HINSTANCE instance, HINSTANCE hPreviousInstance, LPSTR command_line, int show)
#endif
{
  //Openas a console for debugging and testing 
  AllocConsole();
  freopen("CONOUT$", "w", stdout);
  
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
    std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
  
  FT_Face face;
  if (FT_New_Face(ft, "resources/fonts/OpenSans-Regular.ttf", 0, &face))
    std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;


  //Stores the window being created
  HWND window; 
  //Stores windows messages 
  MSG msg;

  //Creates a window, saves it in hwnd, and shows on screen
  window = createWindow(instance);
  ShowWindow(window, show);

  //Creates the core shader and camera 
  Shader basicShader = Shader("resources/VertexShader.txt", "resources/FragmentShader.txt");
  Camera basicCamera = Camera();

  //Instancing Testing 
  //Shader basicShader2 = Shader("resources/VertexShader2.txt", "resources/FragmentShader2.txt");
  //ISprite::Load(basicShader2);
  //ISprite::drawSprites(textureAnimated);

  //Creates Sprites
  Sprite smiley = Sprite(basicShader);
  Sprite excited = Sprite(basicShader);
  Sprite calm = Sprite(basicShader);
  Sprite animated = Sprite(basicShader);
  Sprite player = Sprite(basicShader);
  /*
  Sprite player2 = Sprite(basicShader);
  Sprite player3 = Sprite(basicShader);
  Sprite player4 = Sprite(basicShader);
  */
  pPlayer = &player;

	//Sets up textures 
  Texture textureSmiley = Texture("resources/Smiley1.png");
  Texture textureExcited = Texture("resources/Smiley2.png");
  Texture textureCalm = Texture("resources/Smiley3.png");
	Texture textureAnimated = Texture("resources/ExampleSpriteSheet.png", 3, 64, 64, 1000.0f);
	Texture texturePlayerIdle = Texture("resources/FinalRunAnimations.png", 4, 64, 64, 100.0f);
	Texture texturePlayerRun = Texture("resources/FinalRunAnimations.png", 4, 64, 64, 100.0f, 0, 64);
	pTexturePlayerRun = &texturePlayerRun;
	pTexturePlayerIdle = &texturePlayerIdle;

  //Saves the textures into the sprites 
  smiley.texture = textureSmiley;
  excited.texture = textureExcited;
  calm.texture = textureCalm;
	animated.texture = textureAnimated;

	player.texture = texturePlayerIdle;
  /*
  player2.texture = texturePlayerRun;
  player3.texture = texturePlayerRun;
  player4.texture = texturePlayerRun;
  */
  //Sets inital values of sprites for their respective tests
  smiley.translation = glm::vec3(1.0f, 0.5f, 0.0f);
  excited.translation = glm::vec3(-1.4f, -0.75f, 0.0f);
  calm.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  smiley.scale = glm::vec3(0.15f, 0.15f, 0.15f);
	animated.translation = glm::vec3(-1.5f, 1.0f, 0.0f);


	//I know three parts to drawing isnt ideal but this will eventually be in a larger
	//init graphics function or something. 
	initDebugDraw(basicShader); 
  basicShader.Use();

  //This should probably eventually use a game state manager like cs230
  //But this is fine for now 
  while (!shouldQuit)
  {
    wglMakeCurrent(deviceContext, renderingContext);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    testColor(calm);
    testTranslate(calm);
    testRotation(excited);
    testScaling(smiley);

    basicCamera.Update();

    Sprite::drawSprites();

	  //Again, not ideal, but there will eventually be a draw all function or something
	  debugDrawFrame();

	  debugDrawLine(smiley.translation, calm.translation, glm::vec3(1.0f, 1.0f, 1.0f));
	  debugDrawLine(excited.translation, calm.translation, glm::vec3());
	  debugDrawLine(animated.translation, calm.translation, glm::vec3());

	  debugDrawSquare(calm.translation, calm.scale.x, calm.scale.y, glm::vec3());
	  debugDrawSquare(smiley.translation, smiley.scale.x, smiley.scale.y, glm::vec3());
	  debugDrawSquare(excited.translation, excited.scale.x, excited.scale.y, glm::vec3());

	  debugDrawCircle(calm.translation, calm.scale.x, glm::vec3(), 100);
	  debugDrawCircle(animated.translation, 0.5*animated.scale.x, glm::vec3(), 100);

    
    FramerateController::frameEnd();
    SwapBuffers(deviceContext);

    if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    wglMakeCurrent(NULL, NULL);

  }
  return 0;
}

//Callback function 
LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
  switch (msg)
  {
	case WM_KEYDOWN:
	{
		switch (wp)
		{
			case VK_LEFT:
			{
				pPlayer->translation.x = pPlayer->translation.x -= 0.25;
				pPlayer->scale.x = -1;
				pPlayer->texture = *pTexturePlayerRun;
        break;
			}
			case VK_RIGHT:
			{
				pPlayer->translation.x = pPlayer->translation.x += 0.25;
				pPlayer->scale.x = 1;
				pPlayer->texture = *pTexturePlayerRun;
        break;
			}

			default:
			{
				if (pPlayer->texture.ID != pTexturePlayerIdle->ID)
					pPlayer->texture = *pTexturePlayerIdle;
        break;
			}
		}
	}
  break;
	
  case WM_CREATE:
  {
    //Creates a Dummy Context so a real context can be created
    //Why? I dunno. They made it this way. It's dumb. 
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

  case WM_DESTROY:
    shouldQuit = true;

  default:    
      return DefWindowProc(hWnd, msg, wp, lp);
  }
}