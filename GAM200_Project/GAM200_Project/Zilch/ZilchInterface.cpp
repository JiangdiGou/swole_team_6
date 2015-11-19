#include "ZilchInterface.hpp"
#include "BindInternal.hpp"
#include <iostream>

using namespace Zilch;

ZilchInterface::ZilchInterface()
  : state_(nullptr)
  , setup_(StartupFlags::None)
{
  // Setup the console so that when we call 'Console.WriteLine' it outputs to stdio
  EventConnect(&Console::Events, Events::ConsoleWrite, DefaultWriteText);

  // We can also setup the console so that any 'Read' functions will attempt to read from stdin
  EventConnect(&Console::Events, Events::ConsoleRead, DefaultReadText);
}


ZilchInterface::~ZilchInterface()
{
  Shutdown();
}


void ZilchInterface::Init()
{
  CleanZilchState();
  CompileZilchState();
}


void ZilchInterface::Shutdown()
{
  CleanZilchState();
}

void ZilchInterface::CompileZilchState()
{

  // A project contains all of the code we combine together to make a single Zilch library
  // The project also sends events for compilation errors that occur (includes friendly messages / error codes)
  Project script_project;
  // Here, we can register our own callback for when compilation errors occur
  // The default callback prints the file, line/character number, and message to stderr
  EventConnect(&script_project, Events::CompilationError, DefaultErrorCallback);

  // include our static libraries:
  dependencies_.push_back(ZLib_Internal::GetLibrary());


  // setting up library from scripts:

  // 1. Add code from scripts stored so far.
  for (auto pair : scripts_)
    script_project.AddCodeFromString(pair.second.c_str(), pair.first.c_str());

  // 2. Add code from script files set so far.
  for (auto pair : scriptFiles_)
  {
    bool success = script_project.AddCodeFromFile(pair.first.c_str());
    ErrorIf(!success, std::string("Failed to compiler library '" + pair.first + "'").c_str() );
  }

  // Compile all the code we added together into a single library named "GG_Scripts"
  // We already know this is going to fail to compile, so the error callback
  // we provided above should get called
  library_ = script_project.Compile("GG_Scripts", dependencies_, EvaluationMode::Project);
  ErrorIf(library_ == nullptr, "Failed to compiler library");

  // We want to link together all the libraries that we depended upon, along with our own library
  dependencies_.push_back(library_);

  state_ = dependencies_.Link();
  ErrorIf(state_ == nullptr, "Failed to link libraries together");
}


void ZilchInterface::CleanZilchState()
{
  // make sure to clean up the state variable.
  if (state_)
  {
    delete state_;
    state_ = nullptr;
  }

  // clean exception report
  report_.Clear();

  // clean dependencies
  dependencies_.clear();
  // make sure to re-include the core libraries
  dependencies_.push_back(Zilch::Core::GetInstance().GetLibrary());

  // note: we do NOT remove scripts from our script_ map or scriptFiles_ map
}


void ZilchInterface::IncludeScriptFile(zilchFile filepath)
{
  scriptFiles_[filepath] = true;
}


void ZilchInterface::IncludeScript(zilchCode code, zilchFile origin)
{
  scripts_[origin] = code;
}


void ZilchInterface::DebugPrintBoundType(BoundType * testType)
{
  Console::Write(testType->Name);
  Console::Write(" : ");
  if (testType->BaseType != NULL)
  {
    Console::WriteLine(testType->BaseType->ToString());
  }
  else
  {
    Console::WriteLine("<NO PARENT CLASS>");
  }

  Console::WriteLine("\n - Properties: (Base)");
  for (auto prop : testType->AllProperties)
  {
    Console::Write("   - ");
    Console::Write(prop->Name);
    Console::Write(" : ");
    Console::WriteLine(prop->PropertyType->ToString());
  }

  Console::WriteLine("\n - Functions: (Base)");
  for (auto func : testType->AllFunctions)
  {
    Console::Write("   - ");
    Console::Write(func->Name);
    Console::Write(" : ");
    Console::WriteLine(func->FunctionType->Return->ToString());
    for (auto param : func->FunctionType->Parameters)
    {
      Console::Write("     - ");
      Console::Write(param.Name);
      Console::Write(" : ");
      Console::WriteLine(param.ParameterType->ToString());
    }
  }

  if (testType->BaseType != NULL)
  {
    Console::Write("\n - Properties: (Inherited from '");
    Console::Write(testType->BaseType->ToString());
    Console::Write("')");
    for (auto prop : testType->BaseType->AllProperties)
    {
      Console::Write("   - ");
      Console::Write(prop->Name);
      Console::Write(" : ");
      Console::WriteLine(prop->PropertyType->ToString());
    }

    Console::Write("\n - Functions: (Inherited from '");
    Console::Write(testType->BaseType->ToString());
    Console::WriteLine("')");
    for (auto func : testType->BaseType->AllFunctions)
    {
      Console::Write("   - ");
      Console::Write(func->Name);
      Console::Write(" : ");
      Console::WriteLine(func->FunctionType->Return->ToString());
      for (auto param : func->FunctionType->Parameters)
      {
        Console::Write("     - ");
        Console::Write(param.Name);
        Console::Write(" : ");
        Console::WriteLine(param.ParameterType->ToString());
      }
    }
  }
  else
  {
    //Console::WriteLine("<NO PARENT CLASS>");
  }
  Console::Write("\n");
}







//void ZilchInterface::IncludeLibrary(LibraryRef library)
//{ }

BoundType* ZilchInterface::GetBoundType(std::string typeName)
{
  BoundType* foundType = library_->BoundTypes.findValue(typeName.c_str(), nullptr);
  ErrorIf(foundType == nullptr, std::string("Failed to find a Zilch type named '" + typeName + "'").c_str());
  return foundType;
}


Field* ZilchInterface::GetTypeField(BoundType* boundType, std::string fieldName)
{
  Field* foundField = boundType->InstanceFields.findValue(fieldName.c_str(), nullptr);
  ErrorIf(foundField == nullptr, std::string("Failed to find field '" + fieldName + "' on Zilch type " + boundType->Name.c_str()).c_str());
  return foundField;
}


Function* ZilchInterface::GetFunction(
  BoundType* boundType,
  std::string funcName,
  Type* returnType,
  const Array<Type*>& parameters,
  FindMemberOptions::Flags options)
{
  Function* foundFunction = boundType->FindFunction(funcName.c_str(), parameters, returnType, options);
  ErrorIf(foundFunction == nullptr, std::string("Failed to find function '" + funcName + "' on Zilch type " + boundType->Name.c_str()).c_str());
  return foundFunction;
}


Function* ZilchInterface::GetStaticFunction(
  BoundType* boundType,
  std::string funcName,
  Type* returnType,
  const Array<Type*>& parameters)
{
  Function* foundFunction = boundType->FindFunction(funcName.c_str(), parameters, returnType, FindMemberOptions::Static);
  ErrorIf(foundFunction == nullptr, std::string("Failed to find static function '" + funcName + "' on Zilch type " + boundType->Name.c_str()).c_str());
  return foundFunction;
}


// It is legal to allocate Zilch objects that have no defined default constructor
// The object will first be entirely set to zero (all null and zero values)
// Then the pre-constructor will run, which initializes any members in the class to the value after the '='
Handle ZilchInterface::AllocateType(BoundType *boundType, HeapFlags::Enum flags)
{
  return state_->AllocateDefaultConstructedHeapObject(boundType, report_, flags);
}


