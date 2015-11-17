#include "editorTilemapTools.h"

EditorTilemapTools::EditorTilemapTools()
{

}

void EditorTilemapTools::handleTilemapTools()
{
  ImGui::Text("This grid currently does nothing");

  TextureAtlas* atlas = GRAPHICS->getSpriteAtlas();
  for (std::vector<std::string>::iterator it = FACTORY->textureKey.begin();
    it != FACTORY->textureKey.end(); ++it)
  {
    int index = it - FACTORY->textureKey.begin();

    if (!(index % 6 == 0))
      ImGui::SameLine();

    AtlasTexture texture = atlas->textures[*it];
    
    ImVec2 topLeft = ImVec2(texture.getLeftX(), texture.getTopY());
    ImVec2 bottomRight = ImVec2(texture.getRightX(), texture.getBottomY());

    ImGui::ImageButton((ImTextureID)atlas->ID, ImVec2(64, 64), topLeft, bottomRight);
  }
}