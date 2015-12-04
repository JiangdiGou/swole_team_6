//All content © 2014 DigiPen (USA) Corporation, all rights reserved.
//*****************************************************************************/
/*!
\file   ZilchBind.h
\author Joshua T. Fisher
\par    email: j.fisher\@digipen.edu
\par    DigiPen login: j.fisher
\par    Course: GAM 200
\date   10/25/2014
\brief
This file contains the functions needed to bind Zilch scripts to our engine.

*/
/******************************************************************************/
#include <memory>

#include "ZilchBind.h"
//#include "Utilities/Utilities.h"

//#include "../ComponentSystem.h"
#include "../Component.h"
#include "../Composition.h"
#include "BindInternal.hpp"
//#include "Core/Space.h"

//#include "ZilchComponentFactory.h"
//#include "ZilchComponent.h"
//#include "ZilchComponent.h"

#define DeclareType(TypeName)                   \
if (userData.Type->Name == #TypeName)           \
{                                               \
  retComp = owner->GetComponent(CT_##TypeName); \
  return retComp;                               \
}                                               
#define DeclareZilchType(TypeName)                   \
if (userData.Type->Name == #TypeName)                \
{                                                    \
  retComp = owner->GetZilchComponent(CTZ_##TypeName); \
  return retComp;                                    \
}                                           


GameComponent* ZilchGetComponent(Zilch::Call& call, Zilch::ExceptionReport& report)
{
  GetComponentUserData& userData = call.GetFunction()->ComplexUserData.ReadObject<GetComponentUserData>(0);

  GameObjectComposition *owner = (GameObjectComposition*)call.GetHandle(Zilch::Call::This).Dereference();
  GameComponent* retComp;

  DeclareType(Transform);
  DeclareType(Camera);
  DeclareType(Sprite);
  DeclareType(SpriteText);
  DeclareType(Body);
  DeclareType(TileMapCollision);
  DeclareType(ShapeAAB);
  DeclareType(ShapeLine);
  DeclareType(GameReactive);
  DeclareType(SoundEmitter);
  DeclareType(PlayerTag);
  DeclareType(HUDcomponent);
  DeclareType(Editable);
  DeclareType(MouseVector);
  DeclareType(PlayerState);
  DeclareType(MenuButton);
  DeclareType(OurZilchComponent); 

  DeclareZilchType(Example);

  return nullptr;
}
#undef DeclareType()

void ZilchGetNativeComponent(Zilch::Call& call, Zilch::ExceptionReport& report)
{
  GetComponentUserData& userData = call.GetFunction()->ComplexUserData.ReadObject<GetComponentUserData>(0);

  GameComponent* foundComponent = ZilchGetComponent(call, report);
  
  Zilch::Handle handle;
  handle.Manager = call.GetState()->GetHandleManager<Zilch::PointerManager>();
  handle.Type = userData.Type;
  handle.Manager->ObjectToHandle((const byte*)foundComponent, handle);

  call.SetHandle(Zilch::Call::Return, handle);
}

/*******************************************************************************
Converts std::string to Zilch::String and back
*******************************************************************************/

/*void ZilchGetZilchComponent(Zilch::Call& call, Zilch::ExceptionReport& report)
{
  ZilchComponent* foundComponent = (ZilchComponent*)ZilchGetComponent(call, report);
  if (foundComponent == nullptr)
    call.SetHandle(Zilch::Call::Return, Zilch::Handle());
  else
    call.SetHandle(Zilch::Call::Return, foundComponent->mZilchBaseComponent);
}*/

  
/******************************************************************************/
/*!
  \brief
    Callback function to be called at compile time that will allow us to get 
    some data about the types the Zilch compiler encounters.

    \param builder
          
    \param scriptType
          
    \param codeUserData
          
    \param userData
      Placeholder for data we place. 
*/
/******************************************************************************/
void ZilchBinder::ZilchParsedType(Zilch::ParseEvent *e)
{
  auto scriptType = e->Type;
  auto builder = e->Builder;
  if (hasRegisteredYteTypes == false)
  {
    // Loop through all types defined in the Yte library (we're looking for components, or things that inherit from Component)
    auto boundTypes = ZLib_Internal::GetInstance().GetLibrary()->BoundTypes.values();
    while (!boundTypes.empty())
    {
      Zilch::BoundType* yteType = boundTypes.front();

      auto name = yteType->Name.c_str();
      boundTypes.popFront();

      if (Zilch::TypeBinding::IsA(yteType, ZilchTypeId(GameComponent)))
      {
        Zilch::Property *ComponentProperty 
                          = builder->AddExtensionProperty(ZilchTypeId(GameObjectComposition), 
                                                          yteType->Name, 
                                                          yteType, 
                                                          nullptr, 
														ZilchGetNativeComponent,
                                                          Zilch::MemberOptions::None);


        GetComponentUserData userData;
        userData.Type = yteType;
        userData.ZilchBinder = this;
        ComponentProperty->Get->ComplexUserData.WriteObject(userData);
      }
    }

    hasRegisteredYteTypes = true;
  }

  /*
  if (Zilch::TypeBinding::IsA(scriptType, ZilchTypeId(ZilchComponent)))
  {
    Zilch::Property *ComponentProperty 
                      = builder->AddExtensionProperty(ZilchTypeId(Core::Composition), 
                                                      scriptType->Name, 
                                                      scriptType, 
                                                      nullptr, 
                                                      ZilchGetZilchComponent, 
                                                      Zilch::MemberOptions::None);
    auto name = scriptType->Name.c_str();

    GetComponentUserData userData;
    userData.Type = scriptType;
    userData.ZilchBinder = this;


    auto it = mZilchFactoryData.find(scriptType);

    if (it == mZilchFactoryData.end())
    {
      mZilchFactoryData.emplace(scriptType, userData);
    }

    ComponentProperty->Get->ComplexUserData.WriteObject(userData);
  }*/
}

/******************************************************************************/
/*!
\brief
Creates a map of strings to unique pointers to a ZilchComponentFactory. It
used r-value references to pass this map back.

\return
r-value reference to said map, for easy std::moving.
*/
/******************************************************************************/
/*
void ZilchBinder::ZilchComponentFactories(std::unordered_map<Zilch::BoundType*, std::unique_ptr<StringComponentFactory> > *currComponentFactories)
{
  for (auto &newFactory : mZilchFactoryData)
  {
    auto it = currComponentFactories->find(newFactory.first);

    if (it == currComponentFactories->end())
    {
      auto factory = std::make_unique<ZilchComponentFactory>();

      factory->mType = newFactory.second.Type;

      Zilch::Array<Zilch::Type*> initParameterTypes;
      factory->mInitialize =  newFactory.second.Type->FindFunction("Initialize", 
                                                                    initParameterTypes, 
                                                                    ZilchTypeId(void), 
                                                                    Zilch::FindMemberOptions::None);

      currComponentFactories->emplace(newFactory.first, std::move(factory));
    }
  }
}*/

void ZilchBinder::Compile(bool isZcc)
{
  hasRegisteredYteTypes = false;
  mProject.Clear();
  mDependencies = Zilch::Module();
      
  //auto allScripts = YTE::Utilities::GetScripts(isZcc);

  //for (auto file : allScripts)
  //{
  //  if (file.second != "..")
   // {
  //    auto pathToFile = file.first.c_str();
   //   auto nameOfFile = file.second.c_str();

   //   mProject.AddCodeFromFile(pathToFile);
  //  }
  //}

  //ZILCH SCRIPTS ADD HERE
  //mProject.AddCodeFromFile("Player.zilch");
  mProject.AddCodeFromFile("Scripts/Example.zilch");
  mProject.AddCodeFromFile("Scripts/BasicAIComponent.zilch");
  mProject.AddCodeFromFile("Scripts/EndOfGame.zilch");
  //mProject.AddCodeFromFile("Scripts/EnemyHealthManager.zilch");
  //mProject.AddCodeFromFile("Scripts/PlayerHealthBar.zilch");
 // mProject.AddCodeFromFile("Scripts/PlayerHeathManager.zilch");


  mDependencies.push_back(ZLib_Internal::GetInstance().GetLibrary());

  mLibrary = mProject.Compile("Ripple", mDependencies, Zilch::EvaluationMode::Project);

  if ((mState != nullptr) && (mLibrary != nullptr))
  {
    mState->PatchLibrary(mLibrary);
  }
}

/******************************************************************************/
/*!
\brief
  ZilchBinder constructor. Will construct th
*/
/******************************************************************************/
ZilchBinder::ZilchBinder(bool isZcc)  
  : mState(nullptr), hasRegisteredYteTypes(false)
{    
  Zilch::EventConnect(&mProject, Zilch::Events::CompilationError, Zilch::DefaultErrorCallback);

  Zilch::EventConnect(&mProject, Zilch::Events::TypeParsed, &ZilchBinder::ZilchParsedType, this);

  Compile(isZcc);

  mDependencies.push_back(ZLib_Internal::GetLibrary());

  if (mLibrary == nullptr)
  {
    if (!isZcc)
      Error("Failed to compile library.");
    return;
  }

  mDependencies.push_back(mLibrary);

  // Link all the libraries together into one ExecutableState
  mState = mDependencies.Link();


  if (mState == nullptr)
  {
    if (!isZcc)
      Error("Failed to link libraries together");
    return;
  }

  Zilch::EventConnect(mState, Zilch::Events::UnhandledException, Zilch::DefaultExceptionCallback);

  //debugger.Host(8000);

  //while (debugger.Server.Connections.empty())
  //{
  //  debugger.Update();
  //  Sleep(0);
  //}

  //debugger.AddProject(&project);
  //debugger.AddState(state);

  // Setup the console so that when we call 'Console.WriteLine' it outputs to stdio
  Zilch::EventConnect(&Zilch::Console::Events,
                      Zilch::Events::ConsoleWrite,
                      Zilch::DefaultWriteText);
}

ZilchBinder::~ZilchBinder()
{
}
