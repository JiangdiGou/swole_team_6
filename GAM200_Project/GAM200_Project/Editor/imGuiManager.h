#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H

#include "imGUI\imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "../Engine.h"
#include "../engineGraphics/Graphics.h"

class ImGuiManager : public ISystem
{
public:
  ImGuiManager(GLFWwindow* window);
  ~ImGuiManager();

  void Initialize() override;
  void Update(float dt) override;
  void Draw() override;

private:
  GLFWwindow* pWindow;
};

#endif