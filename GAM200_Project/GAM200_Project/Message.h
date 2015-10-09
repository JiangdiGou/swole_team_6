#ifndef MESSAGE_H
#define MESSAGE_H


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
    FileDrop
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