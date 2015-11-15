#include "TextSerialization.h"
#include <string>

namespace Framework
{
	bool TextSerializer::Open(const std::string& file)
	{
		stream.open(file.c_str());
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
}