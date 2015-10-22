#ifndef WINDOWSSYSTEM_H
#define WINDOWSSYSTEM_H
//#include "Engine.h"
#include "windows.h"
#include "physicsLib/math_utility.h"
#include "System.h"
#include <string>


class WindowsSystem : public ISystem
{
public:
  WindowsSystem(const char* windowTitle, int ClientWidth, int ClientHeight, int show);	//The constructor
  ~WindowsSystem();															//The destructor

  void ActivateWindow();								//Activate the game window so it is actually visible
  virtual void Update(float dt);						//Update the system every frame
  virtual std::string GetName() { return "Windows"; }	//Get the string name of the system
  void SendMessages(Message* m) override;

  HWND hWnd;											//The handle to the game window
  HINSTANCE hInstance;								//The handle to the instance
  POINTS MousePosition;
  HDC deviceContext;
  HGLRC renderingContext;
};

///Message signaling that a key is pressed.
class MessageCharacterKey : public Message
{
public:
  MessageCharacterKey() : Message(Mid::CharacterKey) {};
  char character;
  int keyStatus;
};

///Message signaling that a mouse button state has changed.
class MouseButton : public Message
{
public:
  enum MouseButtonIndexId
  {
    LeftMouse,
    RightMouse
  };
  MouseButton(MouseButtonIndexId button, bool state, Vec2D position)
    : Message(Mid::MouseButton), MouseButtonIndex(button), ButtonIsPressed(state), MousePosition(position) {};

  MouseButtonIndexId MouseButtonIndex;
  bool ButtonIsPressed;
  Vec2D MousePosition;
};

///Message signaling that the mouse has moved.
class MouseMove : public Message
{
public:
  MouseMove(Vec2D position) : Message(Mid::MouseMove), MousePosition(position) {};
  Vec2D MousePosition;
};

///Message signaling that a file was dropped onto the window.
class FileDrop : public Message
{
public:
  FileDrop(std::string filename) : Message(Mid::FileDrop), FileName(filename) {};
  std::string FileName;
};

bool IsShiftHeld();
bool IsCtrlHeld();
bool IsAltHeld();
bool IsUpHeld();
bool IsDownHeld();
bool IsLeftHeld();
bool IsRightHeld();

extern WindowsSystem* WINDOWSSYSTEM;

#endif