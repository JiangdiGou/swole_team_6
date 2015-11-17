#include "editorLevelTools.h"

EditorLevelTools::EditorLevelTools()
{
  levelDimensionInput[0] = 0;
  levelDimensionInput[1] = 0;
  currentMessage = std::string(CORE->LevelName + '\t' +  "currLvl");

  std::string initialText = std::string("resources/Levels/");
  initialText.copy(levelPathInput, initialText.size());
  fetchTextures();
}

void EditorLevelTools::handleLevelTools()
{
  //Displays message if there is one, otherwise blank space 
  if (messageActive)
  {
    if (ImGui::GetTime() - messageStart >= messageDuration)
    {
      messageActive = false;
      ImGui::Text(" ");
      ImGui::Separator();
    }
    else
    {
      ImGui::TextColored(messageColor, message.c_str());
      ImGui::Separator();
    }
  }
  else
  {
    ImGui::Text(" ");
    ImGui::Separator();
  }

  //Button to create a new empty level 
  if (ImGui::Button("Create myLvl"))
  {
    if (checkFilename(levelPathInput) && checkLevelDimensions())
    {
      createEmptyLevelFile(levelPathInput, levelDimensionInput[0], levelDimensionInput[1]);
      generateTextureKey(levelPathInput);

      setupMessage(std::string(levelPathInput + std::string(" created")), ImVec4(0, 1, 0, 1));
    }
  }

  ImGui::SameLine();
  ImGui::InputText("myLvl", levelPathInput, 256);

  //Button to Create and load a new empty level
  if (ImGui::Button("C&load myLvl"))
  {
    if (checkFilename(levelPathInput) && checkLevelDimensions())
    {
      createEmptyLevelFile(levelPathInput, levelDimensionInput[0], levelDimensionInput[1]);
      generateTextureKey(levelPathInput);

      CORE->LevelName = levelPathInput;
      CORE->textureKeyFile = appendKEY(levelPathInput);
      CORE->GameState = GS_LOAD;

      setupMessage(std::string(levelPathInput + std::string(" created and loaded")), ImVec4(0, 1, 0, 1));
    }

  }
  ImGui::SameLine(); 
  ImGui::InputInt2("WxH", levelDimensionInput);

  //Button to load an existing level. Checeks form of file, but not its existence. 
  if (ImGui::Button("Load myLvl"))
  {
    if (checkFilename(levelPathInput))
    {
      CORE->LevelName = levelPathInput;
      CORE->textureKeyFile = appendKEY(levelPathInput);
      CORE->GameState = GS_LOAD;

      setupMessage(std::string(levelPathInput + std::string(" loaded")), ImVec4(0, 1, 0, 1));
    }
  }

  ImGui::SameLine();
  //Button to quick reload level.
  if (ImGui::Button("Reload currLvl"))
  {
    CORE->GameState = GS_LOAD;

    setupMessage(std::string(CORE->LevelName + std::string(" reloaded")), ImVec4(0, 1, 0, 1));
  }
      
  ImGui::SameLine();
  //Button to save current level with a new name 
  if (ImGui::Button("Save as myLvl"))
  {
    if (checkFilename(levelPathInput))
    {
      createLevelFileFromArray(levelPathInput, FACTORY->levelWidth, FACTORY->levelHeight);
      generateTextureKey(levelPathInput);

      setupMessage(std::string(levelPathInput + std::string(" created")), ImVec4(0, 1, 0, 1));
    }
  }

  ImGui::SameLine();
  //Button to quicksave current level
  if (ImGui::Button("Save currLvl"))
  {
    createLevelFileFromArray(CORE->LevelName, FACTORY->levelWidth, FACTORY->levelHeight);

    setupMessage(std::string(CORE->LevelName + std::string(" saved")), ImVec4(0, 1, 0, 1));
  }
}

void EditorLevelTools::generateTextureKey(std::string levelName)
{

  std::ofstream ofs;
  ofs.open(appendKEY(levelName));

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

void EditorLevelTools::levelNameUpdate()
{  
  currentMessage = std::string(CORE->LevelName + '\t' + "currLvl");
}

std::string EditorLevelTools::appendKEY(const std::string input) const
{
  std::string substring(input.begin(), input.end() - 4);
  substring.append("-KEY.txt");
  return substring;
}

void EditorLevelTools::setupMessage(std::string inputMessage, ImVec4 color)
{
  message = inputMessage;
  messageColor = color;
  messageActive = true;
  messageStart = ImGui::GetTime();
}

bool EditorLevelTools::checkFilename(std::string filename)
{
  std::string prefixSubstring(filename.begin(), filename.begin() + 17);
  std::string suffixSubstring(filename.end() - 4, filename.end());

  if (prefixSubstring != "resources/Levels/"
    || suffixSubstring != ".txt")
  {
    setupMessage("Bad filename: " + filename, ImVec4(1, 0, 0, 1));
    return false;
  }
  else
    return true;
}

bool EditorLevelTools::checkLevelDimensions()
{
  if (levelDimensionInput[0] != 0 && levelDimensionInput[1] != 0)
    return true;
  else
  {
    setupMessage("Bad Level Dimensions. Both must be > 0", ImVec4(1, 0, 0, 1));
    return false;
  }   
}