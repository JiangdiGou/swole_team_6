#include "debugConsole.h"
#include "WindowsSystem.h"

debugConsole::debugConsole()
{
  //AllocConsole();
  //freopen("CONIN$", "w", myStream);
}

void debugConsole::getInput()
{
  std::cout << "Enter a Command" << std::endl;
  std::cin >> currentMessage;
  std::cout << currentMessage;

 //THE FUCK?!?!?
}

void debugConsole::Update(float dt)
{
  //std::thread first(&debugConsole::getInput, debugConsole());
  //first.join();
  getInput();

}
