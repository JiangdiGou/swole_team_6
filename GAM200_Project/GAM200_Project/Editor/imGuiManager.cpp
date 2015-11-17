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
  levelTools = new EditorLevelTools();
}

void ImGuiManager::Update(float dt)
{
  glfwPollEvents();
  ImGui_ImplGlfwGL3_NewFrame();
  ImGui::ShowTestWindow();

  ImGui::Begin("Swole Editor");
  if (ImGui::CollapsingHeader("Level Tools"))
  {
    levelTools->handleLevelTools();
  }
  ImGui::End();

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
}

void ImGuiManager::Draw()
{
  ImGui::Render();
}

void ImGuiManager::setFocus(GameObjectComposition* newFocus)
{
  focus = newFocus;
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
      ofs << "0 ";
    }
    ofs << std::endl;
  }

  ofs.close();
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

    int index = 0; 
    for (std::vector<std::string>::iterator it = FACTORY->textureKey.begin();
      it != FACTORY->textureKey.end(); ++it)
    {
      index = it - FACTORY->textureKey.begin();
      if (*it == newTexture)
        break;
    }

    Transform* pTransform = focus->has(Transform);
    FACTORY->tileMap[(int)pTransform->GetPositionY()][(int)pTransform->GetPositionX()] = index;

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
    }*/


    
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