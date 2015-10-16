#include "../_EntryPoint.h"
#include "Audio.h"

FMSoundSys::FMSoundSys()
{
	if (FMOD::System_Create(&fmodsys) != FMOD_OK)
	{
		return;
	}

	int drivers = 0;
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
		sound->setMode(FMOD_LOOP_OFF);
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
	//sound.Initialize();

	// Create a sample sound
	FMSound soundSample;
	sound.createSound(&soundSample, "resources//audio//help.wav");

	// Play the sound, with loop mode
	sound.playSound(soundSample, true);

	// Do something meanwhile...
	while (true)
	{

	}

	// Release the sound
	sound.releaseSound(soundSample);
}