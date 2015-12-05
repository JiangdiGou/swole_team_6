#include "QuitGame.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"

//playerstate component for reference
void QuitGame::Initialize()
{
	parent = GetOwner();
	pTransform = parent->has(Transform);

	pSprite = parent->has(Sprite);
  if (pSprite)
    pSprite->setLayer(1);
  
  pReactive = (GameReactive*)GetOwner()->has(GameReactive);

  if (parent->GetName() == "QuitButton ")
  {
	  Type = QB_Quit;
  }
  else if (parent->GetName() == "YesButton ")
  {
	  Type = QB_Yes;
	  pReactive->active = false;
	  pSprite->visible = false;
  }
  else if (parent->GetName() == "NoButton ")
  {
	  Type = QB_No;
	  pReactive->active = false;
	  pSprite->visible = false;
  }
}

void QuitGame::Update(float dt)
{
	if (pReactive != nullptr)
	{
		if (pReactive->mouseDownAndOver())
		{
			SwitchQuitState();
		}
	}
}

void QuitGame::SendMessages(Message* message)
{
}

void QuitGame::SerializeWrite(Serializer& str)
{
	  StreamWrite(str, (int&)TypeId);
	  StreamWrite(str);
}

void QuitGame::SwitchQuitState()
{
	GOC* buttonYes = parent->FindObject("YesButton ");
	GOC* buttonNo = parent->FindObject("NoButton ");
	GOC* buttonReplay = parent->FindObject("PlayAgain ");
	GOC* buttonQuit = parent->FindObject("QuitButton ");

	std::cout << "ReplayButton: " << buttonReplay;

	//if we are wanting the confirmation to show up
	if (Type == QB_Quit)
	{
		std::cout << "Quit button pressed \n";

		if (buttonYes != nullptr || buttonNo != nullptr)
		{
			if (buttonYes->GetComponent(CT_GameReactive) != nullptr)
			{
				GameReactive* reactYes = buttonYes->has(GameReactive);
				reactYes->active = true;

				Sprite* spriteYes = buttonYes->has(Sprite);
				spriteYes->visible = true;
			}

			if (buttonNo->GetComponent(CT_GameReactive) != nullptr)
			{
				GameReactive* reactNo = buttonNo->has(GameReactive);
				reactNo->active = true;

				Sprite* spriteNo = buttonNo->has(Sprite);
				spriteNo->visible = true;
			}

			if (buttonReplay->GetComponent(CT_GameReactive) != nullptr)
			{
				GameReactive* reactReplay = buttonReplay->has(GameReactive);
				reactReplay->active = false;

				Sprite* spriteReplay = buttonReplay->has(Sprite);
				spriteReplay->visible = false;
			}

			if (buttonQuit->GetComponent(CT_GameReactive) != nullptr)
			{
				GameReactive* reactQuit = buttonQuit->has(GameReactive);
				reactQuit->active = false;

				Sprite* spriteQuit = buttonQuit->has(Sprite);
				spriteQuit->visible = false;
			}

			
		}
		/*else
		{
			std::cout << "something is null. " << buttonYes << ", " << buttonNo << "\n";
		}*/
	}
	//if we are wanting the confirmation to go away
	else if (Type == QB_No)
	{
		std::cout << "No button pressed \n";

		std::cout << "Clicked No button";
		if (buttonYes->GetComponent(CT_GameReactive) != nullptr)
		{
			GameReactive* reactYes = buttonYes->has(GameReactive);
			reactYes->active = false;

			Sprite* spriteYes = buttonYes->has(Sprite);
			spriteYes->visible = false;
		}

		if (buttonNo->GetComponent(CT_GameReactive) != nullptr)
		{
			GameReactive* reactNo = buttonNo->has(GameReactive);
			reactNo->active = false;

			Sprite* spriteNo = buttonNo->has(Sprite);
			spriteNo->visible = false;
		}

		if (buttonReplay->GetComponent(CT_GameReactive) != nullptr)
		{
			GameReactive* reactReplay = buttonReplay->has(GameReactive);
			reactReplay->active = true;

			Sprite* spriteReplay = buttonReplay->has(Sprite);
			spriteReplay->visible = true;
		}

		if (buttonQuit->GetComponent(CT_GameReactive) != nullptr)
		{
			GameReactive* reactQuit = buttonQuit->has(GameReactive);
			reactQuit->active = true;

			Sprite* spriteQuit = buttonQuit->has(Sprite);
			spriteQuit->visible = true;
		}
	}
	else if (Type == QB_Yes)
	{
		CORE->GameActive = false;
	}
}

QuitGame::QuitGame()
{

}