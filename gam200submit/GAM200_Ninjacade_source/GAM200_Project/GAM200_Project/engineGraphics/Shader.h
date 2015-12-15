/*****************************************************************************/
/*!
\file    Shader.h
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  Interface of the shader class, which is responsible for compiling and
  linking shaders, as well as storing shader information
\remarks 
  

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#ifndef SHADER_H
#define SHADER_H

#include "Graphics.h"

#include<string>
#include<fstream>

enum SHADERTYPE {VERTEX, FRAGMENT};

class Shader
{
  public:
	  //Default Constructor does nothing 
	  Shader();
	  //Constructor makes a shader from two files 
	  Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	  //Shader Program ID 
	  GLuint Program;
	  //Tells OpenGL to use this shader 
    void Use() const;

    static std::vector < Shader* > shaders;

  private:
	  std::string loadShaderCodeFromFile(const GLchar* filePath);
	  GLuint compileShader(const GLchar* ShaderCode,
			SHADERTYPE shaderType);
	  GLuint compileShaderProgram(GLuint vertexShader, GLuint fragmentShader);
};
	
#endif
