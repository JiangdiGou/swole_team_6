#ifndef SOUND_H
#define SOUND_H

#include"fmod/fmod_studio.hpp"
#include"fmod/fmod_common.h"
#include"fmod/fmod_errors.h"
#include"fmod/common.h"
#include <unordered_map>
#include "../Composition.h"
#include "../System.h"


#pragma  comment (lib, "fmodWin/fmodstudio_vc")


typedef FMOD::Studio::System * SoundSys;
typedef FMOD::Studio::Bank * SoundBank;
typedef std::unordered_map<std::string, FMOD::Studio::EventInstance *> SoundCollection;
typedef std::unordered_map<std::string, FMOD::Studio::EventInstance *>::iterator Soundit;

class SoundManager //: public ISystem
{
	public:
		SoundManager();
		~SoundManager();


		bool Initialize() ;
		void Update(float dt);
		void ShutDown();

		bool PlayEvent(std::string name);
		bool StopSound(std::string name);
		void Pause(bool pause, std::string name);
		void PauseAll();
		void StopAll(void);
		void ResumeAll(void);
		void Resume();
		void Volume(float vol, std::string name);

	private:
		SoundSys m_Sys;
		SoundBank m_AmbienceBank;
		SoundBank m_MusicBank;
		SoundBank m_Mainmenu;
		SoundBank m_MasterBank;
		SoundBank m_StringBank;
		SoundCollection m_LoopSounds;
};

extern SoundManager * sound;



#endif