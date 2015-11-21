/*****************************************************************************/
/*!
\file    PlayerState.h
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
the header file for the player controller
\remarks


All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/

#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include "../Composition.h"
#include "math_utility.h"
#include "Body.h"
#include "BinaryMap.h"
#include "../WindowsSystem.h"
#include "../GameState/GameStateManager.h"
#include "../engineAudio/SoundEmitter.h"

enum StateList
{
    Grounded,
    Jumping,
	OnGround,
	StartJump
};

class PlayerState : public GameComponent//, public CollisionDelegate
{
  friend Body;
  //friend RigidBody;

  public:
      PlayerState();
      ~PlayerState();
        
      void Initialize();
      void Update(float dt);
      void Release();
		  void SendMessages(Message *)override;
      void SerializeRead(Serializer& str) override;
      void SerializeWrite(Serializer& str) override;
        
      void PressJump();
        
      void HoldJump();
      void ReleaseJump();
		  void ripPlayer();
      //Can be modified
		  //everything divide by 80 to fit the value of gravity, because oringinally the 
	    //gravity should be -40.0f but now is -.5, thus adjust9 the value here maybe

	  	// everything divide by 80 if possible
      float playerRunSpeed = 2.925f;   //9.25 oringinally 
		  float playerJumpVelocity = 0.08f;   // originally 0.8

      int getJumpState(void);
      float WalkTimer;
      float getJumpTimer(void);
	  
		  //"Player Run Speed": 9.250000
		  //	"Player Jump Velocity" : 8.510000
		  //	"Variable Jump Height Enabled" : true
	  	//	"Variable Jump Time" : 0.200000
		  //	"Variable Jump Power" : 1.200000
	  	//	"Time To Jump After Leaving Ground" : 0.200000
	  	//	"Max Downwards Velocity" : 40.000000
	  	//	"Max Upwards Velocity" : 20.000000

    private:
		SoundManager * Sysptr;
		SoundEmitter* playerSound;
    Vector3 PreviousPlatformPosition;
    GameObjectComposition* Platform;
    Body *playerBody;
		//TileMapCollision* playerTileCollision;
        
    GameObjectComposition* parent;

    StateList MyPlayerState;

    Sprite* playerSprite;
    AtlasTexture* idleAnimation;
    AtlasTexture* runAnimation;

    Transform* playerTransform;

		

    bool variableJumpHeightEnabled = true;
    unsigned jumpCount;
    float JumpTimer;
    float variableJumpTime = 8.0f;
    float variableJumpPower = 48.0f;
		float maxDownwardsVelocity = 40.0f;//40.0f;
		float maxUpwardsVelocity = 4.0f;//20.0f;
    bool jumpButtonReleased; //if the jump button has been released, after jumping, before hitting the ground

    float LastframeDT;
    bool IsAlive;
    float DeathCount;
    float timeToJumpAfterLeftGround = 0.2f;
    void OnCollision(GameObjectComposition*);
		//TileMapCollision *playerTileCollision;



};

#endif