#ifndef DEBUGCONSOLE_H
#define DEBUGCONSOLE_H

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>
#include "Engine.h"
#include <thread>

class debugConsole : public ISystem
{
public:
  debugConsole();
  
  void Update(float dt) override;
  std::string currentMessage;
private:
  FILE* myStream;
  void getInput();
};
#endif 