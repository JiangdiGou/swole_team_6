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
  "Test Component",
  "Editbale",
  "MouseVector",
  "PlayerState"
};

EditorEntityTools::EditorEntityTools()
{
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
          setupMessage("I've removed adding physics b/c they crash editor.", ImVec4(1, 0, 0, 1));
          //Damn, this still doesnt work.
          //addShapeAndBody(focus);
          //setupMessage("Body and Shape added.", ImVec4(0, 1, 0, 1));
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
  case CT_Transform:
  {
    ImGui::Text("To Translate...");
    ImGui::Text("Click and Drag");
    ImGui::Text("To Rotate...");
    ImGui::Text("Ctrl-Click and Drag");
    ImGui::Text("To Scale...");
    ImGui::Text("Shift-Click and Drag");
    break;
  }
  case CT_Sprite:
  {
    Sprite* fSprite = (Sprite*)getFocusComponent(CT_Sprite);
    ImGui::InputText("Texture", tweakableText, 256);
    if (ImGui::Button("ChangeTexture") && fSprite)
    {
      fSprite->texture = ((GRAPHICS->getSpriteAtlas())->textures[std::string(tweakableText)]);
    }
    break;
  }
  case CT_SpriteText:
  {
    SpriteText* fSpriteText = (SpriteText*)getFocusComponent(CT_SpriteText);
    ImGui::InputText("Text", tweakableText, 256);

    if (ImGui::Button("Update Text") && fSpriteText)
    {
      fSpriteText->message = std::string(tweakableText);
    }
    break;
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

  case CT_TestComponent:
    return focus->has(TestComponent);

  case CT_Editable:
    return focus->has(Editable);

  case CT_MouseVector:
    return focus->has(MouseVector);
 
  case CT_PlayerState:
    return focus->has(PlayerState);

  default:
    return NULL;
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

  //Makes the entity spawn in the middle of the screen

  Vector2 middleOfScreen = Vector2(INITINFO->clientWidth / 2.0, INITINFO->clientHeight / 2.0);
  middleOfScreen = GRAPHICS->screenToWorld(middleOfScreen);
  newTransform->SetPosition(Vector3(middleOfScreen, 0)); 

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

  case CT_TestComponent:
    return new  TestComponent();

  case CT_Editable:
    return new Editable();

  case CT_MouseVector:
    return new MouseVector();

  case CT_PlayerState:
    return new PlayerState();

  default:
    return NULL;
  }
}


