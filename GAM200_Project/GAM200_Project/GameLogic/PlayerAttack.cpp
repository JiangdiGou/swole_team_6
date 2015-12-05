#include "PlayerAttack.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"
#include "EnemyHealthManager.h"
#include "../engineAudio/SoundEmitter.h"
#include "../Editor/Defines.h"

//playerstate component for reference
void PlayerAttack::Initialize()
{
	parent = GetOwner();
	pTransform = parent->has(Transform);

	pSprite = parent->has(Sprite);
  if (pSprite)
    pSprite->setLayer(1);

  playerBody = parent->has(Body);

  slashTimer = 0.4;

#ifdef EDITOR
  //CanMove = false;
#else
  //CanMove = true;
#endif
}

void PlayerAttack::Update(float dt)
{
  if (!CanSlash && slashTimer > 0.0)
  {
    slashTimer -= dt;
  }
  else if (!CanSlash && slashTimer <= 0)
  {
    playerBody->SetVelocity(Vec2D(0,0));

    pSprite->setTexture("Character");

    slashTimer = 0.4;
    CanSlash = true;
  }
}

void PlayerAttack::Attack(std::vector <GameObjectComposition*> objectsHit, Vec2D start, Vec2D end)
{
#ifndef EDITOR
  if (CanSlash)
  {
    CanSlash = false;

    Vec2D temp = start;

    pSprite->setTexture("CharacterSlash");

    if ((temp.x < 5) && (temp.y < 5))
    {
      temp.x = end.x - start.x;
      temp.y = end.y - start.y;
    }
    else
    {
      temp.x = (end.x - start.x) / 1.5;
      temp.y = (end.y - start.y) / 1.5;
    }

    //std::cout << "Slice Vec" << temp << "\n";
    Vec2D temp2 = temp.Normalize();

    playerBody->SetVelocity(playerBody->Velocity + (temp2 * 20));

    for (std::vector<GameObjectComposition*>::iterator it = objectsHit.begin(); it != objectsHit.end(); ++it)
    {
      if ((*it)->GetName() == "Enemy ")
      {
        GOC *refedEnemy = (*it);
        EnemyHealthManager *refedEHM = refedEnemy->has(EnemyHealthManager);
        refedEHM->UpdateHealth(-20);

        //Play the sword hit sound
        SoundEmitter* emitter = reinterpret_cast<SoundEmitter*>(LOGIC->player->GetComponent(CT_SoundEmitter));
        emitter->SetVolume(1.0f, "SwordHitOrganic");
        emitter->StopEvent("SwordHitOrganic");
        emitter->PlayEvent("SwordHitOrganic");
      }
    }
  }
#endif
}

void PlayerAttack::SendMessages(Message* message)
{
}

void PlayerAttack::SerializeWrite(Serializer& str)
{
	  StreamWrite(str, (int&)TypeId);
	  StreamWrite(str);
}

PlayerAttack::PlayerAttack()
{

}