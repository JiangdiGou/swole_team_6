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
	  void Use();
  private:
	  std::string loadShaderCodeFromFile(const GLchar* filePath);
	  GLuint compileShader(const GLchar* ShaderCode,
			SHADERTYPE shaderType);
	  GLuint compileShaderProgram(GLuint vertexShader, GLuint fragmentShader);
};
	
#endif
