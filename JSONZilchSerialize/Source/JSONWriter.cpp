#include "JSONWriter.hpp"


namespace GGEngine
{
  // Convert the JSON data to a String
  std::string JSONWriter::ToString()
  {
    // refer to my builder
    Zilch::JsonBuilder myBuilder;

    // run commands on jsonBuilder
    jcmdVector* myData = &(commands);
    for (jcmdVector::iterator iter = myData->begin();
    iter != myData->end();
      ++iter)
    {
      JSONCmd* localCmd = &(*iter);
      JSONMorphic* cmdData = &(localCmd->data);

      switch (localCmd->command)
      {
      case JW_BEGIN:
        myBuilder.Begin(cmdData->beginType);
        break;

      case JW_KEY:
        myBuilder.Key(cmdData->dataString.c_str());
        break;

      case JW_END:
        myBuilder.End();
        break;

      case JW_VALUE:
        BuildValue(cmdData, &myBuilder);
        break;

      default:
        // unlikely once this is done
        break;
      }
    }

    return myBuilder.ToString().c_str();
  }

  // start a JSON item
  void JSONWriter::Begin(JMODE type)
  {
    JSONCmd sentCmd;
    sentCmd.command = JW_BEGIN;
    sentCmd.data.dataType = JT_ENUM;
    sentCmd.data.beginType = type;

    this->commands.push_back(sentCmd);
  }

  // give a JSON item a key
  void JSONWriter::Key(std::string name)
  {
    JSONCmd sentCmd;
    sentCmd.command = JW_KEY;
    sentCmd.data.dataType = JT_KEY;
    sentCmd.data.dataString = name;

    this->commands.push_back(sentCmd);
  }

  // give a JSON key a value
  void JSONWriter::Value(int value)
  {
    JSONCmd sentCmd;
    sentCmd.command = JW_VALUE;
    sentCmd.data.dataType = JT_INT;
    sentCmd.data.dataInt = value;

    this->commands.push_back(sentCmd);
  }

  void JSONWriter::Value(unsigned int value)
  {
    JSONCmd sentCmd;
    sentCmd.command = JW_VALUE;
    sentCmd.data.dataType = JT_UINT;
    sentCmd.data.dataUnsignedInt = value;

    this->commands.push_back(sentCmd);
  }

  void JSONWriter::Value(long value)
  {
    JSONCmd sentCmd;
    sentCmd.command = JW_VALUE;
    sentCmd.data.dataType = JT_LONG;
    sentCmd.data.dataLong = value;

    this->commands.push_back(sentCmd);
  }

  void JSONWriter::Value(unsigned long value)
  {
    JSONCmd sentCmd;
    sentCmd.command = JW_VALUE;
    sentCmd.data.dataType = JT_ULONG;
    sentCmd.data.dataUnsignedLong = value;

    this->commands.push_back(sentCmd);
  }

  void JSONWriter::Value(long long value)
  {
    JSONCmd sentCmd;
    sentCmd.command = JW_VALUE;
    sentCmd.data.dataType = JT_LONGLONG;
    sentCmd.data.dataLongLong = value;

    this->commands.push_back(sentCmd);
  }

  void JSONWriter::Value(unsigned long long value)
  {
    JSONCmd sentCmd;
    sentCmd.command = JW_VALUE;
    sentCmd.data.dataType = JT_LONGLONG;
    sentCmd.data.dataUnsignedLongLong = value;

    this->commands.push_back(sentCmd);
  }

  void JSONWriter::Value(double value)
  {
    JSONCmd sentCmd;
    sentCmd.command = JW_VALUE;
    sentCmd.data.dataType = JT_DOUBLE;
    sentCmd.data.dataDouble = value;

    this->commands.push_back(sentCmd);
  }

  void JSONWriter::Value(std::string value)
  {
    JSONCmd sentCmd;
    sentCmd.command = JW_VALUE;
    sentCmd.data.dataType = JT_STR;
    sentCmd.data.dataString = value;

    this->commands.push_back(sentCmd);
  }

  void JSONWriter::Value(cstr value)
  {
    JSONCmd sentCmd;
    sentCmd.command = JW_VALUE;
    sentCmd.data.dataType = JT_STR;
    sentCmd.data.dataString = value;

    this->commands.push_back(sentCmd);
  }

  void JSONWriter::Value(bool value)
  {
    JSONCmd sentCmd;
    sentCmd.command = JW_VALUE;
    sentCmd.data.dataType = JT_BOOL;
    sentCmd.data.dataBool = value;

    this->commands.push_back(sentCmd);
  }

  void JSONWriter::Null()
  {
    JSONCmd sentCmd;
    sentCmd.command = JW_VALUE;
    sentCmd.data.dataType = JT_NULL;

    this->commands.push_back(sentCmd);
  }

  void JSONWriter::Update(std::string fullKey, int value)
  {
    JSONCmd * updateThis = locateKey(fullKey);

    if (updateThis != nullptr)
    {
      updateThis->data.dataType = JT_INT;
      updateThis->data.dataInt = value;
    }
  }

  void JSONWriter::Update(std::string fullKey, unsigned int value)
  {
    JSONCmd * updateThis = locateKey(fullKey);

    if (updateThis != nullptr)
    {
      updateThis->data.dataType = JT_UINT;
      updateThis->data.dataUnsignedInt = value;
    }
  }

  void JSONWriter::Update(std::string fullKey, long value)
  {
    JSONCmd * updateThis = locateKey(fullKey);

    if (updateThis != nullptr)
    {
      updateThis->data.dataType = JT_LONG;
      updateThis->data.dataLong = value;
    }
  }

  void JSONWriter::Update(std::string fullKey, unsigned long value)
  {
    JSONCmd * updateThis = locateKey(fullKey);

    if (updateThis != nullptr)
    {
      updateThis->data.dataType = JT_ULONG;
      updateThis->data.dataUnsignedLong = value;
    }
  }

  void JSONWriter::Update(std::string fullKey, long long value)
  {
    JSONCmd * updateThis = locateKey(fullKey);

    if (updateThis != nullptr)
    {
      updateThis->data.dataType = JT_LONGLONG;
      updateThis->data.dataLongLong = value;
    }
  }

  void JSONWriter::Update(std::string fullKey, unsigned long long value)
  {
    JSONCmd * updateThis = locateKey(fullKey);

    if (updateThis != nullptr)
    {
      updateThis->data.dataType = JT_ULONGLONG;
      updateThis->data.dataUnsignedLongLong = value;
    }
  }

  void JSONWriter::Update(std::string fullKey, double value)
  {
    JSONCmd * updateThis = locateKey(fullKey);

    if (updateThis != nullptr)
    {
      updateThis->data.dataType = JT_DOUBLE;
      updateThis->data.dataDouble = value;
    }
  }

  void JSONWriter::Update(std::string fullKey, std::string value)
  {
    JSONCmd * updateThis = locateKey(fullKey);

    if (updateThis != nullptr)
    {
      updateThis->data.dataType = JT_STR;
      updateThis->data.dataString = value;
    }
  }

  void JSONWriter::Update(std::string fullKey, cstr value)
  {
    this->Update(fullKey, std::string(value));
  }

  void JSONWriter::Update(std::string fullKey, bool value)
  {
    JSONCmd * updateThis = locateKey(fullKey);

    if (updateThis != nullptr)
    {
      updateThis->data.dataType = JT_BOOL;
      updateThis->data.dataBool = value;
    }
  }

  // end a JSON item
  void JSONWriter::End()
  {
    JSONCmd sentCmd;
    sentCmd.command = JW_END;

    this->commands.push_back(sentCmd);
  }

  // get a new set of commands
  void JSONWriter::Flush()
  {
    this->commands.clear();
  }


  // send value to builder
  void JSONWriter::BuildValue(const JSONMorphic* valueContainer, Zilch::JsonBuilder* myBuilder)
  {
    switch (valueContainer->dataType)
    {
    case JT_INT:
      myBuilder->Value(valueContainer->dataInt);
      break;
    case JT_UINT:
      myBuilder->Value(valueContainer->dataUnsignedInt);
      break;
    case JT_LONG:
      myBuilder->Value(valueContainer->dataLong);
      break;
    case JT_ULONG:
      myBuilder->Value(valueContainer->dataUnsignedLong);
      break;
    case JT_ULONGLONG:
      myBuilder->Value(valueContainer->dataUnsignedLongLong);
      break;
    case JT_DOUBLE:
      myBuilder->Value(valueContainer->dataDouble);
      break;
    case JT_STR:
      myBuilder->Value(valueContainer->dataString.c_str());
      break;
    case JT_BOOL:
      myBuilder->Value(valueContainer->dataBool);
      break;
    case JT_NULL:
      myBuilder->RawValue("null");
      break;
    default:
      break;
    }
  }

  // find a key that was placed in the JSONWriter
  JSONCmd * JSONWriter::locateKey(std::string fullKey)
  {
    //stringVector keyParts = splitUp(fullKey, '.');
    jcmdVector* myData = &(commands);
    std::string foundKey = "";

    bool receivingKey = false;
    bool started = false;
    bool gimme = false;

    for (jcmdVector::iterator iter = myData->begin();
    iter != myData->end();
      ++iter)
    {
      if (gimme)
      {
        return &(*iter);
      }

      JSONCmd * localCmd = &(*iter);

      if (localCmd->command == JW_BEGIN)
      {
        receivingKey = true;
      }

      if (localCmd->command == JW_KEY)
      {
        if (!receivingKey)
        {
          size_t lastPeriod = foundKey.find_last_of('.');
          //make sure we can actually erase a period etc
          if (lastPeriod != std::string::npos)
          {
            foundKey.erase(lastPeriod, foundKey.length());
          }
          else
          {
            foundKey.erase(foundKey.begin(), foundKey.end());
          }
        }
        receivingKey = false;
        started = true;
        foundKey.append(".");
        foundKey.append(localCmd->data.dataString);
      }

      if (localCmd->command == JW_END)
      {
        receivingKey = true;
        size_t lastPeriod = foundKey.find_last_of('.');
        //make sure we can actually erase a period etc
        if (lastPeriod != std::string::npos)
        {
          foundKey.erase(lastPeriod, foundKey.length());
        }
        else
        {
          foundKey.erase(foundKey.begin(), foundKey.end());
        }
      }
      if (foundKey.length() > 0)
      {
        if (foundKey.substr(1).compare(fullKey) == 0)
        {
          gimme = true;
        }
      }
    }

    return nullptr;
  }
}