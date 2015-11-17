#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H



#define EDITOR


#include <vector>
#include "imgui_impl_glfw_gl3.h"
#include "../Engine.h"
#include "../engineGraphics/Graphics.h"
#include "editorLevelTools.h"

class EditorLevelTools;

class ImGuiManager : public ISystem
{
public:
  ImGuiManager(GLFWwindow* window);
  ~ImGuiManager();

  void Initialize() override;
  void Update(float dt) override;
  void Draw() override;
  void SendMessages(Message* message) override;

  void setFocus(GameObjectComposition* newFocus);
  GameObjectComposition* getFocus() { return focus; }

private:
  GLFWwindow* pWindow;
  //Useful
  std::string tempMessage = "";

  GameObjectComposition* focus = nullptr;
  EditorLevelTools* levelTools = nullptr;

  int activeLevelDimensions[2];
  char activeLevelName[256];
  char desiredTextureName[256];

  void createEmptyLevelFile(std::string levelName, int width, int height);
  void createLevelFileFromArray(std::string levelName, int width, int height);
  void generateTextureKey(std::string levelName);


  void changeTile(std::string newTexture);
};

extern ImGuiManager *GUIMGR;

#endif