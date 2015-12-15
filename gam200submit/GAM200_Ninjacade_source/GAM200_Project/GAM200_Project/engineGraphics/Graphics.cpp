/*****************************************************************************/
/*!
\file    Graphics.cpp
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  Contains the implementation of very fundamental low level core graphical
  functions
\remarks 
  

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#include "Graphics.h"


#ifdef GFXLOG

txtlog *gfxErrorLog;
int frameNumber = 0;

#endif


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



#ifdef GFXLOG
void logGfxError(std::string precedingMessage)
{
  if (frameNumber < STARTUPFRAMES)
    return;

  int errorCode = glGetError();
  if (errorCode)
  {
    std::string errorStr = std::to_string(errorCode);
    std::string output = std::string("Error #");
    output.append(errorStr);
    precedingMessage.append(output);
    gfxErrorLog->write(precedingMessage);
  }
}
#endif

