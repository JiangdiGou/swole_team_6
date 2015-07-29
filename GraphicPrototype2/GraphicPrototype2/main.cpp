//Conor Lavelle
//Gam 200 Graphics Prototype
//Swole Team 6
//7-11-15

#define _CRT_SECURE_NO_WARNINGS
#include "Sprite.h"
#include "Camera.h"
#include "Testing.h"

#include <Windows.h>

HDC deviceContext;
HGLRC renderingContext;

bool shouldQuit = false;

//Entry point of the application
int WINAPI WinMain(HINSTANCE instance, HINSTANCE hPreviousInstance, LPSTR command_line, int show)
{
    //Openas a console for debugging and testing 
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    //Stores the window being created
    HWND window; 
    //Stores windows messages 
    MSG msg;

    //Creates a window, saves it in hwnd, and shows on screen
    window = createWindow(instance);
    ShowWindow(window, show);

    Shader basicShader = Shader("VertexShader.txt", "FragmentShader.txt");
    Camera basicCamera = Camera(basicShader);

    //Creates Three Sprites
    Sprite smiley = Sprite(basicShader);
    Sprite excited = Sprite(basicShader);
    Sprite calm = Sprite(basicShader);
  
    Sprite animated = Sprite(basicShader);

    Texture textureSmiley = Texture("Smiley1.png");
    Texture textureExcited = Texture("Smiley2.png");
    Texture textureCalm = Texture("Smiley3.png");

    Texture textureAnimated = Texture("ExampleSpriteSheet.png", 3, 64, 64, 1000.0f);
    animated.texture = textureAnimated;
    animated.translation = glm::vec3(-1.5f, 1.0f, 0.0f);

    //Saves the textures into the sprites 
    smiley.texture = textureSmiley;
    excited.texture = textureExcited;
    calm.texture = textureCalm;

    //Sets inital values of sprites for their respective tests
    smiley.translation = glm::vec3(1.0f, 0.5f, 0.0f);
    excited.translation = glm::vec3(-1.4f, -0.75f, 0.0f);
    calm.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    smiley.scale = glm::vec3(0.15f, 0.15f, 0.15f);

    basicShader.Use();

    //This should probably eventually use a game state manager like cs230
    //But this is fine for now 
    while (!shouldQuit)
    {
        wglMakeCurrent(deviceContext, renderingContext);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //basicCamera.move(glm::vec3(0.01f, 0.0f, 0.0f));
        //basicCamera.zoom -= .005;

        basicCamera.update();
        Sprite::drawSprites();

        testScaling(smiley);
        testRotation(excited);
        testTranslate(calm);
        testColor(calm);

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
        WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        0
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