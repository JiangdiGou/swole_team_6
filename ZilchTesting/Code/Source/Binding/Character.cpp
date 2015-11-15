#include "Character.hpp"


Character::Character()
{
  std::cout << "Character Created" << std::endl;
}

Character::~Character() 
{
  std::cout << "Character Destroyed" << std::endl;
}


// Member Functions

void Character::Speak() const
{
  std::cout << "Character speaks" << std::endl;
}

void Character::Yell(float volume) const
{
  std::cout << "CHARACTER YELLS AT VOLUME " << volume << "!!!!" << std::endl;
}

void Character::Yell() const
{
  std::cout << "CHARACTER YELLS AT NORMAL VOLUME!" << std::endl;
}

float Character::GetHealth() const
{
  return InternalHealth;
}

void Character::SetHealth(float value)
{
  InternalHealth = value;
}

// NOTE: Static function
int Character::ComputeLives(float mana, int level)
{
  return level * 10 + static_cast<int>(mana);
}



/*******************************************************************************
Converts MyReal3 to Zilch::Real3 and back
*******************************************************************************/
inline Zilch::Real3 MyReal3ToReal3(const MyReal3& value)
{
  return Zilch::Real3(value.my_x, value.my_y, value.my_z);
}

inline MyReal3 Real3ToMyReal3(const Zilch::Real3& value)
{
  return MyReal3(value.x, value.y, value.z);
}
ZilchDefineRedirectType(MyReal3, MyReal3ToReal3, Real3ToMyReal3);



// This allows us to define all the members on Character (as well as which library it belongs to: ZLib_Internal)
// The 'builder' and 'type' members are only there to let the user know they can do builder->... or type->...
ZilchDefineType(Character, "Character", ZLib_Internal, builder, type)
{
  // Binding Constructor / Destructor

  // The 'ZilchNoNames' macro is simply a way of saying that there are no parameter names for the argument types
  // Zilch supports named parameter calling, so feel free to provide them

  // We should generally always bind a constructor and destructor,
  // especially if this is a dervied class and the base is constructable

  ZilchBindConstructor(builder, type, Character, ZilchNoNames);
  ZilchBindDestructor(builder, type, Character);

  // Binding Methods

  // The 'ZilchNoOverload' lets the binding know that there are no overloads of the same name
  // Otherwise, we'd have to pass in the type/signature of the member function in parentheses
  ZilchBindMethod(builder, type, &Character::Speak, ZilchNoOverload, "Speak", ZilchNoNames);

  // Bind both overloads of Yell
  ZilchBindMethod(builder, type, &Character::Yell, (void (Character::*)(float) const), "Yell", "volume");
  ZilchBindMethod(builder, type, &Character::Yell, (void (Character::*)() const), "Yell", ZilchNoNames);

  // The binding templates/macros can automatically determine if you're binding a static or instance member function
  // You can also bind global functions to a class
  ZilchBindMethod(builder, type, &Character::ComputeLives, ZilchNoOverload, "ComputeLives", "mana, level");


  // Binding Fields

  // Zilch does not have the concept of 'const' (therefore we remove all consts from bound C++ members)
  // It is up to us to be very careful here and bind const members as 'Get' only
  ZilchBindField(builder, type, &Character::MaxLives, "MaxLives", PropertyBinding::Get);
  ZilchBindField(builder, type, &Character::Lives, "Lives", PropertyBinding::GetSet);

  ZilchBindField(builder, type, &Character::Lives, "Position", PropertyBinding::GetSet);

  // We can specially bind getters and setters in C++ as a single property in Zilch
  ZilchBindProperty(builder, type, &Character::GetHealth, &Character::SetHealth, "Health");


  // BINDING CUSTOM TYPE

  // Character::MyPosition is of type 'MyReal3'.
  ZilchBindField(builder, type, &Character::MyPosition, "MyPosition", PropertyBinding::GetSet);

  // NOTE: WE explicitly did not bind 'InternalHealth'
}