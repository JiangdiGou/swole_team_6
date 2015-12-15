/******************************************************************************/
/*!
\file   Message.h
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
Engine Depends
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef MESSAGE_H
#define MESSAGE_H

#pragma optimize("", off)

namespace Mid // Message id
{
  enum MessageIdType
  {
    None,
    Quit,
    Collide,
    ToggleDebugInfo,
    CharacterKey,
    MouseButton,
    MouseMove,
    FileDrop,
    CollisionStarted,
    CollisionPersisted,
    CollisionEnded,
    Collision
  };
}

///Base message class. New message types are defined by deriving from this
///class and mapping defined an element of the MessageIdType enumeration.
class Message
{
public:
  Message(Mid::MessageIdType id) : MessageId(id) {};
  Mid::MessageIdType MessageId;
  virtual ~Message() {};
};
#endif // ! 