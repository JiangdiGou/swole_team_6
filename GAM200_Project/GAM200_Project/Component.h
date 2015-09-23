#ifndef COMPONENT_H
#define COMPONENT_H
#include "ComponentTypeIds.h"
namespace Framework
{
  class GameObjectComposition;
  typedef GameObjectComposition GOC;

  class GameComponent
  {
  public:
    friend class GameObjectComposition;

    virtual void Initialize() {};

    GOC* GetOwner() { return Base; }

    ComponentTypeId TypeId;

  protected:
    virtual ~GameComponent() {};
  private:
    //pointer to the owner composition
    GOC* Base;
  };
}

#endif