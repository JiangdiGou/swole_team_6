#include "WindowsSystem.h"
#include "engineGraphics\Graphics.h"
#include "Core.h"

//A global pointer to the windows system
WindowsSystem* WINDOWSSYSTEM = NULL;



const char windowsClassName[] = "FrameworkEngineWindowClass";


void WindowsSystem::Update(float dt)
{
  MSG msg;
  while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) //It is important to get all windows messages available not just one
  {
    TranslateMessage(&msg);	//Makes sure WM_CHAR and similar messages are generated
    DispatchMessage(&msg);	//Calls the message procedure (see below) with this message

                            //If we get a quit message, broadcast it to all systems
    if (msg.message == WM_QUIT)
    {
      MessageQuit q;
      CORE->BroadcastMessage(&q);
    }
  }
}

LRESULT WINAPI MessageHandler(HWND hWnd,	 //The window the message is for (ours in this case)
	UINT msg,		 //The message type
	WPARAM wParam, //The primary data for the message
	LPARAM lParam) //The secondary data for the message (if any)
{
	//See what type of message it is
	switch (msg)
	{
	case WM_CHAR: //A character key was pressed
	{
		//Create a key message
		MessageCharacterKey key;
		//Set the character pressed (the wParam is the ascii value)
		key.character = wParam;
		//Broadcast the message to all systems
		CORE->BroadcastMessage(&key);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		MouseButton m(MouseButton::LeftMouse, true, Vec2D(WINDOWSSYSTEM->MousePosition.x, WINDOWSSYSTEM->MousePosition.y));
		CORE->BroadcastMessage(&m);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		MouseButton m(MouseButton::RightMouse, true, Vec2D(WINDOWSSYSTEM->MousePosition.x, WINDOWSSYSTEM->MousePosition.y));
		CORE->BroadcastMessage(&m);
		break;
	}
	case WM_LBUTTONUP:
	{
		MouseButton m(MouseButton::LeftMouse, false, Vec2D(WINDOWSSYSTEM->MousePosition.x, WINDOWSSYSTEM->MousePosition.y));
		CORE->BroadcastMessage(&m);
		break;
	}
	case WM_RBUTTONUP:
	{
		MouseButton m(MouseButton::RightMouse, false, Vec2D(WINDOWSSYSTEM->MousePosition.x, WINDOWSSYSTEM->MousePosition.y));
		CORE->BroadcastMessage(&m);
		break;
	}
	case WM_MOUSEMOVE:
	{
		WINDOWSSYSTEM->MousePosition = MAKEPOINTS(lParam);
		MouseMove m(Vec2D(WINDOWSSYSTEM->MousePosition.x, WINDOWSSYSTEM->MousePosition.y));
		CORE->BroadcastMessage(&m);
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 0x41:
		{
			MessageCharacterKey m;
			m.character = 'a';
			CORE->BroadcastMessage(&m);
		}
		case 0x44:
		{
			MessageCharacterKey m;
			m.character = 'd';
			CORE->BroadcastMessage(&m);
		}
		}
		break;
	}
	case WM_KEYUP:
		break;
	case WM_CREATE:
	{
		WINDOWSSYSTEM->deviceContext = GetDC(hWnd);
		setupPixelFormatDescriptor(WINDOWSSYSTEM->deviceContext);
		HGLRC dummyContext = wglCreateContext(WINDOWSSYSTEM->deviceContext);
		wglMakeCurrent(WINDOWSSYSTEM->deviceContext, dummyContext);

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
		WINDOWSSYSTEM->renderingContext = wglCreateContextAttribsARB(WINDOWSSYSTEM->deviceContext, 0, contextAttributes);
		wglMakeCurrent(WINDOWSSYSTEM->deviceContext, WINDOWSSYSTEM->renderingContext);

		//Deletes Dummy Context 
		wglDeleteContext(dummyContext);

		if (!WINDOWSSYSTEM->renderingContext)
			std::cout << "Failed to Create Rendering Context." << std::endl;
		else
			std::cout << "Redering Context Created Successfully." << std::endl;

		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_DROPFILES:
	{
		unsigned int itemCount = DragQueryFile((HDROP)wParam, 0xFFFFFFFF, 0, 0);
		if (itemCount)
		{
			char  buffer[512] = { 0 };
			DragQueryFile((HDROP)wParam, 0, buffer, 512);
			DragFinish((HDROP)wParam);


			FileDrop drop(buffer);
			CORE->BroadcastMessage(&drop);
		}
		return 0;
	}
	case WM_SYSKEYDOWN:
	{
		//Eat the WM_SYSKEYDOWN message to prevent freezing the game when
		//the alt key is pressed
		switch (wParam)
		{
		case VK_LMENU:
		case VK_RMENU:
			return 0;//Stop Alt key from stopping the winProc
		case VK_F4:
			//Check for Alt F4
			DWORD dwAltKeyMask = (1 << 29);
			if ((lParam & dwAltKeyMask) != 0)
				PostQuitMessage(0);
			return 0;
		}
		return 0;
	}
		//We didn't completely handle the message, so pass it on for Windows to handle.
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
	
	
}


WindowsSystem::WindowsSystem(const char* windowTitle, int ClientWidth, int ClientHeight, int show)
{
  //Check to make sure the windows system is created before the factory
  //ErrorIf(FACTORY != NULL, "Windows System already created");

  //Set the global pointer to the windows system
  WINDOWSSYSTEM = this;

  //The size passed to CreateWindow is the full size including the windows border and caption 
  //AdjustWindowRect will adjust the provided rect so that the client size of the window is the desired size
  RECT fullWinRect = { 0, 0, ClientWidth, ClientHeight };
  AdjustWindowRect(&fullWinRect,			//The rectangle for the full size of the window
    WS_OVERLAPPEDWINDOW,	//The style of the window, which must match what is passed in to CreateWindow below
    FALSE);					//Does this window have a menu?

                    //Register the window class for the game.
  WNDCLASSEX wc = { sizeof(WNDCLASSEX),	//The size of this structure (passing the size allows Microsoft to update their interfaces and maintain backward compatibility)
    CS_CLASSDC,							//The style of the window class--this is the base type (one device context for all windows in the process)
    MessageHandler,						//The name of the message handling function
    0L, 0L,								//The amount of extra memory to allocate for this class and window
    GetModuleHandle(NULL),				//Handle to the instance that has the windows procedure--NULL means use this file.
    NULL,								//Add an Icon as a resource and add them here
    LoadCursor(NULL, IDC_ARROW),		//Use the default arrow cursor
    NULL, NULL,							//The background brush and menu--these can be NULL
    windowsClassName, NULL };			//The class name and the small icon (NULL just uses the default)

  RegisterClassEx(&wc);

  //Store the handle to the instance
  hInstance = wc.hInstance;

  //Create the game's window
  hWnd = CreateWindow(windowsClassName,	//The class name
    windowTitle,						//The name for the title bar
    WS_OVERLAPPEDWINDOW,				//The style of the window (WS_BORDER, WS_MINIMIZEBOX, WS_MAXIMIZE, etc.)
    CW_USEDEFAULT, CW_USEDEFAULT,		//The x and y position of the window (screen coords for base windows, relative coords for child windows)
    fullWinRect.right - fullWinRect.left,	//Width of the window, including borders
    fullWinRect.bottom - fullWinRect.top,	//Height of the window, including borders and caption
    GetDesktopWindow(),					//The parent window
    NULL,								//The menu for the window
    hInstance,							//The handle to the instance of the window (ignored in NT/2K/XP)
    NULL);								//The lParam for the WM_CREATE message of this window

  DragAcceptFiles(hWnd, true);
  ShowWindow(hWnd, show);
}

WindowsSystem::~WindowsSystem()
{
  //Unregister the window class
  UnregisterClass(windowsClassName, hInstance);
}

void WindowsSystem::ActivateWindow()
{
  ShowWindow(hWnd, SW_SHOWDEFAULT);
  UpdateWindow(hWnd);
}


bool IsShiftHeld()
{
  return GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0;
}

bool IsCtrlHeld()
{
  return GetKeyState(VK_LCONTROL) < 0 || GetKeyState(VK_RCONTROL) < 0;
}

bool IsAltHeld()
{
  return GetKeyState(VK_LMENU) < 0 || GetKeyState(VK_RMENU) < 0;
}

bool IsUpHeld() { return GetKeyState(VK_UP) < 0; }
bool IsDownHeld() { return GetKeyState(VK_DOWN) < 0; }
bool IsLeftHeld() { return GetKeyState(VK_LEFT) < 0; }
bool IsRightHeld() { return GetKeyState(VK_RIGHT) < 0; }
