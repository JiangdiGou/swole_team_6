/*****************************************************************************/
/*!
\file    SoundEmitter.h
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
the header file for the sound emitter class.
\remarks


All content 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
#ifndef SOUNDEMITTER_H
#define SOUNDEMITTER_H

#include "Sound.h"
#include "../Core.h"
#include "../Zilch/BindInternal.hpp"
#include "../Zilch/Zilch.hpp"

using namespace Zilch;

class SoundEmitter;

class SoundEmitter : public GameComponent
{
public:
  ZilchDeclareDerivedType(SoundEmitter, GameComponent);
	SoundEmitter() {};
	SoundEmitter(GameObjectComposition *Owner);
	~SoundEmitter();

	void Initialize() override;
	void Update(float dt) override;
	void Release() override;

	void PlayEvent(std::string name);
	void StopEvent(std::string name);
	void BeQuiet();
	void Rock();
	void SetPause(bool pause, std::string name);
	void SetVolume(float vol, std::string name);

  void SerializeRead(Serializer& str) override;
  void SerializeWrite(Serializer& str) override;

	//Set in editor (optional, see segment in FactoryManager)
	bool playSoundOnStart;
	std::string startSound;
private:
	// Core
	SoundManager* m_manager;


};

#endif