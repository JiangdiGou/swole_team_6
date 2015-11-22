#ifndef TEXT_SERIALIZATION_H
#define TEXT_SERIALIZATION_H
#include "Serialization.h"
#include <fstream>

namespace Framework
{
	///Serializer for a simple text file format.
	class TextSerializer : public Serializer
	{
	public:
		std::fstream stream;
		virtual bool Open(const std::string& file);
		virtual bool IsGood();

		virtual void ReadInt(int& i);
		virtual void ReadFloat(float& f);
		virtual void ReadString(std::string& str);
    virtual void ReadVec2(float& f, float& f2);
    virtual void ReadVec3(float& f, float& f2, float& f3);

    virtual void WriteInt(int& i);
    virtual void WriteVec2(float& f, float& f2);
    virtual void WriteVec3(float& f, float& f2, float& f3);
    virtual void WriteFloat(float& f);
    virtual void WriteString(std::string& str);

    virtual void WriteEndl();
	};

}

#endif