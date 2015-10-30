#include "Swole.h"

Swole::Swole(const CoreEngine& engine) :logger(txtlog(SWOLELOG_FILENAME))
{
  for (std::vector<ISystem*>::iterator it = engine.getSystems().begin();
    it != engine.getSystems().end(); ++it)
  {
    systems.push_back(*it);
  }
}