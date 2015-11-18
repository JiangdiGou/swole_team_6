#include "imGuiManager.h"

ImGuiManager *GUIMGR;

ImGuiManager::ImGuiManager(GLFWwindow* window) : pWindow(window)
{
  GUIMGR = this;
}

ImGuiManager::~ImGuiManager()
{
  delete levelTools;
  delete tilemapTools;
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
    levelTools->handle();
  
  if (ImGui::CollapsingHeader("Tilemap Tools"))
    tilemapTools->handle();

  //Main editor window ends here
  ImGui::End();

  /*
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
  */
}

void ImGuiManager::Draw()
{
  ImGui::Render();
}


void ImGuiManager::SendMessages(Message* message)
{
  switch (message->MessageId)
  {
  case Mid::MouseButton:
  {
    
  }
  } 
}

void ImGuiManager::updateModules()
{
  levelTools->levelNameUpdate();
}