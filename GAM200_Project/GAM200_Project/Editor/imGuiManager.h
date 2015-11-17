#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H



#define EDITOR

#include <vector>
#include "imgui_impl_glfw_gl3.h"
#include "../Engine.h"
#include "../engineGraphics/Graphics.h"
#include "editorLevelTools.h"
#include "editorTilemapTools.h"

class EditorLevelTools;
class EditorTilemapTools;

class ImGuiManager : public ISystem
{
public:
  ImGuiManager(GLFWwindow* window);
  ~ImGuiManager();

  void Initialize() override;
  void Update(float dt) override;
  void Draw() override;
  void SendMessages(Message* message) override;

  void updateModules();

  void setFocus(GameObjectComposition* newFocus);
  GameObjectComposition* getFocus() { return focus; }

private:
  GLFWwindow* pWindow;
  //Useful
  std::string tempMessage = "";

  GameObjectComposition* focus = nullptr;
  EditorLevelTools* levelTools = nullptr;
  EditorTilemapTools* tilemapTools = nullptr;

  char desiredTextureName[256];


  void changeTile(std::string newTexture);
};

extern ImGuiManager *GUIMGR;

#endif