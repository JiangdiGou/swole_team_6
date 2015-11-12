/*****************************************************************************/
/*!
\file    Sound.h
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
the header file for the base sound manager class.
\remarks


All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/

#ifndef SOUND_H
#define SOUND_H

#include"fmod/fmod_studio.hpp"
#include"fmod/fmod_common.h"
#include"fmod/fmod_errors.h"
#include"fmod/common.h"
#include <unordered_map>
#include "../Composition.h"
#include "../System.h"
//#include "SoundEmitter.h"


#pragma  comment (lib, "fmodWin/fmodstudio_vc")


typedef FMOD::Studio::System * SoundSys;
typedef FMOD::Studio::Bank * SoundBank;
typedef std::unordered_map<std::string, FMOD::Studio::EventInstance *> SoundCollection;
typedef std::unordered_map<std::string, FMOD::Studio::EventInstance *>::iterator Soundit;

class SoundManager : public ISystem
{
	public:
		SoundManager();
		~SoundManager();


		void Initialize() override;
		void Update(float dt)override;
		void ShutDown();

		bool PlayEvent(std::string name);
		bool StopSound(std::string name);
		void Pause(bool pause, std::string name);
		void PauseAll();
		void StopAll(void);
		void ResumeAll(void);
		void Resume(void);
		void Volume(float vol, std::string name);

	private:
		SoundSys m_Sys;
		SoundBank m_AmbienceBank;
		SoundBank m_MusicBank;
		SoundBank m_MasterBank;
		SoundBank m_StringsBank;
		SoundCollection m_LoopSounds;
};

extern SoundManager * sound;



#endif