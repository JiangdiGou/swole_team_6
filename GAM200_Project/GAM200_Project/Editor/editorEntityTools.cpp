#include "editorEntityTools.h"

const const char* EditorEntityTools::components[TOTALCOMPONENTS] = {
  "Transform",
  "Camera",
  "Sprite",
  "SpriteText",
  "Body",
  "TileMapCollision",
  "Shape AAB",
  "Shape Line",
  "Reactive",
  "Sound Emitter",
  "Editbale"
};

EditorEntityTools::EditorEntityTools()
{
  
  /*
  
  for (int i = CT_Transform; i != CT_Editable; ++i)
  {
    components[i] = new char[256];
  }
  


  for (int i = CT_Transform; i != CT_Editable; ++i)
  {
    ComponentTypeId component = (ComponentTypeId)i;
    std::string componentName = (getComponentName(component));


    strcpy(components[i], componentName.c_str());
    ++numComponents;
    

    const char* cStr = new const char[256];

    cStr = componentName.c_str();
    
    
  }*/
}

void EditorEntityTools::handle()
{
  if (focus)
    ImGui::Text(std::string("Current Entity: " + focus->GetName()).c_str());
  else
    ImGui::Text("No entity selected. ");

  handleMessage();

  if (ImGui::Button("Create new Entity"))
  {

  }

  ImGui::SameLine();
  ImGui::InputText("Name", newEntityName, 256);

  ImGui::Columns(2);
  ImGui::ListBox("", &currentItem, components, TOTALCOMPONENTS); 
  ImGui::NextColumn();
  ImGui::Text("Tweakables will go here");
  ImGui::Columns(1);

  ImGui::Button("Remove Component");
  ImGui::SameLine();
  ImGui::Button("Add Component");

}

//This isnt in use right now cause it was giving me issues. array is just hard coded now
std::string EditorEntityTools::getComponentName(ComponentTypeId type)
{
  switch (type)
  {
  case CT_Transform:
  {
    return std::string("Transform");
    break;
  }

  case CT_Camera :
    return std::string("Camera");

  case CT_Sprite :
    return std::string("Sprite");

  case CT_SpriteText :
    return std::string("Sprite Text");

  case CT_Body :
    return std::string("Body");

  case CT_TileMapCollision:
    return std::string("Tile Map Collision");

  case CT_PlayerState:
    return std::string("Player State");

  case CT_ShapeAAB:
    return std::string("Shape AAB");

  case CT_ShapeLine:
    return std::string("Shape line");

  case CT_MouseVector:
    return std::string("Mouse Vector");

  case CT_Reactive:
    return std::string("Reactive");

  case CT_SoundEmitter:
    return std::string("Sound Emitter");

  case CT_Editable:
    return std::string("Editable");

  }
}

GameComponent* createComponentPointer(ComponentTypeId type)
{
  switch (type)
  {
  case CT_Transform:
    return new Transform();

  case CT_Camera:
    return new Camera();

  case CT_Sprite:
    return new Sprite();

  case CT_SpriteText:
    return new SpriteText("Default Text");

  case CT_Body:
    return new Body();

  case CT_TileMapCollision:
    return new TileMapCollision();

  case CT_ShapeAAB:
    return new ShapeAAB();

  case CT_ShapeLine:
    return new ShapeLine();

  case CT_Reactive:
    return new Reactive();

  case CT_SoundEmitter:
    return new SoundEmitter();

  case CT_Editable:
    return new Editable();


    /*
    case CT_PlayerState:
    return new PlayerState();
    */

    /*
    case CT_MouseVector:
    return new mouseVector();
    */
  }
}