#pragma once

#include <ZILCH/zilch.hpp>

#include <string>
#include <unordered_map>

#include "Filesystem/Filepaths.hpp"

using namespace Zilch;

class ZilchInterface
{
public:
  // setting up some typedefs
  using zilchOrigin = std::string;
  using zilchCode   = std::string;
  using zilchFile   = std::string;

  ZilchInterface();
  ~ZilchInterface();

  void Init();
  void Shutdown();

  void IncludeScriptFile(zilchFile filepath);
  void IncludeScript(zilchCode code, zilchFile origin);
  //void IncludeLibrary(LibraryRef library);

  static void DebugPrintBoundType(BoundType * testType);

  //// Helper functions for Zilch Classes ////

  // Given the name of a zilch type, return pointer to its BoundType.
  BoundType* GetBoundType(std::string name);
  // Given the name of a field on a given bound type, return pointer to the field.
  Field* GetTypeField(BoundType* boundType, std::string fieldName);
  
  Function* GetFunction(
    BoundType* boundType, std::string funcName,
    Type* returnType = ZilchTypeId(void), const Array<Type*>& parameters = Array<Type*>(),
    FindMemberOptions::Flags options = FindMemberOptions::None );
  
  Function* GetStaticFunction(
    BoundType* boundType, std::string funcName,
    Type* returnType = ZilchTypeId(void), const Array<Type*>& parameters = Array<Type*>() );

  Handle AllocateType(BoundType *boundType, HeapFlags::Enum flags = HeapFlags::NonReferenceCounted);


  //// Public Member Variables

  ExecutableState* state_;
  LibraryRef       library_;

  // The exception report stores any exceptions that may have occurred while executing code
  // Exceptions include accessing arrays out of bounds, dereferencing null, etc
  // You can check 'report.HasThrownExceptions()' to see if the script threw an exception
  // This is useful if you want to stop a particular script from running again, or abort the program
  ExceptionReport  report_;

private:


  //// Private Member Functions

  // Compile the zilch library and state. Will compile files currently in scripts_.
  void CompileZilchState();
  
  // Clean up the zilch library and state. NOTE: scripts_ persists through clean.
  void CleanZilchState();


  //// Private Member Variables

  // Any one time startup and static initialization Zilch needs to do
  // This also registers a custom assertion handler (Zilch code has many user friendly asserts!)
  // NOTE: MUST BE INITIALIZED BEFORE any Zilch 'project'.
  ZilchSetup setup_;

  // Create a list of dependent libraries.
  // A side note: the Core library in Zilch is always added as a dependency, because Core includes
  // things like Integer, Boolean, Real, the basic vector types, String, etc
  Module dependencies_;

  std::unordered_map<zilchOrigin, zilchCode> scripts_;
  std::unordered_map<zilchFile, bool>        scriptFiles_;

};



// Zilch Binding Helper Macros

#define DefineType(Type, Library) ZilchDefineType(Type, #Type, Library, builder, type)
#define BindConstructor() ZilchBindConstructor(builder, type, ZilchSelf, ZilchNoNames)
#define BindDestructor() ZilchBindDestructor(builder, type, ZilchSelf)
#define BindVirtualConstructor(...) ZilchBindConstructorVirtual(builder, type, ZilchSelf, ZilchNoNames, __VA_ARGS__)

#define BindMethod(Method) ZilchBindMethod(builder, type, &ZilchSelf::Method, ZilchNoOverload, #Method, ZilchNoNames)
#define BindMethodAs(Method, Name) ZilchBindMethod(builder, type, &ZilchSelf::Method, ZilchNoOverload, Name, ZilchNoNames)

#define BindMethodOverload(Method, ReturnType, ...) (ZilchBindMethod(builder, type, &ZilchSelf::Method, (ReturnType (ZilchSelf::*)(__VA_ARGS__)), #Method, ZilchNoNames))
#define BindMethodOverloadAs(Method, Name, ReturnType, ...) (ZilchBindMethod(builder, type, &ZilchSelf::Method, (ReturnType (ZilchSelf::*)(__VA_ARGS__)), Name, ZilchNoNames))

#define BindStaticMethod(Method) ZilchBindMethod(builder, type, &ZilchSelf::Method, ZilchNoOverload, #Method, ZilchNoNames)
#define BindStaticMethodAs(Method, Name) ZilchBindMethod(builder, type, &ZilchSelf::Method, ZilchNoOverload, Name, ZilchNoNames)

#define BindStaticMethodOverload(Method, ReturnType, ...) (ZilchBindMethod(builder, type, ZilchSelf::Method, (ReturnType (*)(__VA_ARGS__)), #Method, ZilchNoNames))
#define BindStaticMethodOverloadAs(Method, Name, ReturnType, ...) (ZilchBindMethod(builder, type, ZilchSelf::Method, (ReturnType (*)(__VA_ARGS__)), Name, ZilchNoNames))

#define BindFieldGet(Type) (ZilchBindField(builder, type, (&ZilchSelf::Type), #Type, Zilch::PropertyBinding::Get))
#define BindFieldSet(Type) (ZilchBindField(builder, type, (&ZilchSelf::Type), #Type, Zilch::PropertyBinding::Set))
#define BindFieldGetSet(Type) (ZilchBindField(builder, type, (&ZilchSelf::Type), #Type, Zilch::PropertyBinding::GetSet))

#define BindFieldGetAs(Type, Name) (ZilchBindField(builder, type, (&ZilchSelf::Type), Name, Zilch::PropertyBinding::Get))
#define BindFieldSetAs(Type, Name) (ZilchBindField(builder, type, (&ZilchSelf::Type), Name, Zilch::PropertyBinding::Set))
#define BindFieldGetSetAs(Type, Name) (ZilchBindField(builder, type, (&ZilchSelf::Type), Name, Zilch::PropertyBinding::GetSet))

#define BindStaticFieldGet(Type) (ZilchBindField(builder, type, (&ZilchSelf::Type), #Type, Zilch::PropertyBinding::Get))
#define BindStaticFieldSet(Type) (ZilchBindField(builder, type, (&ZilchSelf::Type), #Type, Zilch::PropertyBinding::Set))
#define BindStaticFieldGetSet(Type) (ZilchBindField(builder, type, (&ZilchSelf::Type), #Type, Zilch::PropertyBinding::GetSet))

#define BindStaticFieldGetAs(Type, Name) (ZilchBindField(builder, type, (&ZilchSelf::Type), Name, Zilch::PropertyBinding::Get))
#define BindStaticFieldSetAs(Type, Name) (ZilchBindField(builder, type, (&ZilchSelf::Type), Name, Zilch::PropertyBinding::Set))
#define BindStaticFieldGetSetAs(Type, Name) (ZilchBindField(builder, type, (&ZilchSelf::Type), Name, Zilch::PropertyBinding::GetSet))

#define BindProperty(Getter, Setter, Name) ZilchBindProperty(builder, type, &ZilchSelf::Getter, &ZilchSelf::Setter, Name)