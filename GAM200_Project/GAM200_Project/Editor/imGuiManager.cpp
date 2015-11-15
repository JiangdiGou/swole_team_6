#include "imGuiManager.h"

ImGuiManager *GUIMGR;

ImGuiManager::ImGuiManager(GLFWwindow* window) : pWindow(window)
{
  activeLevelDimensions[0] = 0;
  activeLevelDimensions[1] = 0;

  GUIMGR = this;
}

ImGuiManager::~ImGuiManager()
{
  ImGui_ImplGlfwGL3_Shutdown();
}

void ImGuiManager::Initialize()
{
  ImGui_ImplGlfwGL3_Init(pWindow, false);
  fetchTextures();
}

void ImGuiManager::Update(float dt)
{
  glfwPollEvents();
  ImGui_ImplGlfwGL3_NewFrame();
  ImGui::ShowTestWindow();

  switch (state)
  {
    case IDLE:
    {
      ImGui::Begin("Level Tools");
      if (ImGui::Button("Create Level"))
      {
        tempMessage = "Creating Level";
        state = CREATINGLEVEL;
      }
      ImGui::End();
      //We can't load levels right now 
      /*
      else if (ImGui::Button("Load Level"))
        state = LOADINGLEVEL;
        */
      if (focus)
      {
        //Allows changing a tile's texture
        bool result;
        ImGui::Begin("Change Tile Texture", &result);
        ImGui::InputText("New Filename: ", desiredTextureName, 256);
        if (ImGui::Button("Change Texture: "))
        {
          if (std::string(desiredTextureName).size() > 2)
            changeTile(desiredTextureName);
          else
            tempMessage = "Invalid name. too short. ";
        }
        ImGui::End();

        //Probably add more to this one later
        ImGui::Begin("utils", &result);
        if (ImGui::Button("ClearFocus"))
          focus = NULL;
        ImGui::End();
        
      }

      break;
    }
    case CREATINGLEVEL:
    {
      //Waits for input
      ImGui::Begin("Creating Level");
      ImGui::Text(tempMessage.c_str());
      ImGui::InputInt2("Width x Height", activeLevelDimensions);
      ImGui::InputText("Level Name", activeLevelName, 256);

      if (ImGui::Button("Create"))
      {
        //Checks input
        if (activeLevelDimensions[0] <= 0 || activeLevelDimensions[1] <= 0)
          tempMessage = "Invalid dimensions, both must be > 0";
        else if (std::string(activeLevelName).size() <= 2)
          tempMessage = "Invalid name. too short. ";
        else
        { 
          //creates level file and key
          createEmptyLevelFile(std::string(activeLevelName), activeLevelDimensions[0], activeLevelDimensions[1]);
          generateTextureKey(std::string(activeLevelName));
          tempMessage = std::string(activeLevelName) + " created";
        }
      }
      else if (ImGui::Button("Create and Load"))
      {
        if (activeLevelDimensions[0] <= 0 || activeLevelDimensions[1] <= 0)
          tempMessage = "Invalid dimensions, both must be > 0";
        else if (std::string(activeLevelName).size() <= 2)
          tempMessage = "Invalid name. too short. ";
        else
        {
          createEmptyLevelFile(std::string(activeLevelName), activeLevelDimensions[0], activeLevelDimensions[1]);
          generateTextureKey(std::string(activeLevelName));
          tempMessage = "Sorry, " + std::string(activeLevelName) + " was created but loading isn't functional yet.";
          //FACTORY->readTextureKey("resources/levels/" + std::string(activeLevelName) + "-KEY.txt");
          //FACTORY->loadLevelFrom("resources/levels/" + std::string(activeLevelName) + ".txt");
        }
      }
      ImGui::End();
      break;
    }
    case LOADINGLEVEL:
    {
      break;
    }
    case INLEVEL:
    {
      break;
    }
  }
}

void ImGuiManager::Draw()
{
  ImGui::Render();
}

void ImGuiManager::setFocus(GameObjectComposition* newFocus)
{
  focus = newFocus;
}

void ImGuiManager::fetchTextures()
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

void ImGuiManager::createEmptyLevelFile(std::string levelName, int width, int height)
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
      ofs << '0';
    }
    ofs << std::endl;
  }

  //Unsure if needed with new system, just matching old file for now.
  ofs << "[EntityMap]" << std::endl;
  for (int j = 0; j < height; ++j)
  {
    for (int i = 0; i < width; ++i)
    {
      ofs << '0';
    }
    ofs << std::endl;
  }

  ofs.close();
}

void ImGuiManager::generateTextureKey(std::string levelName)
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

void ImGuiManager::changeTile(std::string newTexture)
{
  //You will change the number in the file here, but not till digit thing fixed.
  Sprite* tSprite = (Sprite*)(focus->GetComponent(CT_Sprite));
  if (tSprite)
  {
    bool wasEmpty;
    if (tSprite->texture == GRAPHICS->getSpriteAtlas()->textures["emptyTile"])
      wasEmpty = true;
    else
      wasEmpty = false;

    TextureAtlas* pAtlas = GRAPHICS->getSpriteAtlas();
    tSprite->texture = pAtlas->textures[desiredTextureName];
    //I wanted to have it so that if you make it a tile it has collision
    //but something about how im doing it below is wrong. 
    /*
    if (newTexture != "emptyTile" && wasEmpty)
    {
      Body * tileBody = new Body();
      tileBody->Mass = 0;
      tileBody->Restitution = 0.3f;
      tileBody->Friction = 0.0f;
      ShapeAAB * boxCollider = new ShapeAAB();
      boxCollider->Extents = Vec2D(.5, .5);
      tileBody->BodyShape = boxCollider;
      focus->AddComponent(CT_Body, tileBody);
      focus->AddComponent(CT_ShapeAAB, boxCollider);

      tileBody->Initialize();
      boxCollider->Initialize();
    }
    */
  }
  focus = NULL;
}

void ImGuiManager::SendMessages(Message* message)
{
  //I was gonna do something here but i changed my mind
  //I probably will do something here later
  /*
  switch (message->MessageId)
  {
  case Mid::MouseButton:
  {
    MouseButton* mouseEvent = (MouseButton*)message;

    if (mouseEvent->MouseButtonIndex == 1
      && mouseEvent->ButtonIsPressed)
    {
      rightClickMenuOpen = true;
    }
  }
  }
  */
}