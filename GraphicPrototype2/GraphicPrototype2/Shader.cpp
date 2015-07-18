#include "Shader.h"

//Default constructor for shader. Doesn't do anything. 
Shader::Shader()
{
}

//Constructor for the Shader Class 
Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	//Loads shader code from file and stores as strings
	std::string vertexString = loadShaderCodeFromFile(vertexPath);
	std::string fragmentString = loadShaderCodeFromFile(fragmentPath);

	//Converts strings to GL char*
	const GLchar* vertexShaderCode = vertexString.c_str();
	const GLchar* fragmentShaderCode = fragmentString.c_str();

	//Compiles Shaders
	GLuint vertexShader = compileShader(vertexShaderCode, SHADERTYPE::VERTEX);
	GLuint fragmentShader = compileShader(fragmentShaderCode,
                                        SHADERTYPE::FRAGMENT);

	//Links Shaders into shader program
	this->Program = compileShaderProgram(vertexShader, fragmentShader);	
}

//Loads shader code from a text file into a std string
std::string Shader::loadShaderCodeFromFile(const GLchar* filePath)
{
	std::string shaderCode;
	std::string tempString;
	std::ifstream inputFile;

	inputFile.open(filePath);

	//If the file was successfully opened 
	if (inputFile.is_open())
	{
		//Loop through the file
		while (!inputFile.eof())
		{
			//Get a line and save it into a temp string
			getline(inputFile, tempString);
			//Add the temp string to the back of the shader code 
			shaderCode.append(tempString);
			//Re-adds the new line cause the code needs it
			shaderCode.push_back('\n');
		}
		//Adds the null zero when done looping
		shaderCode.push_back('\0');
	}
	//If filed failed to open.
	else
	{
		std::cout << "ERROR. Failed open file: " << filePath << std::endl;
		std::cout << "No shader code has been generated." << std::endl;
		shaderCode = "";
	}

	return shaderCode;
}


GLuint Shader::compileShader(const GLchar* shaderCode, SHADERTYPE shaderType)
{
	GLuint shader;
	GLint success;
	GLchar errorLog[512];

	//Generates shader
	if (shaderType == SHADERTYPE::VERTEX)
		shader = glCreateShader(GL_VERTEX_SHADER);
	else if (shaderType == SHADERTYPE::FRAGMENT)
		shader = glCreateShader(GL_FRAGMENT_SHADER);

	//Saves the source code into the shader and compiles 
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);

	//Checks if the shader successfully compiled 
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	//If the shader failed to compile, print out error 
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, errorLog);

		if (shaderType == SHADERTYPE::VERTEX)
			std::cout << "Vertex ";
		else if (shaderType == SHADERTYPE::FRAGMENT)
			std::cout << "Fragment ";

		std::cout << "Compilation Failed\n" << errorLog << std::endl;
	}
  else
  {
      if (shaderType == SHADERTYPE::VERTEX)
          std::cout << "Vertex ";
      else if (shaderType == SHADERTYPE::FRAGMENT)
          std::cout << "Fragment ";

      std::cout << "Shader Compilation Successful." << std::endl;
  }

	return shader;
}

GLuint Shader::compileShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint shaderProgram;
	GLint success;
	GLchar errorLog[512];

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Print linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
      glGetProgramInfoLog(shaderProgram, GL_LINK_STATUS, &success, errorLog);
      std::cout << "Shader Program Linking Failed\n" << errorLog << std::endl;
  }
  else
      std::cout << "Shader Program Linked Successfully." << std::endl;
	
	return shaderProgram;
}


void Shader::Use()
{
	glUseProgram(this->Program);
}