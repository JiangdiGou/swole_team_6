#pragma once

#define ABSTRACT = 0

class BaseComponent
{
public:

  virtual void Init() ABSTRACT;
  virtual void Shutdown() ABSTRACT;

private:

};