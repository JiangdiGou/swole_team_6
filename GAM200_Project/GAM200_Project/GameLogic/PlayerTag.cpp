#include "PlayerTag.h"


//playerstate component for reference
void PlayerTag::Initialize()
{
}

void PlayerTag::SerializeWrite(Serializer& str)
{
  StreamWrite(str, (int&)TypeId);
  StreamWrite(str);
}
