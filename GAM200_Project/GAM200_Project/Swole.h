#ifndef SWOLE_H
#define SWOLE_H

#include "Core.h"
#include "logger\logger.h"
#include <vector>

#define SWOLELOG_FILENAME "swoleLog.txt"

class Swole
{
  Swole(const CoreEngine& engine);

  virtual void SendMessages(Message *) {};

  txtlog logger;
  std::vector<ISystem*> systems = {};
};

#endif