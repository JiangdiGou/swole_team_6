#include "editorTilemapTools.h"

EditorTilemapTools::EditorTilemapTools()
{
  currentTexture = " ";
  recentTextures.assign(3, "");
  recentTopLefts.assign(3, ImVec2(0, 0));
  recentBotRights.assign(3, ImVec2(0, 0));
}

void EditorTilemapTools::handle()
{
  TextureAtlas* atlas = GRAPHICS->getSpriteAtlas();

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

  for (std::vector<std::string>::iterator it = FACTORY->textureKey.begin();
    it != FACTORY->textureKey.end(); ++it)
  {
    int index = it - FACTORY->textureKey.begin();

    //Creates a grid by calling SameLine every frame except when time for new row
    if (!(index % 6 == 0))
      ImGui::SameLine();

    //Gets the texture's info for displaying in imgui
    AtlasTexture texture = atlas->textures[*it];
    ImVec2 topLeft = ImVec2(texture.getLeftX(), texture.getTopY());
    ImVec2 botRight = ImVec2(texture.getRightX(), texture.getBottomY());

    ImGui::PushID(index);
    //Displays image buttons of textures
    if (ImGui::ImageButton((ImTextureID)atlas->ID, ImVec2(64, 64), topLeft, botRight))
    {
      currentTexture = *it;
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


void EditorTilemapTools::changeTile(GameObjectComposition* tile)
{
  if (!(currentTexture.size() > 2))
  {
    setupMessage("No tile selected or error in selection.", ImVec4(1, 0, 0, 1));
    return;
  }

  //You will change the number in the file here, but not till digit thing fixed.
  Sprite* tSprite = (Sprite*)(tile->GetComponent(CT_Sprite));
  if (tSprite)
  {
    bool wasEmpty;
    if (tSprite->texture == GRAPHICS->getSpriteAtlas()->textures["emptyTile"])
      wasEmpty = true;
    else
      wasEmpty = false;

    TextureAtlas* pAtlas = GRAPHICS->getSpriteAtlas();
    tSprite->texture = pAtlas->textures[currentTexture];

    int index = 0;

    //Find the index of texture in texture key. texture key might need to be improved. mess right now.
    for (std::vector<std::string>::iterator it = FACTORY->textureKey.begin();
      it != FACTORY->textureKey.end(); ++it)
    {
      index = it - FACTORY->textureKey.begin();
      if (*it == currentTexture)
        break;
    }

    Transform* pTransform = tile->has(Transform);
    FACTORY->tileMap[(int)pTransform->GetPositionY()][(int)pTransform->GetPositionX()] = index;

    //I wanted to have it so that if you make it a tile it has collision
    //but something about how im doing it below is wrong. 

    /*
    if (currentTexture != "emptyTile" && wasEmpty)
    {
    Body * tileBody = new Body();
    tileBody->Mass = 0;
    tileBody->Restitution = 0.3f;
    tileBody->Friction = 0.0f;
    ShapeAAB * boxCollider = new ShapeAAB();
    boxCollider->Extents = Vec2D(.5, .5);
    tileBody->BodyShape = boxCollider;
    tile->AddComponent(CT_Body, tileBody);
    tile->AddComponent(CT_ShapeAAB, boxCollider);

    tileBody->Initialize();
    boxCollider->Initialize();
    }*/



  }
}
