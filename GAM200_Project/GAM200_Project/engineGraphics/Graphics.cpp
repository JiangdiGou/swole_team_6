#include "Graphics.h"

//**********************
//Function    : setupPixelFormatDescriptor
//Input       : deviceContext - the device context of the window. 
//Output      : none
//Description : PFD is used to tell windows how pixels draw on the screen.
//              this sets one up. 
//**********************
void setupPixelFormatDescriptor(HDC deviceContext)
{
  PIXELFORMATDESCRIPTOR pfd;
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  pfd.iLayerType = PFD_MAIN_PLANE;

  int chosenPixelFormat = ChoosePixelFormat(deviceContext, &pfd);
  bool result = SetPixelFormat(deviceContext, chosenPixelFormat, &pfd);

  if (!result)
    std::cout << "Pixel Format Descriptor Creation Failed." << std::endl;
  else
    std::cout << "Pixel Format Descriptor Creation Successful." << std::endl;
}

//**********************
//Function    : createWindow
//Input       : instance - paramter from winMain 
//Output      : HWND - handle to the window that is created 
//Description : Creates a window and returns a handle to it. 
//**********************
/*HWND createWindow(HINSTANCE instance)
{
  WNDCLASS windowClass;
  //Class Style
  windowClass.style = CS_HREDRAW | CS_VREDRAW;
  //Pointer to Winproc
  windowClass.lpfnWndProc = WinProc;
  //Extra Bytes the class needs 
  windowClass.cbClsExtra = 0;
  //Extra Bytes the window needs 
  windowClass.cbWndExtra = 0;
  //Instance from winmain parameter
  windowClass.hInstance = instance;
  //Icon in top left of window 
  windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  //Handle to cursor class 
  windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  //Handle to window background
  windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  //Something for menus, which we're not using
  windowClass.lpszMenuName = NULL;
  //Name of class 
  windowClass.lpszClassName = "window";

  RegisterClass(&windowClass);


  return CreateWindow(
    // The name of the window class of this window 
    windowClass.lpszClassName,
    // The caption in the created window 
    "graphicsPrototype",
    //The style of the window
    WS_OVERLAPPEDWINDOW,
    //Window's starting X coordinate
    200,
    //Window's starting Y coordinate
    200,
    //Window's Width
    WINDOWWIDTH,
    //Window's Height
    WINDOWHEIGHT,
    //Handle to the parent window 
    NULL,
    //Handle to a menu 
    NULL,
    //Instance parameter from winmain
    instance,
    //Pointer to value associated with WM_CREATE message
    NULL);
}*/

