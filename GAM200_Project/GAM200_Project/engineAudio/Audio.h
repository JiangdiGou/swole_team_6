#ifndef AUDIO_H
#define AUDIO_H

#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h" // Only if you want error checking

#ifdef _WIN32
	#pragma comment(lib, "fmodWin/fmod_vc.lib")
	#pragma comment(lib, "fmodWin/fmodL_vc.lib")
#endif

typedef FMOD::Sound* FMSound;

class FMSoundSys
{
public:
	FMSoundSys();
	FMOD::System *fmodsys;

	void createSound(FMSound *pSound, const char* pFile);
	void playSound(FMSound pSound, bool loop = false);
	void releaseSound(FMSound pSound);
};



#endif
