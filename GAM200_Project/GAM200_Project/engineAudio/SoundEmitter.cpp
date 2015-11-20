/*****************************************************************************/
/*!
\file    SoundEmitter.cpp
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
Gettors/Settors for the sound 
\remarks


All content © 2015 DigiPen (USA) Corporation, all rights reserved.
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
}

void SoundEmitter::Rock()
{
	m_manager->ResumeAll();
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