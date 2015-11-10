//#include "Precompiled.h"
#include "Sound.h"


SoundManager * sound = nullptr;


SoundManager::SoundManager() : m_Sys(0), m_MasterBank(0), m_StringBank(0)
{

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
	FMOD_RESULT result;
	// here we create our sound system
	char text[200];
	if (FMOD::Studio::System::create(&m_Sys))
	{
		return;
	}


  //For later... check for errors


	if (m_Sys->initialize(1024, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_NORMAL, 0))
	{
		return;
	}

	result = m_Sys->loadBankFile("resources/Audio/Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_MasterBank);
	if (result != FMOD_OK)
	{
		return;
	}

	result = m_Sys->loadBankFile("resources/Audio/Ambience.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_AmbienceBank);
	if (result != FMOD_OK)
	{
		return;
	}

	result = m_Sys->loadBankFile("resources/Audio/Music.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_MusicBank);
	if (result != FMOD_OK)
	{
		return;
	}

	result = m_Sys->loadBankFile("resources/Audio/Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_StringBank);
	if (result != FMOD_OK)
	{
		return;
	}
	  
}


void SoundManager::Update(float dt)
{
	m_Sys->update();
}


void SoundManager::ShutDown()
{
	for (Soundit iter = m_LoopSounds.begin(); iter != m_LoopSounds.end(); iter++)
	{
		iter->second->release();
	}
	m_StringBank->unload();
	m_MasterBank->unload();
	m_Sys->unloadAll();
	m_Sys->release();
}

bool SoundManager::PlayEvent(std::string name)
{
	FMOD::Studio::EventDescription * SoundDescription = NULL;
	FMOD::Studio::EventInstance * SoundInstance = NULL;

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

	if (!OneShot && m_LoopSounds.find(name) != m_LoopSounds.end())
	{
		return false;
	}

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

		m_LoopSounds[name]->release();
		m_LoopSounds[name]->setPaused(true);
		m_LoopSounds[name]->stop(FMOD_STUDIO_STOP_IMMEDIATE);

		m_LoopSounds[name]->getPlaybackState(&rock);
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
		FMOD_RESULT myfuckingresult = it->second->setPaused(true);
		int randonumshit = 9;
	}
}


void SoundManager::Volume(float vol, std::string name)
{
	m_LoopSounds[name]->setVolume(vol);
}
