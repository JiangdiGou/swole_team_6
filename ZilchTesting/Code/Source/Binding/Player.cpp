#include "Player.hpp"

Player::Player(const Zilch::String& name, float startingHealth) : Name(name)
{
  InternalHealth = startingHealth;
  std::cout << "Player Created with name: " << Name.c_str() << " and health: " << InternalHealth << "." << std::endl;
}

Player::~Player()
{
  std::cout << "Player Destroyed" << std::endl;
}

// Member Functions
void Player::Speak() const
{
  std::cout << "Player: Hello, I am " << Name.c_str() << std::endl;
}


ZilchDefineType(Player, "Player", ZLib_Internal, builder, type)
{
  // Be sure to always pass the correct types in to all the bindings
  // Do NOT pass Character, for example, and avoid copy pasting from other bindings!

  // Even though we only have a non-overloaded constructor, we unfortunately cannot
  // detect the argument types automatically for constructors due to a limitation in C++
  // The argument types must be explicitly passed in
  ZilchBindConstructor(builder, type, Player, "name, startingHealth", const String&, float);
  ZilchBindDestructor(builder, type, Player);

  ZilchBindField(builder, type, &Player::Name, "Name", PropertyBinding::GetSet);

  // Note that we don't bind Speak again because it gets inherited from the base
}