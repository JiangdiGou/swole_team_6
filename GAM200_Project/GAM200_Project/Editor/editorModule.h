#ifndef EDITORMODULE_H
#define EDITORMODULE_H

class EditorModule
{
public:
  virtual void handle() = 0;
  virtual void init() = 0;

  std::string message = "";
  ImVec4 messageColor = ImVec4(1, 1, 1, 1);
  float messageDuration = 5.0f;
  float messageStart;
  bool messageActive = false;


  void setupMessage(std::string inputMessage, ImVec4 color)
  {
    message = inputMessage;
    messageColor = color;
    messageActive = true;
    messageStart = ImGui::GetTime();
  }

  void handleMessage()
  {
    //Displays message if there is one
    if (messageActive)
    {
      //Checks if its time for the messasge to go away
      if (ImGui::GetTime() - messageStart >= messageDuration)
      {
        messageActive = false;
        ImGui::Text(" ");
        ImGui::Separator();
      }
      //If not time to go away, displays message
      else
      {
        ImGui::TextColored(messageColor, message.c_str());
        ImGui::Separator();
      }
    }
    //If no message active, displays blank space
    else
    {
      ImGui::Text(" ");
      ImGui::Separator();
    }
  }

  bool addTilemapAndBody(GOC* owner)
  {
    Body* body = new Body();
    ShapeAAB* shape = new ShapeAAB();
    shape->body = body;
    body->BodyShape = shape;

    owner->AddComponent(CT_Body, body);
    owner->AddComponent(CT_ShapeAAB, shape);

    owner->Initialize();

    setupMessage("Body and Shape added.", ImVec4(0, 1, 0, 1));
  }
};

#endif