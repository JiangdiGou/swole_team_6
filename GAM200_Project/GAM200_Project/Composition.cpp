#include "Composition.h"
#include "./gameComponents/objFactory.h"
#include <algorithm>
  //Used to sort components using their type Id.
struct ComponentSorter
{
	bool operator()(GameComponent* left, GameComponent* right)const
	{
		return left->TypeId < right->TypeId;
	}
};

//Binary search a sorted array of components.
GameComponent* BinaryComponentSearch(ComponentArray& components, ComponentTypeId name)
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

GameObjectComposition::GameObjectComposition()
{
	
}

GameObjectComposition::~GameObjectComposition()
{
	//Delete each component using the component's virtual destructor
	//takes care of all resources and memory.
	for (ComponentIt it = Components.begin(); it != Components.end(); ++it)
		delete *it;
}

void GameObjectComposition::AddComponent(ComponentTypeId typeId, GameComponent* component)
{
	//Store the components type Id
	component->TypeId = typeId;
	Components.push_back(component);

	//Sort the component array so binary search can be used to find components quickly.
	std::sort(Components.begin(), Components.end(), ComponentSorter());
}

GameComponent * GameObjectComposition::GetComponent(ComponentTypeId typeId)
{
	return BinaryComponentSearch(Components, typeId);
}

void GameObjectComposition::Destroy()
{
	//Signal the factory that is object needs to be destroyed
	//this will happen at the end of the frame.
	FACTORY->destroyObject(this->ObjectId);
}