

#include "SoundEmitter.h"
#include "../Engine.h"

SoundEmitter::SoundEmitter(GameObjectComposition* Owner) : playSoundOnStart(false)
{

}

SoundEmitter::~SoundEmitter()
{

}

void SoundEmitter::Initialize()
{
	//CoreEngine * engine;
	//m_manager = engine->m_Sound;
	if (playSoundOnStart)
		PlayEvent(startSound);
}
void SoundEmitter::Update(float dt)
{

}
void SoundEmitter::Release()
{
	
}

void SoundEmitter::PlayEvent(std::string name)
{
	m_manager->PlayEvent(name);
}

void SoundEmitter::StopEvent(std::string name)
{
	if (playSoundOnStart)
		StopEvent(startSound);
}
void SoundEmitter::SetPause(bool pause, std::string name)
{
	if (pause == true)
		m_manager->Pause(true,name);
	else
		m_manager->Pause(false,name);
}

void SoundEmitter::SetVolume(float vol, std::string name)
{
	m_manager->Volume(vol, name);
}

