#ifndef SYSTEM_H
#define SYSTEM_H
class ISystem
{
public:
  ///All systems are updated every game frame.
  virtual void Update(float dt) = 0;

  ///Initialize the system.
  virtual void Initialize() {};
  ///Initialize the system.
  virtual void Draw() {};

  ///All systems need a virtual destructor to have their destructor called 
  virtual ~ISystem() {}
};
#endif