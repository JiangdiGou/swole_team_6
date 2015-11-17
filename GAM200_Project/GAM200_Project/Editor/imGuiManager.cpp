#include "imGuiManager.h"

ImGuiManager *GUIMGR;

ImGuiManager::ImGuiManager(GLFWwindow* window) : pWindow(window)
{
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
  tilemapTools = new EditorTilemapTools();
}

void ImGuiManager::Update(float dt)
{
  glfwPollEvents();
  ImGui_ImplGlfwGL3_NewFrame();
  ImGui::ShowTestWindow();

  //Main editor window starts here
  ImGui::Begin("Swole Editor");

  if (ImGui::CollapsingHeader("Level Tools"))
    levelTools->handleLevelTools();
  
  if (ImGui::CollapsingHeader("Tilemap Tools"))
    tilemapTools->handleTilemapTools();

  //Main editor window ends here
  ImGui::End();

  if (focus)
  {
    //Allows changing a tile's texture
    ImGui::Begin("Change Tile Texture");
    ImGui::InputText("New Filename: ", desiredTextureName, 256);
    if (ImGui::Button("Change Texture: "))
    {
      if (std::string(desiredTextureName).size() > 2)
        changeTile(desiredTextureName);
      else
        tempMessage = "Invalid name. too short. ";
    }
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
  switch (message->MessageId)
  {
  case Mid::MouseButton:
  {
    MouseButton* mouseEvent = (MouseButton*)message;

    if (mouseEvent->MouseButtonIndex == 1
      && mouseEvent->ButtonIsPressed)
    {
      focus = NULL;
    }
  }
  } 
}

void ImGuiManager::updateModules()
{
  levelTools->levelNameUpdate();
}