/******************************************************************************/
/*!
\author Conor Lavelle

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "editorTilemapTools.h"

EditorTilemapTools::EditorTilemapTools()
{
  currentTexture = " ";
  recentTextures.assign(3, "");
  recentTopLefts.assign(3, ImVec2(0, 0));
  recentBotRights.assign(3, ImVec2(0, 0));
}

void EditorTilemapTools::init()
{
  atlas = GRAPHICS->getSpriteAtlas();
}

void EditorTilemapTools::handle()
{
  if (ImGui::Checkbox("Active", &active))
  {
    if (active)
      emptyTilesVisible(true);
    else
      emptyTilesVisible(false);
  }

  if (!active)
    return;

  ImGui::Text("Curr: ");
  
  //If you have something selected, display it. 
  if (currentTexture.size() > 5)
  {
    ImGui::SameLine();
    ImGui::Image((ImTextureID)atlas->ID, ImVec2(64, 64), currentTopLeft, currentBotRight);
  }

  ImGui::SameLine();
  ImGui::Text("Recent: ");

  handleMessage();

  /*
  for (std::list<ImVec2>::iterator tIt = recentTopLefts.begin(), bIt = recentBotRights.begin();
    tIt != recentTopLefts.begin() || bIt != recentBotRights.begin(); ++tIt, ++bIt)
  {
    ImGui::SameLine();
    ImGui::ImageButton((ImTextureID)atlas->ID, ImVec2(64, 64), *tIt, *bIt);
  }
  */

  int counter = 0;
  for (std::map<std::string, AtlasTexture>::iterator it = atlas->textures.begin();
      it != atlas->textures.end(); ++it, ++counter)
  {
    if (it->second.textureName == "E")
    {
      --counter;
      continue;
    }

    //Creates a grid by calling SameLine every frame except when time for new row
    if (!(counter % 6 == 0))
      ImGui::SameLine();


    AtlasTexture texture = (*it).second; 
    //Gets the texture's info for displaying in imgui
    ImVec2 topLeft = ImVec2(texture.getLeftX(), texture.getTopY());
    ImVec2 botRight = ImVec2(texture.getRightX(), texture.getBottomY());

    ImGui::PushID(counter);
    //Displays image buttons of textures
    if (ImGui::ImageButton((ImTextureID)atlas->ID, ImVec2(64, 64), topLeft, botRight))
    {
      currentTexture = texture.textureName;
      currentTopLeft = topLeft;
      currentBotRight = botRight;

      //AddToPreviousArray(currentTexture, currentTopLeft, currentBotRight);

    }
    ImGui::PopID();
  }
}

void EditorTilemapTools::AddToPreviousArray(const std::string &textureName, ImVec2 topLeft, ImVec2 botRight)
{
  //List is guarunteed to have 3 cause this is only thing that modifies list
  //This does -1 +1, which net 0, and list init to 3.
  recentTextures.pop_back();
  recentTopLefts.pop_back();
  recentBotRights.pop_back();

  recentTextures.push_front(textureName);
  recentTopLefts.push_front(topLeft);
  recentBotRights.push_front(botRight);
}


void EditorTilemapTools::changeTile(GameObjectComposition* tile, bool setEmpty)
{
  if (currentTexture.size() < 2)
  {
    setupMessage("No tile selected or error in selection.", ImVec4(1, 0, 0, 1));
    return;
  }

  //You will change the number in the file here, but not till digit thing fixed.
  Sprite* tSprite = (Sprite*)(tile->GetComponent(CT_Sprite));
  if (tSprite)
  {
    bool wasEmpty;
    if (tSprite->texture == GRAPHICS->getSpriteAtlas()->textures["E"])
      wasEmpty = true;
    else
      wasEmpty = false;

    Transform* pTransform = tile->has(Transform);
    TextureAtlas* pAtlas = GRAPHICS->getSpriteAtlas();
    if (setEmpty)
    {
      tSprite->texture = pAtlas->textures["E"];
      FACTORY->tileMap[(int)pTransform->GetPositionY()][(int)pTransform->GetPositionX()] = std::string("E");
    }
    else
    {
      tSprite->texture = pAtlas->textures[currentTexture];
      FACTORY->tileMap[(int)pTransform->GetPositionY()][(int)pTransform->GetPositionX()] = currentTexture;
    }

    //I wanted to have it so that if you make it a tile it has collision
    //but something about how im doing it below is wrong. 

    
    if (currentTexture != "E" && wasEmpty)
    {
      /*
      ShapeAAB* col = (ShapeAAB*)FACTORY->getNewComponent(CT_ShapeAAB);
      Body* body = (Body*)FACTORY->getNewComponent(CT_Body);

      tile->AddComponent(CT_ShapeAAB, col);
      tile->Initialize();
      tile->AddComponent(CT_Body, body);
      tile->Initialize();
      */
    }
  }
}

void EditorTilemapTools::emptyTilesVisible(bool visibility)
{
  for (std::map<int, GameObjectComposition*>::iterator it = FACTORY->gameObjs.begin();
    it != FACTORY->gameObjs.end(); it++)
  {
    GameObjectComposition* goc = it->second;
    Sprite* gocSprite = goc->has(Sprite);

    if (!gocSprite)
      continue;
    else if (gocSprite->texture == atlas->textures["E"])
      gocSprite->visible = visibility;
  }
}
