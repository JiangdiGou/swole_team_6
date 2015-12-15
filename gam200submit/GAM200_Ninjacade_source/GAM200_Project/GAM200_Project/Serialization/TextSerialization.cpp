/******************************************************************************/
/*!
\file   TextSerialization.cpp
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
Text Serializer to save and load our files
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "TextSerialization.h"
#include <string>

namespace Framework
{
	bool TextSerializer::Open(const std::string& file)
	{
#ifdef EDITOR
		stream.open(file.c_str());
#else
    stream.open(file.c_str(), std::ifstream::in);
#endif
		return stream.is_open();
	}

	bool TextSerializer::IsGood()
	{
		return stream.good();
	}

	void TextSerializer::ReadInt(int& i)
	{
		stream >> i;
	}

	void TextSerializer::ReadFloat(float& f)
	{
		stream >> f;
	}

	void TextSerializer::ReadString(std::string& str)
	{
		stream >> str;
	}
  void TextSerializer::ReadVec2(float& f, float& f2)
  {
    ReadFloat(f);
    ReadFloat(f2);
  }
  void TextSerializer::ReadVec3(float& f, float& f2, float& f3)
  {
    ReadFloat(f);
    ReadFloat(f2);
    ReadFloat(f3);
  }

#ifdef EDITOR
  void TextSerializer::WriteVec2(float& f, float& f2)
  {
    WriteFloat(f);
    WriteFloat(f2);
  }
  void TextSerializer::WriteVec3(float& f, float& f2, float& f3)
  {
    WriteFloat(f);
    WriteFloat(f2);
    WriteFloat(f3);
  }

  void TextSerializer::WriteInt(int& i)
  {

    stream << i << ' ';

  }

  void TextSerializer::WriteFloat(float& f)
  {

    stream << f << ' ';

  }

  void TextSerializer::WriteString(std::string& str)
  {

    stream << str << ' ';

  }

  void TextSerializer::WriteEndl()
  {

    stream << '\n';

  }
#endif
}