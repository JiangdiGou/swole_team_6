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
  //MAKE NEW ENTITY, CURRENTLY DOES NOTHING
  ImGui::Button("Create Entity");
  ImGui::SameLine();
  ImGui::InputText("Name", newEntityName, 256);

  //CORE
  //Displays currently selected entity name
  if (focus)
    ImGui::Text(std::string("Current Entity: " + focus->GetName()).c_str());
  else
    ImGui::Text("No entity selected. ");

  handleMessage();
  
  //COMPONENT LIST
  ImGui::Columns(2);
  ImGui::ListBox("", &currentItem, components, TOTALCOMPONENTS); 
  
  //TWEAKABLES
  //Displays currently selected component name
  ImGui::NextColumn();
  const char* curComponent = components[currentItem];

  //Checks if the focus has the component
  if (focus)
  {
    GameComponent* component = getFocusComponent((ComponentTypeId)(currentItem + 1));

    if (component != NULL)
    {
      ImGui::TextColored(ImVec4(0, 1, 0, 1), curComponent);

      ImGui::SameLine();
      if (ImGui::Button("Rmv"))
      {
        setupMessage("Remove not yet implemented", ImVec4(1, 0, 0, 1));
      }
      showTweakables((ComponentTypeId)(currentItem + 1));
    }
    else
    {
      ImGui::TextColored(ImVec4(1, 0, 0, 1), curComponent);

      ImGui::SameLine();
      if(ImGui::Button("Add"))
      {
        GameComponent* component = getNewComponent((ComponentTypeId(currentItem + 1)));

        focus->AddComponent((ComponentTypeId)(currentItem + 1), component);
        focus->Initialize();
      }
    }
  }

  //Sets imgui back to a single column
  ImGui::Columns(1);
}

void EditorEntityTools::showTweakables(ComponentTypeId type)
{
  switch (type)
  {
  case CT_Sprite:
  {
    /*
    //Setup default vals input fields to curr vals

    std::string textureName(fSprite->texture.textureName);

    strcpy(tweakableText, textureName.c_str());
    */

    Sprite* fSprite = focus->has(Sprite);
    ImGui::InputText("Texture", tweakableText, 256);
    
    if (ImGui::Button("ChangeTexture"))
    {
      fSprite->texture = ((GRAPHICS->getSpriteAtlas())->textures[std::string(tweakableText)]);
    }
  }
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

GameComponent* EditorEntityTools::getNewComponent(ComponentTypeId type)
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
    return new SpriteText(std::string("default text"));

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


