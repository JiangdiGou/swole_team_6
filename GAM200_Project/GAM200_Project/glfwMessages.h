#include "Core.h"
#include "engineGraphics\Graphics.h"
#include "WindowsSystem.h"
#include "lvlTools\imGUI\imgui.h"

/*

	case WM_LBUTTONDOWN:
	{
		Vec2D worldPos = GRAPHICS->screenToWorld(Vec2D(WINDOWSSYSTEM->MousePosition.x,
			WINDOWSSYSTEM->MousePosition.y));
		MouseButton m(MouseButton::LeftMouse, true, worldPos);
		CORE->BroadcastMessage(&m);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		Vec2D worldPos = GRAPHICS->screenToWorld(Vec2D(WINDOWSSYSTEM->MousePosition.x,
			WINDOWSSYSTEM->MousePosition.y));
		MouseButton m(MouseButton::RightMouse, true, worldPos);
		CORE->BroadcastMessage(&m);
		break;
	}
	case WM_LBUTTONUP:
	{
		Vec2D worldPos = GRAPHICS->screenToWorld(Vec2D(WINDOWSSYSTEM->MousePosition.x,
			WINDOWSSYSTEM->MousePosition.y));
		MouseButton m(MouseButton::LeftMouse, false, worldPos);
		CORE->BroadcastMessage(&m);
		break;
	}
	case WM_RBUTTONUP:
	{
		Vec2D worldPos = GRAPHICS->screenToWorld(Vec2D(WINDOWSSYSTEM->MousePosition.x,
			WINDOWSSYSTEM->MousePosition.y));
		MouseButton m(MouseButton::RightMouse, false, worldPos);
		CORE->BroadcastMessage(&m);
		break;
	}
	case WM_MOUSEMOVE:
	{
		WINDOWSSYSTEM->MousePosition = MAKEPOINTS(lParam);
		Vec2D worldPos = GRAPHICS->screenToWorld(Vec2D(WINDOWSSYSTEM->MousePosition.x,
			WINDOWSSYSTEM->MousePosition.y));
		MouseMove m(worldPos);
		CORE->BroadcastMessage(&m);
		break;
	}
	case WM_KEYDOWN:
	{
		MessageCharacterKey m;
		if (lParam & 0x40000000)
			m.keyStatus = KEY_DOWN;
		else
			m.keyStatus = KEY_PRESSED;
		m.character = (char)wParam;
		CORE->BroadcastMessage(&m);
		break;
	}
	case WM_KEYUP:
	{
		MessageCharacterKey m;
		m.keyStatus = KEY_RELEASED;
		m.character = (char)wParam;
		CORE->BroadcastMessage(&m);
		break;
	}
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
	case WM_SIZE:
	{
		int width = LOWORD(lParam);
		int height = HIWORD(lParam);
		INITINFO->clientWidth = width;
		INITINFO->clientHeight = height;
		glViewport(0, 0, width, height);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_CLOSE:
	{
		int  result = MessageBox(hWnd, "Are you sure you want to quit Ninjacade?", "Quit Confirmation", MB_YESNO);
		std::cout << result << std::endl;
		if (result == 6)
		{
			PostQuitMessage(0);
			return 0;
		}
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
}
*/

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Create a key message
	MessageCharacterKey keyMsg;
	//Lazy conversion to char
	keyMsg.character = key + '0' - '0';

	if (action == GLFW_PRESS)
	{
		keyMsg.keyStatus = KEY_PRESSED;
	}
	else if (action == GLFW_REPEAT)
	{
		keyMsg.keyStatus = KEY_DOWN;
	}
	else if (action == GLFW_RELEASE)
	{
		keyMsg.keyStatus = KEY_RELEASED;
	}

	//Broadcast the message to all systems
	CORE->BroadcastMessage(&keyMsg);

  ImGuiIO& io = ImGui::GetIO();
  if (action == GLFW_PRESS)
    io.KeysDown[key] = true;
  if (action == GLFW_RELEASE)
    io.KeysDown[key] = false;

  (void)mods; // Modifiers are not reliable across systems
  io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
  io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
  io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
}

void glfwMouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	double cursorPosX, cursorPosY;
	bool buttonState;
	Vec2D worldPos;

	if (action == GLFW_PRESS)
		buttonState = true;
	else if (action == GLFW_RELEASE)
		buttonState = false;

	glfwGetCursorPos(window, &cursorPosX, &cursorPosY);
	worldPos = GRAPHICS->screenToWorld(Vec2D(cursorPosX, cursorPosY));

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		MouseButton m(MouseButton::LeftMouse, buttonState, worldPos);
		CORE->BroadcastMessage(&m);
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		MouseButton m(MouseButton::RightMouse, buttonState, worldPos);
		CORE->BroadcastMessage(&m);
	}
}

void glfwMousePosCallback(GLFWwindow *window, double x, double y)
{
	Vec2D worldPos = GRAPHICS->screenToWorld(Vec2D(x, y));
	MouseMove m(worldPos);
	CORE->BroadcastMessage(&m);
}

//The remaining functions are from imgui binding, i just put here for consistency
void glfwCharCallback(GLFWwindow*, unsigned int c)
{
  ImGuiIO& io = ImGui::GetIO();
  if (c > 0 && c < 0x10000)
    io.AddInputCharacter((unsigned short)c);
}