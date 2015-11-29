#include "editorLevelTools.h"
#include "../Serialization/TextSerialization.h"

EditorLevelTools::EditorLevelTools()
{
  levelDimensionInput[0] = 0;
  levelDimensionInput[1] = 0;

  //Puts default text in the box
  std::string initialText = std::string("resources/Levels/");
  initialText.copy(levelPathInput, initialText.size());
}

void EditorLevelTools::init()
{
  currentMessage = std::string(CORE->LevelName + '\t' + "currLvl");
}

void EditorLevelTools::handle()
{
  handleMessage();

  //Button to create a new empty level 
  if (ImGui::Button("Create myLvl"))
  {
    if (checkFilename(levelPathInput) && checkLevelDimensions())
    {
      createEmptyLevelFile(levelPathInput, levelDimensionInput[0], levelDimensionInput[1]);
      createBlankEntFile(levelPathInput);

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
      createBlankEntFile(levelPathInput);

      CORE->LevelName = levelPathInput;
      CORE->GameState = GS_LOAD;

      setupMessage(std::string(levelPathInput + std::string(" created and loaded")), ImVec4(0, 1, 0, 1));
    }

  }
  ImGui::SameLine(); 
  ImGui::InputInt2("WxH", levelDimensionInput);

  //Button to load an existing level. Checeks form of file, but not its existence. 
  if (ImGui::Button("Load myLvl"))
  {
    if (checkFilename(levelPathInput, true))
    {
      CORE->LevelName = levelPathInput;
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

      if (saveEntities(levelPathInput))
        setupMessage(std::string(levelPathInput + std::string(" created")), ImVec4(0, 1, 0, 1));
    }
  }

  ImGui::SameLine();
  //Button to quicksave current level
  if (ImGui::Button("Save currLvl"))
  {
    createLevelFileFromArray(CORE->LevelName, FACTORY->levelWidth, FACTORY->levelHeight);

    if (saveEntities(CORE->LevelName))
      setupMessage(std::string(CORE->LevelName + std::string(" saved")), ImVec4(0, 1, 0, 1));
  }
}

bool EditorLevelTools::saveEntities(std::string levelName)
{
  Framework::TextSerializer serializer = Framework::TextSerializer();

  if (!(serializer.Open(appendEnt(levelName))))
  {
    setupMessage("Failed to open to -ENT file", ImVec4(1, 0, 0, 1));
    return false;
  }
  else
  {
    //Factory fx will jusst write on top of old shit if no clear.
    //serializer.stream.clear();
    std::ofstream ofs;
    ofs.open(appendEnt(levelName), std::ofstream::out | std::ofstream::trunc);
    ofs.close(); 

    FACTORY->SerializeAllObjects(serializer);
    return true;
  }
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
      ofs << FACTORY->tileMap[j][i] << ' ';
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
  {
    setupMessage("Failed to Create level File", ImVec4(1, 0, 0, 1));
    return;
  }

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
      ofs << std::string("E ");
    }
    ofs << std::endl;
  }

  ofs.close();
}

void EditorLevelTools::createBlankEntFile(std::string levelName)
{
  std::ofstream ofs;
  ofs.open(appendEnt(levelName));

  if (!ofs.is_open())
  {
    setupMessage("Failed to Create level ENT File", ImVec4(1, 0, 0, 1));
    return;
  }
  else
  {
    ofs.clear();
    ofs.close();
    return;
  }
}

void EditorLevelTools::levelNameUpdate()
{  
  currentMessage = std::string(CORE->LevelName + '\t' + "currLvl");
}


bool EditorLevelTools::checkFilename(std::string filename, bool checkContentsAndKey)
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
  {
    if (checkContentsAndKey)
    {
      std::string testLine;
      std::ifstream is;

      //Check that it can open the level file
      is.open(filename);
      if (!is.is_open())
      {
        setupMessage("Error opening level file: " + filename, ImVec4(1, 0, 0, 1));
        return false;
      }

      //Check it's got stuff in it 
      std::getline(is, testLine);
      if (testLine.size() < 2)
      {
        setupMessage("Level file exists, but appears corrupt: " + filename, ImVec4(1, 0, 0, 1));
        return false;
      }
      //Done checking level file
      is.close();
    }
    return true;
  }
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
