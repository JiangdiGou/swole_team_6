#include "editorEntityTools.h"
#include "../ZilchComponent.h"

const const char* EditorEntityTools::components[TOTALCOMPONENTS] = {
  "Transform",
  "Camera",
  "Sprite",
  "SpriteText",
  "Body",
  "TileMapCollision",
  "Shape AAB",
  "Shape Line",
  "GameReactive",
  "Sound Emitter",
  "Player Tag",
  "HUD Component",
  "Editbale",
  "MouseVector",
  "PlayerState",
  "Menu Button",
  "OurZilchComponent",
  "Bad Enemy AI",
  "Health Manager",
  "PlayerHealthBar",
  "Player Attack",
  "Load Level",
  "Enemy Health Manager",
  "WinLogic",
  "Tutorial Logic",
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

  if (ImGui::Button("Destroy Entity") && focus != NULL)
    FACTORY->destroyObject(focus->GetId());

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
        if (focus->RemoveComponent((ComponentTypeId)(currentItem + 1), component))
          setupMessage("Component Removed", ImVec4(0, 1, 0, 1));
        else
          setupMessage("Error in removing component", ImVec4(1, 0, 0, 1));
      }
      showTweakables((ComponentTypeId)(currentItem + 1));
    }
    else
    {
      //17 is our zilch component
      if (currentItem + 1 == 17)
      {
        ImGui::InputText("Comp", tweakableText, 256);
        ImGui::InputInt("ID", &tweakI);
        if (ImGui::Button("Add"))
        {
          LibraryRef library = ZILCHMANAGER->library;
          if (library->BoundTypes.findValue(tweakableText, nullptr) == NULL)
          {
            setupMessage("Incorrect Zilch Class", ImVec4(1, 0, 0, 1));
          }
          else
          {
            OurZilchComponent* zComp = new OurZilchComponent(std::string(tweakableText), (ZilchComponentTypeId)tweakI);
            focus->AddComponent(CT_OurZilchComponent, zComp);
            setupMessage("Zilch comp Added", ImVec4(0, 1, 0, 1));
          }
        }

      }
      else
      {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), curComponent);

        ImGui::SameLine();
        if (ImGui::Button("Add"))
        {

          GameComponent* component = FACTORY->getNewComponent((ComponentTypeId(currentItem + 1)));

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
    Transform* fTransform = (Transform*)getFocusComponent(CT_Transform);
    Vector3 pos = fTransform->GetPosition();
    Vector3 scl = fTransform->GetScale();
    float rot = fTransform->GetRotation().z;

    // Get current value of transform stuff
    char posChar[256];
    char sclChar[256];
    char rotChar[256];
    sprintf(posChar, "Pos: %f %f %f", pos.x, pos.y, pos.z);
    sprintf(sclChar, "Scl: %f %f %f", scl.x, scl.y, scl.z);
    sprintf(rotChar, "Rot: %f", rot);

    //Pos stuff
    ImGui::Text("Translation: Click and Drag");
    ImGui::Text(posChar);
    ImGui::InputFloat3("pos", tweakf3_1);

    if (ImGui::Button("Update Pos"))
      fTransform->SetPosition(Vector3(tweakf3_1[0], tweakf3_1[1], tweakf3_1[2]));

    //Rot Stuff
    ImGui::Text("Rotation: Ctrl-Click and Drag");
    ImGui::Text(rotChar);
    ImGui::InputFloat("rot", &tweakF);

    if (ImGui::Button("Update Rot"))
      fTransform->SetRotationZ(tweakF);

    //Scl Stuff
    ImGui::Text("Scaling: Shift-Click and Drag");
    ImGui::Text(sclChar);
    ImGui::InputFloat3("scl", tweakf3_2);

    if (ImGui::Button("Update Scl"))
      fTransform->SetScale(Vector3(tweakf3_2[0], tweakf3_2[1], tweakf3_2[2]));

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
    ImGui::InputFloat4("Color", tweakF4);
    if (ImGui::Button("Update Color") && fSprite)
    {
      fSprite->color = glm::vec4(tweakF4[0], tweakF4[1], tweakF4[2], tweakF4[3]);
    }
    ImGui::InputInt("Layer", &tweakI);
    if (ImGui::Button("Update Layer"))
    {
      fSprite->setLayer(tweakI);
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
  case CT_HUDcomponent:
  {
    HUDcomponent* pHUD = (HUDcomponent*)getFocusComponent(CT_HUDcomponent);
    char currentOffset[256];
    Vector3 offset = pHUD->getOffset();

    sprintf(currentOffset, "Cur Offset: %f %f %f", offset.x, offset.y, offset.z);
    ImGui::Text(currentOffset);
    ImGui::InputFloat3("offset", tweakf3_1);

    if (ImGui::Button("Update"))
    {
      pHUD->setOffset(Vector3(tweakf3_1[0], tweakf3_1[1], tweakf3_1[2]));
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

  case CT_GameReactive:
    return focus->has(GameReactive);

  case CT_SoundEmitter:
    return focus->has(SoundEmitter);

  case CT_PlayerTag:
    return focus->has(PlayerTag);

  case CT_HUDcomponent:
	  return focus->has(HUDcomponent);

  case CT_Editable:
    return focus->has(Editable);

  case CT_MouseVector:
    return focus->has(MouseVector);
 
  case CT_PlayerState:
    return focus->has(PlayerState); 

  case CT_MenuButton:
    return focus->has(MenuButton);

  case CT_BadEnemyAI:
    return focus->has(BadEnemyAI);

  case CT_HealthManager:
	  return focus->has(HealthManager);

  case CT_PlayerHealthBar:
    return focus->has(PlayerHealthBar);

  case CT_PlayerAttack:
	  return focus->has(PlayerAttack);

  case CT_LoadLevel:
	  return focus->has(LoadLevel);

  case CT_EnemyHealthManager:
    return focus->has(EnemyHealthManager);

  case CT_WinLogic:
	  return focus->has(WinLogic);

  case CT_TutorialLogic:
    return focus->has(TutorialLogic);

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
  Editable* newEditable = new Editable(false);

  //Add Core stuff
  newEntity->AddComponent(CT_Transform, newTransform);

  //Makes the entity spawn in the middle of the screen

  Vector2 middleOfScreen = Vector2(INITINFO->clientWidth / 2.0, INITINFO->clientHeight / 2.0);
  middleOfScreen = GRAPHICS->screenToWorld(middleOfScreen);
  newTransform->SetPosition(Vector3(middleOfScreen, 0)); 

  newEntity->AddComponent(CT_Sprite, newSprite);

  //Add edutir stuff
  newEntity->AddComponent(CT_Editable, newEditable);

  setupMessage(componentName + " created.", ImVec4(0, 1, 0, 1));

  return newEntity;
}


