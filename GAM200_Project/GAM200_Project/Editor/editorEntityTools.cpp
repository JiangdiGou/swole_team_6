#include "editorEntityTools.h"

EditorEntityTools::EditorEntityTools()
{

}

void EditorEntityTools::handle()
{
  if (focus)
    ImGui::Text(std::string("Current Entity: " + focus->GetName()).c_str());
  else
    ImGui::Text("No entity selected. ");
}