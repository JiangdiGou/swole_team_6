#include "Composition.h"
#include "gameComponents/objFactory.h"
#include <algorithm>
#include "physicsLib\Transform.h"
#include "ZilchComponent.h"

objFactory *FACTORY;//extern I believe still requires the declaration

  //Used to sort components using their type Id.
struct ComponentSorter
{
	bool operator()(GameComponent* left, GameComponent* right)const
	{
		return left->TypeId < right->TypeId;
	}
};

//Binary search a sorted array of components.
GameComponent* BinaryComponentSearch(const ComponentArray& components, ComponentTypeId name)
{
	size_t begin = 0;
	size_t end = components.size();

	while (begin < end)
	{
		size_t mid = (begin + end) / 2;
		if (components[mid]->TypeId < name)
		begin = mid + 1;
		else
		end = mid;
	}

	if ((begin < components.size()) && (components[begin]->TypeId == name))
		return components[begin];
	else
		return NULL;
}
GameComponent* BinaryZilchComponentSearch(const ZilchComponentArray& components, ZilchComponentTypeId name)
{
  size_t begin = 0;
  size_t end = components.size();

  while (begin < end)
  {
    size_t mid = (begin + end) / 2;
    if (components[mid]->TypeId < name)
      begin = mid + 1;
    else
      end = mid; 
  }

  if ((begin < components.size()) && (components[begin]->TypeId == name))
    return (GameComponent*)components[begin];
  else
    return NULL;
}

void GameObjectComposition::Initialize()
{
	//Initialize every component on this composition
	//and set their composition owner. This allows each
	//component to initialize itself separate from its constructor.
	//Which is need for serialization and to allow components to get
	//pointers to each other during initialization.

	for (ComponentIt it = Components.begin(); it != Components.end(); ++it)
	{
		(*it)->Base = this;
		(*it)->Initialize();
	}
}
void GameObjectComposition::SerializeRead(Serializer& str)
{
  str.ReadString(ObjectName);
  for (ComponentIt it = Components.begin(); it != Components.end(); ++it)
  {
    (*it)->SerializeRead(str);
  }
}
void GameObjectComposition::SerializeWrite(Serializer& str)
{
  std::string NewObj = "#";
  str.WriteString(NewObj);
  str.WriteEndl();
  str.WriteString(ObjectName);
  str.WriteEndl();
  for (ComponentIt it = Components.begin(); it != Components.end(); ++it)
  {
    (*it)->SerializeWrite(str);
  }
}

void GameObjectComposition::Update(float dt)
{
	//Can I check for existence of actions?
	Actions.Update(dt);
	
  for (ComponentIt it = Components.begin(); it != Components.end(); ++it)
  {
	  (*it)->Update(dt);
  }
}
GameObjectComposition::GameObjectComposition() : Actions(ActionGroup())
{
	
}

GameObjectComposition::~GameObjectComposition()
{
	//Delete each component using the component's virtual destructor
	//takes care of all resources and memory.
  for (ComponentIt it = Components.begin(); Components.size() > 0; it = Components.begin())
  {
    (*it)->~GameComponent();
    Components.erase(it);
  }
}

void GameObjectComposition::AddComponent(ComponentTypeId typeId, GameComponent* component)
{
	//Store the components type Id
	component->TypeId = typeId;
	Components.push_back(component);
  if (typeId == CT_OurZilchComponent)
    ZilchComponents.push_back((OurZilchComponent*)component);

	//Sort the component array so binary search can be used to find components quickly.
	std::sort(Components.begin(), Components.end(), ComponentSorter());
}

//Returns false if component could not be found. 
bool GameObjectComposition::RemoveComponent(ComponentTypeId typeId, GameComponent* toBeRemoved)
{
  if (toBeRemoved != NULL)
  {
    ComponentIt found = std::find(Components.begin(), Components.end() + 1, toBeRemoved);
    if (found == Components.end() + 1)
      return false;

    if (typeId == CT_Body)
    {
      //PHYSICS->Bodies.erase(std::find(PHYSICS->Bodies.begin(), PHYSICS->Bodies.end(), (Body*)toBeRemoved));
      std::cout << "Error, Can't Remove physics" << std::endl;
      return false;
    }

    Components.erase(found);
    Components.shrink_to_fit();
    delete toBeRemoved;   
    Initialize();
    return true;
  }
  else
    return false;

}

GameComponent * GameObjectComposition::GetComponent(ComponentTypeId typeId) const
{
	return BinaryComponentSearch(Components, typeId);
}

GameComponent * GameObjectComposition::GetZilchComponent(ZilchComponentTypeId typeId) const
{
  return BinaryZilchComponentSearch(ZilchComponents, typeId);
}
void GameObjectComposition::Destroy()
{
	//Signal the factory that is object needs to be destroyed
	//this will happen at the end of the frame.
	//FACTORY = new objFactory();
	FACTORY->destroyObject(this->ObjectId);
}

void GameObjectComposition::SendMessages(Message * message)
{
  //When a message is sent to a composition it sends to
  //all of its components
  //for( MapIt it = Map.begin();it!=Map.end();++it)
  for (ComponentIt it = Components.begin(); it != Components.end(); ++it)
    (*it)->SendMessages(message);

}

GameObjectComposition* GameObjectComposition::FindObject(std::string name)
{
  return FACTORY->FindObjectByName(name);
}

ZilchDefineType(GameObjectComposition, "GameObjectComposition", ZLib_Internal, builder, type)
{
  type->HandleManager = ZilchManagerId(PointerManager);
  //Getting and Adding COMPS. Zilch
  ZilchBindMethod(builder, type, &GameObjectComposition::GetComponent, ZilchNoOverload, "GetComponent", ZilchNoNames);
  ///ZilchBindMethod(builder, type, &GameObjectComposition::AddComponent, ZilchNoOverload, "AddComponent", ZilchNoNames);

  //ZilchBindMethod(builder, type, &GameObjectComposition::SendMessages, ZilchNoOverload, "SendMessages", ZilchNoNames);
  //ZilchBindMethod(builder, type, &GameObjectComposition::GetComponentType, ZilchNoOverload, "GetComponent", ZilchNoNames);

  ZilchBindMethod(builder, type, &GameObjectComposition::Initialize, ZilchNoOverload, "Initialize", ZilchNoNames);
  ZilchBindMethod(builder, type, &GameObjectComposition::Update, ZilchNoOverload, "Update", ZilchNoNames);

  //ZilchBindMethod(builder, type, &GameObjectComposition::SerializeRead, ZilchNoOverload, "SerializeRead", ZilchNoNames);
  //ZilchBindMethod(builder, type, &GameObjectComposition::SerializeWrite, ZilchNoOverload, "SerializeWrite", ZilchNoNames);

  ZilchBindMethod(builder, type, &GameObjectComposition::Destroy, ZilchNoOverload, "Destroy", ZilchNoNames);
  ///ZilchBindMethod(builder, type, &GameObjectComposition::GetId, ZilchNoOverload, "GetId", ZilchNoNames);

  ZilchBindMethod(builder, type, &GameObjectComposition::GetName, ZilchNoOverload, "GetName", ZilchNoNames);
  ZilchBindMethod(builder, type, &GameObjectComposition::FindObject, ZilchNoOverload, "GetName", ZilchNoNames);

  ///Type safe way of accessing components.
  //template<typename type>
  //type* GetComponentType(ComponentTypeId typeId);

  //A group of actions
  //ActionGroup Actions;

}