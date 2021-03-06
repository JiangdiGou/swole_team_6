/******************************************************************************/
/*!
\author Conor Lavelle

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
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
  entityTools = new EditorEntityTools();

  //If i eventually have enough modules it might be worth it
  //to do this in a loop. 
  levelTools->init();
  tilemapTools->init();
  entityTools->init();
}

void ImGuiManager::Update(float dt)
{
  glfwPollEvents();
  ImGui_ImplGlfwGL3_NewFrame();
  //ImGui::ShowTestWindow();

  //Main editor window starts here
  ImGui::Begin("Swole Editor");

  if (ImGui::CollapsingHeader("Level Tools"))
    levelTools->handle();
  
  if (ImGui::CollapsingHeader("Entity Tools"))
    entityTools->handle();

  if (ImGui::CollapsingHeader("Tilemap Tools"))
    tilemapTools->handle();

  //Main editor window ends here
  ImGui::End();
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