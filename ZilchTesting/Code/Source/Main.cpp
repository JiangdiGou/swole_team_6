#include <ZILCH/zilch.hpp>

#include "Binding/BindInternal.hpp"
#include "ZilchInterface.hpp"
#include <iostream>

#include "Binding/Character.hpp"

using namespace Zilch;



void ZilchTest1(ZilchInterface *zilch)
{
  // Find the Player type we created in Zilch
  BoundType* playerType = zilch->GetBoundType("Script_Player");

  // Find the instance data member 'Health' on the Player (a data member is called a Field in Zilch)
  Field* healthField = zilch->GetTypeField(playerType, "Health");

  // Find the static SayHello function we defined on the Player type
  Function* sayHelloFunc = zilch->GetStaticFunction(playerType, "SayHello");

  // Find the instance 'TakeDamage' function on the Player which accepts a Real and returns nothing (Void)
  Function* takeDamageFunc = zilch->GetFunction(playerType, "TakeDamage", ZilchTypeId(void), Array<Type*>(ZeroInit, ZilchTypeId(Real)));

  // Find the instance 'ReturnReal' function on the player
  Function* returnRealFunc = zilch->GetFunction(playerType, "ReturnReal", ZilchTypeId(Real));

  // Find the instance 'Test' function
  Function* testFunc = zilch->GetFunction(playerType, "Test");


  // Player.SayHello()
  {
    // Invoke the SayHello function, which should print out to the console
    Call call(sayHelloFunc, zilch->state_);
    call.Invoke(zilch->report_);
  }

  // var playerInstance = new Player();
  // playerInstance.Health = 200.0;
  // playerInstance.TakeDamage(10.0);
  {
    // Allocate the player and call a default constructor if one is provided
    Handle playerInstance = zilch->AllocateType(playerType);

    {
      Call call(healthField->Set, zilch->state_);
      call.Set<Handle>(Call::This, playerInstance);
      call.Set<Real>(0, 200.0f);
      call.Invoke(zilch->report_);
    }

    // read from member
    {
      Call call(healthField->Get, zilch->state_);
      call.Set<Handle>(Call::This, playerInstance);
      call.Invoke(zilch->report_);
      float cur_health = call.Get<Zilch::Real>(Zilch::Call::Return);
      std::cout << "Current health is: " << cur_health << std::endl;
    }

    // Now invoke the member function 'TakeDamage'
    {
      Call call(takeDamageFunc, zilch->state_);
      call.Set<Handle>(Call::This, playerInstance);
      call.Set<Real>(0, 10.0f);
      call.Invoke(zilch->report_);
    }

    // get member function return type
    {
      Call call(returnRealFunc, zilch->state_);
      call.Set<Handle>(Call::This, playerInstance);
      call.Invoke(zilch->report_);
      float val = call.Get<Zilch::Real>(Zilch::Call::Return);
      std::cout << "Return Real val is: " << val << std::endl;
    }

  }
}


void ZilchTest2(ZilchInterface *zilch)
{
  
  // grab type
  BoundType* playerType = zilch->GetBoundType("Script_Player");

  // grab test function from type
  Function* testFunc = zilch->GetFunction(playerType, "Test");

  // allocate instance
  Handle playerInstance = zilch->AllocateType(playerType);

  Call call(testFunc, zilch->state_);            // 1. Set up call.
  call.Set<Handle>(Call::This, playerInstance);  // 2. Fill function parameters (member function requires 'this')
  call.Invoke(zilch->report_);                   // 3. Invoke call without return value.

  // we need an event handler pointer for the sender of the event (can even be the receiver)
  EventHandler *p_playerInstance = (EventHandler*)(playerInstance.Dereference());
  EventHandler *p_characterTemp = new Character();

  EventData* test = new EventData();
  //EventSend(p_playerInstance, "TestEvent", test);

 // testType->AllProperties.

}


void ZilchTest3(ZilchInterface *zilch)
{
  BoundType* cppDefinedType   = ZLib_Internal::GetLibrary()->BoundTypes.findValue("Player", nullptr);
  BoundType* scriptDefinedType = zilch->library_->BoundTypes.findValue("Script_Player", nullptr);

  Console::WriteLine("\n======= CPP Defined Type =======\n");
  ZilchInterface::DebugPrintBoundType(cppDefinedType);

  Console::WriteLine("\n======= Script Defined Type =======\n");
  ZilchInterface::DebugPrintBoundType(scriptDefinedType);
}





int main()
{
  // sets up stuff that needs to be set once, and never again for the life of the program
  ZilchInterface *zilch = new ZilchInterface();

  // add a file for zilch to compile
  zilch->IncludeScriptFile(FilePaths::GetBasePath("Player.zilch"));

  // compiles zilch
  zilch->Init();

  ZilchTest3(zilch);

  getchar();

  return 0;
}