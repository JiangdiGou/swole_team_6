#include "imGuiManager.h"

ImGuiManager::ImGuiManager(GLFWwindow* window) : pWindow(window) {}

ImGuiManager::~ImGuiManager()
{
  ImGui_ImplGlfwGL3_Shutdown();
}

void ImGuiManager::Initialize()
{
  ImGui_ImplGlfwGL3_Init(pWindow, true);
}

void ImGuiManager::Update(float dt)
{
  ImGui_ImplGlfwGL3_NewFrame();
  //Do stuff here
  ImGui::Text("Hello World!");
  //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
}

void ImGuiManager::Draw()
{
  ImGui::Render();
}