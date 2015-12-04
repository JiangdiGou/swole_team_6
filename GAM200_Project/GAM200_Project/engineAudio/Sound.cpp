/*****************************************************************************/
/*!
\file    Sound.cpp
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
the implementation for the base sound load/play functions using FMOD studio
with bank file supported.
\remarks


All content 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//#include "Precompiled.h"
#include "Sound.h"
#include <iostream>
SoundManager * sound = nullptr;


SoundManager::SoundManager() : ISystem(), m_Sys(nullptr), m_MasterBank(nullptr), m_StringsBank(nullptr)
{
	sound = this;
}

SoundManager::~SoundManager()
{

}


//    MessageBox(NULL, "ERROR: Could not create Sound System", 
//      strcpy(text, strcat("Error: ", system_name)), NULL);
//
//    return false;
//  }

void SoundManager::Initialize()
{
	FMOD_RESULT result_;
	// here we create our sound system
	char text[200];
	
	result_ = FMOD::Studio::System::create(&m_Sys);
	if (result_ != FMOD_OK)
	{
		std::cout << result_ << std::endl;
		printf("sound created?");
		//return;
	}
  //For later... check for errors


	if (m_Sys->initialize(1024, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_NORMAL, 0))
	{
		printf("Bank creation initialized\n");
		//return;
	}
	
	result_ = m_Sys->loadBankFile("resources/Audio/Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_MasterBank);
	if (result_ != FMOD_OK)
	{
		std::cout << result_ << std::endl;
		printf("shit happenes1\n");
	}

	result_ = m_Sys->loadBankFile("resources/Audio/Ambience.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_AmbienceBank);
	if (result_ != FMOD_OK)
	{
		std::cout << result_ << std::endl;
		printf("shit happenes2\n");
	}

	result_ = m_Sys->loadBankFile("resources/Audio/RealBGM.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_MusicBank);
	if (result_ != FMOD_OK)
	{
		std::cout << result_ << std::endl;
		printf("shit happenes3\n");
	}

	result_ = m_Sys->loadBankFile("resources/Audio/Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_StringsBank);
	if (result_ != FMOD_OK)
	{
		std::cout << result_ << std::endl;
		printf("shit happenes4\n");
	}

	return;
}


void SoundManager::Update(float dt)
{
	m_Sys->update();
}


void SoundManager::ShutDown()
{
	// we loop through the sounds list and call the built in release function
	for (Soundit iter = m_LoopSounds.begin(); iter != m_LoopSounds.end(); iter++)
	{
		iter->second->release();
	}
	// release the string bank;
	m_StringsBank->unload();	
	m_MasterBank->unload();
	//
	m_Sys->unloadAll();
	m_Sys->release();
}

bool SoundManager::PlayEvent(std::string name)
{
	FMOD::Studio::EventDescription * SoundDescription = NULL;
	FMOD::Studio::EventInstance * SoundInstance = nullptr;

	std::string temptext = "event:/" + name;

	FMOD_RESULT SoundResult = m_Sys->getEvent(temptext.c_str(), &SoundDescription);

	if (SoundResult == FMOD_ERR_EVENT_NOTFOUND)
	{
		return false;
	}

	SoundDescription->createInstance(&SoundInstance);
	bool OneShot;
	//properties access
	SoundDescription->isOneshot(&OneShot);

	//if we cant find the music file in the list
	if (!OneShot && m_LoopSounds.find(name) != m_LoopSounds.end())
	{
		return false;
	}

	// start the sound
	SoundInstance->start();

	if (OneShot)
		SoundInstance->release();
	else
		m_LoopSounds.insert(std::pair<std::string, FMOD::Studio::EventInstance *>(name, SoundInstance));

	return true;
}


bool SoundManager::StopSound(std::string name)
{
	if (m_LoopSounds.find(name) == m_LoopSounds.end())
		return true;
	if (m_LoopSounds[name]->isValid())
	{
		FMOD_STUDIO_PLAYBACK_STATE rock;
		m_LoopSounds[name]->getPlaybackState(&rock);

		m_LoopSounds[name]->setPaused(true); // Don't neet to pause before stopping.
		m_LoopSounds[name]->stop(FMOD_STUDIO_STOP_IMMEDIATE);

		m_LoopSounds[name]->getPlaybackState(&rock);

		m_LoopSounds[name]->release();
	}


    m_LoopSounds.erase(name);
	return true;
}


void SoundManager::Pause(bool pauseSound, std::string name)
{
	m_LoopSounds[name]->setPaused(pauseSound);
}


void SoundManager::PauseAll()
{
	for (Soundit it = m_LoopSounds.begin(); it != m_LoopSounds.end(); ++it)
	{
		FMOD_RESULT myfuckingresult = it->second->setPaused(true);
		int randonum = 0;
	}
}

void SoundManager::StopAll()
{
	for (Soundit it = m_LoopSounds.begin(); it != m_LoopSounds.end(); ++it)
	{
		FMOD_RESULT myfuckingresult = it->second->setPaused(true);
		int randonum = 0;
	}
}

void SoundManager::ResumeAll()
{
	for (Soundit it = m_LoopSounds.begin(); it != m_LoopSounds.end(); ++it)
	{
		FMOD_RESULT myfuckingresult = it->second->setPaused(false);
		int randonumshit = 9;
	}
}


void SoundManager::Volume(float vol, std::string name)
{
	m_LoopSounds[name]->setVolume(vol);
}
