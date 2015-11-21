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
  if (ImGui::Button("Create Entity"))
  {
    GOC* newComponent = createNewComponent(newEntityName);
    newComponent->Initialize();
  }
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
        //If body or AAB
        if (currentItem + 1 == 5 || currentItem + 1 == 7)
        {
          addShapeAndBody(focus);
          setupMessage("Body and Shape added.", ImVec4(0, 1, 0, 1));
        }
        else
        {
          GameComponent* component = getNewComponent((ComponentTypeId(currentItem + 1)));

          focus->AddComponent((ComponentTypeId)(currentItem + 1), component);
          focus->Initialize();
        }
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

GOC* EditorEntityTools::createNewComponent(std::string componentName)
{
  GOC* newEntity = FACTORY->makeObject(componentName);
  if (!newEntity)
  {
    setupMessage("Entity creation failed", ImVec4(1, 0, 0, 1));
    return NULL;
  }

  //Core stuff
  Transform* newTransform = new Transform();
  Sprite* newSprite = new Sprite();
  newSprite->texture = (GRAPHICS->getSpriteAtlas())->textures["Smiley1"];

  //Editor Stuff
  //Since we're in editor mode if this fx got called 
  Reactive* newReactive = new Reactive();
  Editable* newEditable = new Editable(false);

  //Add Core stuff
  newEntity->AddComponent(CT_Transform, newTransform);
  newEntity->AddComponent(CT_Sprite, newSprite);

  //Add edutir stuff
  newEntity->AddComponent(CT_Reactive, newReactive);
  newEntity->AddComponent(CT_Editable, newEditable);

  setupMessage(componentName + " created.", ImVec4(0, 1, 0, 1));

  return newEntity;
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


