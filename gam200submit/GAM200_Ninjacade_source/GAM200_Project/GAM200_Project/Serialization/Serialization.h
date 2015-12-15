/******************************************************************************/
/*!
\file   Serialization.h
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
Virtual Base Serializer
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef SERIALIZATION_H
#define SERIALIZATION_H
#include "../physicsLib/math_utility.h"
	//Base Serializaer Class
	class Serializer
	{
	public:
		///Open the serialization stream from a file.
		virtual bool Open(const std::string& file)=0;
		///Does the stream still have data?
		virtual bool IsGood()=0;
		virtual void ReadInt(int& i)=0;
		virtual void ReadFloat(float& f)=0;
		virtual void ReadString(std::string& str)=0;
    virtual void ReadVec2(float& f, float& f2) = 0;
    virtual void ReadVec3(float& f, float& f2, float& f3) = 0;
    virtual void WriteInt(int& i) = 0;
    virtual void WriteFloat(float& f) = 0;
    virtual void WriteString(std::string& str) = 0;
    virtual void WriteVec2(float& f, float& f2) = 0;
    virtual void WriteVec3(float& f, float& f2, float& f3) = 0;
    virtual void WriteEndl() = 0;
	};

	//Serialization Operators 


	//Base case of serialization is that the object serializes itself.
	/*template<typename type>
	inline void StreamRead(Serializer& stream,type& typeInstance)
	{
		stream.Serialize(stream);
	}
  template<typename type>
  inline void StreamWrite(Serializer& stream, type& typeInstance)
  {
    stream.Serialize(stream);
  }*/
	//Base non recursive stream operators of fundamental types.

	inline void StreamRead(Serializer& stream,float& f)
	{
		stream.ReadFloat(f);
	}

	inline void StreamRead(Serializer& stream,int& i)
	{
		stream.ReadInt(i);
	}
  inline void StreamRead(Serializer& stream, bool& i)
  {
    int boolVal;
    stream.ReadInt(boolVal);
    if (boolVal == 1)
      i = true;
    else
      i = false;
  }

	inline void StreamRead(Serializer& stream,std::string& str)
	{
		stream.ReadString(str);
	}
  inline void StreamRead(Serializer& stream, Vec2D& vector)
  {
    stream.ReadVec2(vector.x, vector.y);
  }
  inline void StreamRead(Serializer& stream, Vector3& vector)
  {
    stream.ReadVec3(vector.x, vector.y, vector.z);
  }


  inline void StreamWrite(Serializer& stream, float& f)
  {
    stream.WriteFloat(f);
  }
  inline void StreamWrite(Serializer& stream, Vec2D& vector)
  {
    stream.WriteVec2(vector.x, vector.y);
  }
  inline void StreamWrite(Serializer& stream, Vector3& vector)
  {
    stream.WriteVec3(vector.x, vector.y, vector.z);
  }
  inline void StreamWrite(Serializer& stream, int& i)
  {
    stream.WriteInt(i);
  }
  inline void StreamWrite(Serializer& stream, bool& i)
  {
    int boolVal;
    if (i == true)
      boolVal = 1;
    else
      boolVal = 0;
    stream.WriteInt(boolVal);
  }
  inline void StreamWrite(Serializer& stream, std::string& str)
  {
    stream.WriteString(str);
  }

  inline void StreamWrite(Serializer& stream)
  {
    stream.WriteEndl();
  }


#endif