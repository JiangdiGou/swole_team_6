#ifndef SOUNDEMITTER_H
#define SOUNDEMITTER_H

#include "Sound.h"
#include "../Core.h"

class SoundEmitter;

class SoundEmitter : public GameComponent
{
public:
	SoundEmitter() {};
	SoundEmitter(GameObjectComposition *Owner);
	~SoundEmitter();

	void Initialize() override;
	void Update(float dt) override;
	void Release() override;

	void PlayEvent(std::string name);
	void StopEvent(std::string name);
	void SetPause(bool pause, std::string name);
	void SetVolume(float vol, std::string name);

	//Set in editor (optional, see segment in FactoryManager)
	bool playSoundOnStart;
	std::string startSound;
private:
	// Core
	SoundManager* m_manager;


};

#endif