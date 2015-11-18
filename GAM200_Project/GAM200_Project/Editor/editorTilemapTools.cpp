#include "editorTilemapTools.h"

EditorTilemapTools::EditorTilemapTools()
{
  currentTexture = " ";
  recentTextures = std::list<std::string>();
  recentTopLefts = std::list<ImVec2>();
  recentBotRights = std::list<ImVec2>(); 

}

void EditorTilemapTools::handleTilemapTools()
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

  
  for (std::list<ImVec2>::iterator tIt = recentTopLefts.begin(), bIt = recentBotRights.begin();
    tIt != recentTopLefts.begin() || bIt != recentBotRights.begin(); ++tIt, ++bIt)
  {
    ImGui::SameLine();
    ImGui::ImageButton((ImTextureID)atlas->ID, ImVec2(64, 64), *tIt, *bIt);
  }
 

  ImGui::Separator();

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
    //Displays image button
    if (ImGui::ImageButton((ImTextureID)atlas->ID, ImVec2(64, 64), topLeft, botRight))
    {
      if (recentTextures.size() > 0)
        AddToPreviousArray(currentTexture, currentTopLeft, currentBotRight);

      currentTexture = *it;
      currentTopLeft = topLeft;
      currentBotRight = botRight;

      if (recentTextures.size() == 0)
        AddToPreviousArray(currentTexture, currentTopLeft, currentBotRight);
    }
    ImGui::PopID();
  }
}
/*
void EditorTilemapTools::AddToPreviousArray(const std::string& textureName, ImVec2 topLeft, ImVec2 botRight)
{
  if (prev3Textures[0].size() < 2)
  {
    prev3Textures[0] = textureName;
    prev3TopLeft[0] = topLeft;
    prev3BotRight[0] = botRight;
  }
  else if (prev3Textures[1].size() < 2)
  {
    prev3Textures[1] = textureName;
    prev3TopLeft[1] = topLeft;
    prev3BotRight[1] = botRight;
  }
  else if (prev3Textures[2].size() < 2)
  {
    prev3Textures[2] = textureName;
    prev3TopLeft[2] = topLeft;
    prev3BotRight[2] = botRight;
  }
  else
  {
    //Shift everything over
    prev3Textures[2] = prev3Textures[1];
    prev3TopLeft[2] = prev3TopLeft[1];
    prev3BotRight[2] = prev3BotRight[1];

    prev3Textures[1] = prev3Textures[0];
    prev3TopLeft[1] = prev3TopLeft[0];
    prev3BotRight[1] = prev3BotRight[0];

    prev3Textures[0] = textureName;
    prev3TopLeft[0] = topLeft;
    prev3BotRight[0] = botRight;
  }
}*/

/*
void EditorTilemapTools::AddToPreviousArray(const std::string& textureName, ImVec2 topLeft, ImVec2 botRight)
{
  if (prev3Textures.size() == 0)
  {
    prev3Textures.push_back(textureName);
    prev3TopLeft.push_back(topLeft);
    prev3BotRight.push_back(botRight);
  }
  else if (prev3Textures.size() == 1)
  {
    //Moves stuff from 0 to 1
    prev3Textures.push_back(prev3Textures[0]);
    prev3TopLeft.push_back(prev3TopLeft[0]);
    prev3BotRight.push_back(prev3BotRight[0]);

    //Sets stuff in 0 to recent stuff
    prev3Textures[0] = textureName;
    prev3TopLeft[0] = topLeft; 
    prev3BotRight[0] = botRight;
  }
  else if (prev3Textures.size() >= 2)
  {
    //moves stuff from 1 to 2 
    prev3Textures[2] = prev3Textures[1];
    prev3TopLeft[2] = prev3TopLeft[1];
    prev3BotRight[2] = prev3BotRight[1];

    //Moves stuff from 0 to 1
    prev3Textures[1] = prev3Textures[0];
    prev3TopLeft[1] = prev3TopLeft[0];
    prev3BotRight[1] = prev3BotRight[0];

    //Sets stuff in 0 to recent stuff 
    prev3Textures[0] = textureName;
    prev3TopLeft[0] = topLeft;
    prev3BotRight[0] = botRight;
  }

}
*/

void EditorTilemapTools::AddToPreviousArray(const std::string textureName, ImVec2 topLeft, ImVec2 botRight)
{
  if (recentTextures.size() < 3)
  {
    recentTextures.push_front(textureName);
    recentTopLefts.push_front(topLeft);
    recentBotRights.push_front(botRight);
  }
  else
  {

    recentTextures.pop_back();
    recentTopLefts.pop_back();
    recentBotRights.pop_back();

    recentTextures.push_front(textureName);
    recentTopLefts.push_front(topLeft);
    recentBotRights.push_front(botRight);

  }
}