#include "editorLevelTools.h"

EditorLevelTools::EditorLevelTools()
{
  currentMessage = std::string("Current Level Name: " + CORE->LevelName);
  state = EditorLevelState::IDLE;
  fetchTextures();
}

void EditorLevelTools::handleLevelTools()
{
  ImGui::Text(currentMessage.c_str());
  {
    switch (state)
    {
    case IDLE:
    {
      if (ImGui::Button("Create Level"))
      {
        currentMessage = "Creating Level";
        state = CREATINGLEVEL;
      }
      else if (ImGui::Button("Load Level"))
        state = LOADINGLEVEL;
      else if (ImGui::Button("Save Level"))
      {
        createLevelFileFromArray(CORE->LevelName, FACTORY->levelWidth, FACTORY->levelHeight);
        std::string substring((CORE->LevelName).begin(), (CORE->LevelName).end() - 5);
        substring.append("-KEY.txt");
        generateTextureKey(substring);
      }
      else if (ImGui::Button("Reload Level"))
      {
        CORE->GameState = GS_LOAD;
      }
    }
    }
  }
}

void EditorLevelTools::generateTextureKey(std::string levelName)
{

  std::ofstream ofs;
  ofs.open("resources/levels/" + levelName + "-KEY.txt");

  if (!ofs.is_open())
    std::cout << "Failed to Create file" << std::endl;

  for (std::vector<std::string>::iterator it = textureNames.begin(); it != textureNames.end(); ++it)
  {
    int index = it - textureNames.begin();
    //+= 1 b/c i want to reserve 0 for empty
    index += 1;

    ofs << *it << std::endl;
  }
}

void EditorLevelTools::fetchTextures()
{
  TextureAtlas* atlas = GRAPHICS->getSpriteAtlas();

  for (std::map<std::string, AtlasTexture>::iterator it = atlas->textures.begin();
    it != atlas->textures.end(); ++it)
  {
    textureNames.push_back((*it).first);
  }

  /*
  std::cout << "Hey, check out all these textures I found." << std::endl;
  for (std::vector<std::string>::iterator it = textureNames.begin(); it != textureNames.end(); ++it)
  std::cout << (int)(it - textureNames.begin()) << ": " << *it << std::endl;
  */
}


void EditorLevelTools::createLevelFileFromArray(std::string levelName, int width, int height)
{
  std::ofstream ofs;
  ofs.open(levelName);

  if (!ofs.is_open())
    std::cout << "Faied to create file " << std::endl;

  ofs << "[LevelName]" << std::endl;
  ofs << levelName << std::endl;

  ofs << "[ArraySpecs]" << std::endl;
  ofs << width << std::endl;
  ofs << height << std::endl;

  ofs << "[TileMap]" << std::endl;
  //Loop through tile map, fill with 0's
  for (int j = height - 1; j >= 0; --j)
  {
    for (int i = 0; i < width; ++i)
    {
      ofs << FACTORY->tileMap[j][i] << " ";
    }
    ofs << std::endl;
  }

  ofs.close();
}

void EditorLevelTools::createEmptyLevelFile(std::string levelName, int width, int height)
{
  std::ofstream ofs;
  ofs.open("resources/levels/" + levelName + ".txt");

  if (!ofs.is_open())
    std::cout << "Faied to create file " << std::endl;

  ofs << "[LevelName]" << std::endl;
  ofs << levelName << std::endl;

  ofs << "[ArraySpecs]" << std::endl;
  ofs << width << std::endl;
  ofs << height << std::endl;

  ofs << "[TileMap]" << std::endl;
  //Loop through tile map, fill with 0's
  for (int j = 0; j < height; ++j)
  {
    for (int i = 0; i < width; ++i)
    {
      ofs << "0 ";
    }
    ofs << std::endl;
  }

  ofs.close();
}
