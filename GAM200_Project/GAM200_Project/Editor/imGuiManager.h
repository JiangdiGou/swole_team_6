#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H



#define EDITOR

enum EditorState { IDLE, CREATINGLEVEL, LOADINGLEVEL, INLEVEL };

#include <vector>
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
  void SendMessages(Message* message) override;

  void setFocus(GameObjectComposition* newFocus);
  GameObjectComposition* getFocus() { return focus; }

private:
  GLFWwindow* pWindow;
  //Useful
  std::string tempMessage = "";
  EditorState state = IDLE;

  GameObjectComposition* focus = NULL;

  int activeLevelDimensions[2];
  char activeLevelName[256];
  char desiredTextureName[256];

  void createEmptyLevelFile(std::string levelName, int width, int height);
  void createLevelFileFromArray(std::string levelName, int width, int height);
  void generateTextureKey(std::string levelName);

  void fetchTextures();
  std::vector<std::string> textureNames;

  void changeTile(std::string newTexture);
};

extern ImGuiManager *GUIMGR;

#endif