/*!
 ********************************************************************************
 \file    Audio.cpp
 \author  Nolan Taeksang Yoo
 \par     Contact: nolan\@projectexist.net
 \par     Classes: FMSoundSys, FMSound
 \brief
 This implements an FMOD sound system (FMSoundSys).
 \remarks
 All content © 2015 DigiPen (USA) Corporation, all rights reserved.
 *******************************************************************************/

#include "../_EntryPoint.h"
#include "Audio.h"

FMSoundSys::FMSoundSys()
{
	if (FMOD::System_Create(&fmodsys) != FMOD_OK)
	{
		return;
	}

	int drivers = 0;
  // Check the bloody hardware.
	fmodsys->getNumDrivers(&drivers);

	if (drivers == 0)
	{
		return;
	}

	// Give instance 36 channels.
	fmodsys->init(36, FMOD_INIT_NORMAL, nullptr);
}

void FMSoundSys::createSound(FMSound *sound, const char* pFile)
{
	fmodsys->createSound(pFile, FMOD_CREATESAMPLE, 0, sound);
}

void FMSoundSys::playSound(FMSound sound, bool loop)
{
	if (!loop)
  {
		sound->setMode(FMOD_LOOP_OFF);
  }
	else
	{
		sound->setMode(FMOD_LOOP_NORMAL);
		sound->setLoopCount(-1);
	}

	fmodsys->playSound(sound, nullptr, false, 0);
}

void FMSoundSys::releaseSound(FMSound sound)
{
	sound->release();
}

#ifdef AUDIOTEST_RUN
int main(int argc, char **argv)
#else
int test(int argc, char **argv)
#endif
{
	// Initialize our sound system
	FMSoundSys sound = *new FMSoundSys();
	//sound.Initialize(); <-- deprecated

	FMSound soundSample;
	sound.createSound(&soundSample, "resources//audio//help.wav");

	// loop the sound
	sound.playSound(soundSample, true);

	// Do something meanwhile...
	while (true)
	{
    //sound plays until released because it looped
	}

	// done with the sound
	sound.releaseSound(soundSample);
}