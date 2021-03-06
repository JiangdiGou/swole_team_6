/*****************************************************************************/
/*!
\file    SoundEmitter.cpp
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
Gettors/Settors for the sound 
\remarks


All content 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/

#include "SoundEmitter.h"
#include "../Engine.h"

SoundEmitter::SoundEmitter(GameObjectComposition* Owner) : playSoundOnStart(true)
{

}

void SoundEmitter::Initialize()
{
	// * engine;
	m_manager = sound;
	if (playSoundOnStart)
		PlayEvent(startSound);
	
}

SoundEmitter::~SoundEmitter()
{
	if (playSoundOnStart)
		StopEvent(startSound);
}


void SoundEmitter::PlayEvent(std::string name)
{
	m_manager->PlayEvent(name);
}

void SoundEmitter::StopEvent(std::string name)
{
	m_manager->StopSound(name);
}
void SoundEmitter::SetPause(bool pause, std::string name)
{
	if (pause == true)
		m_manager->Pause(true,name);
	else
		m_manager->Pause(false,name);
}

void SoundEmitter::BeQuiet()
{
	m_manager->PauseAll();
	m_manager->Update(0.0f);
}

void SoundEmitter::Rock()
{
	m_manager->ResumeAll();
	m_manager->Update(0.0f);
}

void SoundEmitter::SetVolume(float vol, std::string name)
{
	m_manager->Volume(vol, name);
}

void SoundEmitter::Update(float dt)
{

}
void SoundEmitter::Release()
{

}

void SoundEmitter::SerializeRead(Serializer& str)
{
  StreamRead(str, playSoundOnStart);
  StreamRead(str, startSound);
}
void SoundEmitter::SerializeWrite(Serializer& str)
{
  StreamWrite(str, playSoundOnStart);
  StreamWrite(str);
  StreamWrite(str, startSound);
  StreamWrite(str);
}

ZilchDefineType(SoundEmitter, "SoundEmitter", ZLib_Internal, builder, type)
{
  type->HandleManager = ZilchManagerId(PointerManager);
  ZilchBindConstructor(builder, type, SoundEmitter, ZilchNoNames);
  ZilchBindDestructor(builder, type, SoundEmitter);

  //ZilchBindMethod(builder, type, &SoundEmitter::PlayEvent, ZilchNoOverload, "PlayEvent", ZilchNoNames);
  //ZilchBindMethod(builder, type, &SoundEmitter::StopEvent, ZilchNoOverload, "StopEvent", ZilchNoNames);
  ZilchBindMethod(builder, type, &SoundEmitter::BeQuiet, ZilchNoOverload, "BeQuiet", ZilchNoNames);
  ZilchBindMethod(builder, type, &SoundEmitter::Rock, ZilchNoOverload, "Rock", ZilchNoNames);
  //ZilchBindMethod(builder, type, &SoundEmitter::SetPause, ZilchNoOverload, "SetPause", ZilchNoNames);
  //ZilchBindMethod(builder, type, &SoundEmitter::SetVolume, ZilchNoOverload, "SetVolume", ZilchNoNames);

  ZilchBindField(builder, type, &SoundEmitter::playSoundOnStart, "playSoundOnStart", PropertyBinding::GetSet);
  //ZilchBindField(builder, type, &SoundEmitter::startSound, "startSound", PropertyBinding::GetSet);
}