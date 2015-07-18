#include "Sprite.h"


Sprite::Sprite()
{
	std::cout << "ERROR: Sprite was Implicitly Constructed.";
	std::cout << "Sprite requires shader to construct properly." << std::endl;
}

Sprite::Sprite(Shader intendedShader)
{
	//Verticies making up the square and texture coordinates 
	GLfloat vertices[] = {
		//X    Y     Z     TexX  TexY
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	};

	//Generates their IDs and saves them in vars
	glGenVertexArrays(1, &vertexArray);
	glGenBuffers(1, &vertexBuffer);

	//Binds the VAO and VBO so future GL fx calls will affet them
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	//Copies the Vertex data into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Tells openGL how to interpret this array of random numbers
	//glVertexAttribPointer
	//Param 1: Location. Which attribute in the vertex shader we're setting up
	//Param 2: Size. How many values the vertex attribute has 
	//Param 3: Type. What type the vertex attributes are
	//Param 4: Normalization. Whether or not the values should be normalized 
	//Param 5: Stride. Space in bytes between attribute sets 
	//Param 6: Offset. After how many bytes the info begins (cast as glvoid*)

	//Sets up Vertex position information
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
		(GLvoid*)0);
	//Activates Vertex Position Information
	glEnableVertexAttribArray(0);

	//Sets up Texture coordinate information 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	//Activates texture coordinate information 
	glEnableVertexAttribArray(1);

	//We're done with the buffers now, so unbinds them 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Initalizes remaining members
	shader = intendedShader;
	scale = glm::vec3(0.5f, 0.5f, 0.5f);
	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = 0;
	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

}

Sprite::~Sprite()
{
	//De allocates resources 
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteBuffers(1, &vertexBuffer);
}

glm::mat4 Sprite::calculateTransorm(void)
{
	glm::mat4 transform;
	transform = glm::translate(transform, translation);
	//Since we're in 2d, rotation occurs about the Z axis
	//Can be changed later if you want different types of rotation
	transform = glm::rotate(transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, scale);

	return transform;
}

void Sprite::Draw(void)
{
	GLint transformLocation, colorLocation;

	glBindVertexArray(vertexArray);
	glBindTexture(GL_TEXTURE_2D, texture);

	//Sends the sprite's transformation matrix into the shader
	transformLocation = glGetUniformLocation(shader.Program, "uniformTransform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE,
			              glm::value_ptr(calculateTransorm()));

	//Sends the sprite's color information in the the shader 
	colorLocation = glGetUniformLocation(shader.Program, "uniformColor");
	glUniform4f(colorLocation, color.w, color.x, color.y, color.z);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


