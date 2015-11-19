#include "editorEntityTools.h"
#include <typeinfo>

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

void EditorEntityTools::init()
{

}

void EditorEntityTools::handle()
{
  //CORE
  //Displays currently selected entity name
  if (focus)
    ImGui::Text(std::string("Current Entity: " + focus->GetName()).c_str());
  else
    ImGui::Text("No entity selected. ");

  handleMessage();

  //MAKE NEW ENTITY, CURRENTLY DOES NOTHING
  ImGui::Button("Create Entity");
  ImGui::SameLine();
  ImGui::InputText("Name", newEntityName, 256);
  
  //COMPONENT LIST
  ImGui::Columns(2);
  ImGui::ListBox("", &currentItem, components, TOTALCOMPONENTS); 
  
  //TWEAKABLES
  //Displays currently selected component name
  ImGui::NextColumn();
  const char* curComponent = components[currentItem];
  std::string curText = "Curr: ";
  curText.append(curComponent);
  ImGui::Text(curText.c_str());

  //Checks if the focus has the component
  if (focus)
  {
    GameComponent* component = getFocusComponent((ComponentTypeId)(currentItem + 1));

    if (component != NULL)
    {
      ImGui::Text("Entity has component");
    }
    else
    {
      ImGui::Text("Entity doesn't have component");
    }
  }

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

GameComponent* EditorEntityTools::getFocusComponent(ComponentTypeId type)
{
  switch (type)
  {
  case CT_Transform:
    return focus->has(Transform);

  case CT_Camera:
    return focus->has(Camera);

  case CT_Sprite:
    return focus->has(Sprite);

  case CT_SpriteText:
    return focus->has(SpriteText);

  case CT_Body:
    return focus->has(Body);

  case CT_TileMapCollision:
    return focus->has(TileMapCollision);

  case CT_ShapeAAB:
    return focus->has(ShapeAAB);

  case CT_ShapeLine:
    return focus->has(ShapeLine);

  case CT_Reactive:
    return focus->has(Reactive);

  case CT_SoundEmitter:
    return focus->has(SoundEmitter);

  case CT_Editable:
    return focus->has(Editable);

  default:
    return NULL;


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

