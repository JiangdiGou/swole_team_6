/******************************************************************************/
/*!
\file   ComponentCreator.h
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
Declarations for ComponentCreator
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef COMPONENTCREATOR_H
#define COMPONENTCREATOR_H
#include "ComponentTypeIds.h"
  class GameComponent;

  //Game Component Creator Interface.
  //To be implemented in factory for data driven component creation
  class ComponentCreator
  {
  public:
    ComponentCreator(ComponentTypeId typeId)
      :TypeId(typeId)
    {
    }

    ComponentTypeId TypeId;
    //Create component
    virtual GameComponent * Create() = 0;
  };

  //Templated class to make component creators.
  template<typename type>
  class ComponentCreatorType : public ComponentCreator
  {
  public:
    ComponentCreatorType(ComponentTypeId typeId)
      :ComponentCreator(typeId)
    {
    }

    virtual GameComponent * Create()
    {
      return new type();
    }
  };

//Register component macro
#define RegisterComponent(type) FACTORY->AddComponentCreator( #type, new ComponentCreatorType<type>( CT_##type ) );
#endif