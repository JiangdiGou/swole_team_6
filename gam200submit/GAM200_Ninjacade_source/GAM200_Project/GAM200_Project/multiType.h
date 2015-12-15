//
//  multiType.h
//  GAM200_Project
//
//  Created by Nolan Yoo on 9/30/15.
//  All content © 2015 DigiPen (USA) Corporation, all rights reserved.
//

#ifndef GAM200_Project_multiType_h
#define GAM200_Project_multiType_h

enum type {ISINT, ISCHAR, ISFLOAT, ISSTRING};

class multiType
{
public:
  int integer;
  char character;
  float shortDec;
  //double longDec; lua be like: "What's a double?"
  std::string word;
  type wrapperType;
};

#endif
