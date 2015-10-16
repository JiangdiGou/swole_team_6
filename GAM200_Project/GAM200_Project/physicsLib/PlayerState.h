//#include "../Composition.h"
//#include "Trigger.h"
//#include "math_utility.h"
//#include "Body.h"
//#include "BinaryMap.h"
//#include "../WindowsSystem.h"
//
//enum StateList
//{
//    Grounded,
//    Jumping,
//	OnGround,
//	StartJump
//};
//
//class PlayerState : public GameComponent, public CollisionDelegate
//{
//    public:
//		//friend RigidBody;
//        PlayerState();
//        ~PlayerState();
//        
//        void Initialize();
//        void Update(float dt);
//        void Release();
//		void SendMessages(Message *);
//        
//        void PressJump();
//        
//        void HoldJump();
//        void ReleaseJump();
//
//        //Can be modified
//        float *playerRunSpeed;
//        float *playerJumpVelocity;
//
//        int getJumpState(void);
//        float WalkTimer;
//        float getJumpTimer(void);
//
//    private:
//        Vector3 PreviousPlatformPosition;
//        GameObjectComposition* Platform;
//        RigidBody *playerBody;
//        
//        
//        //now we need some functions for player to connect with messaging system.
//		//?????????????
//		//??????????????
//
//        GameObjectComposition* parent;
//
//        StateList MyPlayerState;
//
//
//        bool *variableJumpHeightEnabled;
//        unsigned jumpCount;
//        float JumpTimer;
//        float *variableJumpTime;
//        float *variableJumpPower;
//        float *maxDownwardsVelocity;
//        float *maxUpwardsVelocity;
//        bool jumpButtonReleased; //if the jump button has been released, after jumping, before hitting the ground
//
//        float LastframeDT;
//        bool IsAlive;
//        float DeathCount;
//        float *timeToJumpAfterLeftGround;
//        void OnCollision(GameObjectComposition*);
//		TileMapCollision *playerTileCollision;
//
//
//
//};