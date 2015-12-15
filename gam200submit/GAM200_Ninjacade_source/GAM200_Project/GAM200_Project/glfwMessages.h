/******************************************************************************/
/*!
\file   glfwMessages.h
\author Conor Lavelle
\brief
Input Callback recieved through GLFW
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Core.h"
#include "engineGraphics\Graphics.h"
#include "WindowsSystem.h"
#include "Editor\imGUI\imgui.h"

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
#ifdef EDITOR
  ImGuiIO& io = ImGui::GetIO();
  if (action == GLFW_PRESS)
    io.KeysDown[key] = true;
  if (action == GLFW_RELEASE)
    io.KeysDown[key] = false;

  (void)mods; // Modifiers are not reliable across systems
  io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
  io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
  io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
#endif
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
		MouseButton m(MouseButton::LeftMouse, buttonState, worldPos, mods);
		CORE->BroadcastMessage(&m);
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		MouseButton m(MouseButton::RightMouse, buttonState, worldPos, mods);
		CORE->BroadcastMessage(&m);
	}
}

void glfwMousePosCallback(GLFWwindow *window, double x, double y)
{
	Vec2D worldPos = (GRAPHICS->screenToWorld(Vec2D(x, y)));
	MouseMove m(worldPos);
	CORE->BroadcastMessage(&m);
}

void glfwWindowMinimizeCallback(GLFWwindow* pWindow, int minimized)
{
  if (minimized)
  {
	SoundEmitter* emitter = reinterpret_cast<SoundEmitter*>(LOGIC->player->GetComponent(CT_SoundEmitter));
	emitter->BeQuiet();

    CORE->Pause = true;
    GRAPHICS->toggleBackground(false);
  }
}