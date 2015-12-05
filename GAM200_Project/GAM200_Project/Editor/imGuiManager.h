#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H

//#define EDITOR
#include "Defines.h"
#include <vector>
#include "imgui_impl_glfw_gl3.h"
#include "../Engine.h"
#include "../engineGraphics/Graphics.h"
#include "editorLevelTools.h"
#include "editorTilemapTools.h"
#include "editorEntityTools.h"

class EditorLevelTools;
class EditorTilemapTools;
class EditorEntityTools;

class ImGuiManager : public ISystem
{
  friend class Editable;

public:
  ImGuiManager(GLFWwindow* window);
  ~ImGuiManager();

  void Initialize() override;
  void Update(float dt) override;
  void Draw() override;
  void SendMessages(Message* message) override;

  void updateModules();

private:
  GLFWwindow* pWindow;

  EditorLevelTools* levelTools = nullptr;
  EditorTilemapTools* tilemapTools = nullptr;
  EditorEntityTools* entityTools = nullptr;


};

extern ImGuiManager *GUIMGR;

#endif