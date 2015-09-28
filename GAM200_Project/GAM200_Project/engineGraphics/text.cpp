#include "text.h"

std::map<GLchar, Character> Text::characters = {};
GLuint Text::vertexArray = 0;
GLuint Text::vertexBuffer = 0;
GLuint Text::textureBuffer = 0;

void Text::initText(Shader shader)
{
  //First, check to make sure we can access the library
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
    std::cout << "Could not init FreeType Library" << std::endl;
  else
    std::cout << "Successfully initialized the FreeType Library" << std::endl;

  //Next, try to load a font 
  FT_Face face;
  if (FT_New_Face(ft, "resources/fonts/OpenSans-Regular.ttf", 0, &face))
    std::cout << "Failed to load font" << std::endl;
  else
    std::cout << "Freetype successfully loaded a font." << std::endl;

  //Sets up the Height and width of our font 
  FT_Set_Pixel_Sizes(face, 0, 48);

  //Try to load a glypg from our font. 
  if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    std::cout << "Failed to load test Glyph X" << std::endl;
  else
    std::cout << "Succssfully accessed glyph from font." << std::endl;


  //Normally, openGL will align textures to 4 bytes, but we want it to be 1 
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

  generateTexturesFromFont(face);

  GLfloat vertices[] = {
    //X    Y     Z     
    0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
  };

  GLfloat texCoords[] = {
    //X   Y
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f
  };

  // Configure VAO/VBO for texture quads
  glGenVertexArrays(1, &vertexArray);
  glGenBuffers(1, &vertexBuffer);
  glGenBuffers(1, &textureBuffer);

  //Binds the VAO and VBO so future GL fx calls will affet them
  glBindVertexArray(vertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

  //Copies the Vertex data into the buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  //Sets up Vertex position information
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  //Activates Vertex Position Information
  glEnableVertexAttribArray(0);

  //Binds the texture buffer and sends it data 
  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STREAM_DRAW);

  //Sets up Texture coordinate information 
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  //Activates texture coordinate information 
  glEnableVertexAttribArray(1);

  //We're done with the buffers now, so unbinds them 
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  FT_Done_Face(face);
  FT_Done_FreeType(ft);

}

void Text::Update()
{
  GLint transformLocation, colorLocation;
  std::string::const_iterator characterIt;
  glm::vec3 initialTranslation;

  glBindVertexArray(vertexArray);
  shader.Use();

  //saves initial translation since its gonna be moved over each time for diffferent letters
  Transform *transformComponent = GetOwner()->has(Transform)

  
  initialTranslation = glm::vec3(
    transformComponent->GetPosition().x,
    transformComponent->GetPosition().y,
    transformComponent->GetPosition().z);

  for (characterIt = message.begin(); characterIt != message.end(); ++characterIt)
  {
    //Binds the texture from the map
    glBindTexture(GL_TEXTURE_2D, characters[*characterIt].textureID);
    //Moves over based on how far along w3e are in the word
    glm::vec3 newPosition = glm::vec3(
      initialTranslation +
      glm::vec3(((characterIt - message.begin())*-transformComponent->GetScale().x), 0, 0)
      );
    transformComponent->SetPosition(
      newPosition.x,
      newPosition.y,
      newPosition.z);

    //Sends the text's transformation matrix into the shader
    transformLocation = glGetUniformLocation(shader.Program, "uniformTransform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE,
      glm::value_ptr(calculateTransform()));

    glDrawArrays(GL_TRIANGLES, 0, 6);
 
    glBindTexture(GL_TEXTURE_2D, 0);
    //Since we actually modified the translation, reset it for the next letter
    transformComponent->SetPosition(initialTranslation.x, initialTranslation.y, initialTranslation.z);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

Text::Text(std::string initialMessage, Shader textShader)
{
  message = initialMessage;
  /*translation = glm::vec3(0.0f, 0.0f, 0.0f);
  scale = glm::vec3(-0.5f, 0.5f, 1.0f);*/
  shader = textShader;
}

void Text::generateTexturesFromFont(FT_Face face)
{

  //Loops through the first 128 characters and saves all their data into a map
  for (GLubyte c = 0; c < 128; c++)
  {
    // Load character glyph 
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
      std::cout << "When generating alphabet, Failed to load Glyph" << std::endl;
      continue;
    }

    // Generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //GLTEXIMAGE2D
    //p1 - target
    //p2 - level(has to do with mipmaps)
    //p3 - internal format of texture 
    //p4 - width
    //p5 - height
    //p6 - always 0
    //p7 - same as p3
    //p8 - type of data
    //p9 - data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
      face->glyph->bitmap.width, face->glyph->bitmap.rows, 0,
      GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Now store character for later use
    Character character = {
      texture,
      glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      face->glyph->advance.x
    };

    Text::characters.insert(std::pair<GLchar, Character>(c, character));
  }
}

//This is straight copypasta'd from the sprite class. I modeled this after the sprite class to get it to work,
//and for some reason, It wont let me send matricies but through this function. I can look into it more later, 
//I'm just trying to finish up what i've got so far. 
glm::mat4 Text::calculateTransform()
{
  glm::mat4 transform, translate, rotate, scale;
  Transform *transformComponent = GetOwner()->has(Transform)

    transform = glm::translate(transform,
    glm::vec3(
    transformComponent->GetPosition().x,
    transformComponent->GetPosition().y,
    transformComponent->GetPosition().z
    ));
  //Since we're in 2d, rotation occurs about the Z axis
  //Can be changed later if you want different types of rotation
  transform = glm::rotate(transform, (transformComponent->GetRotation()).z, glm::vec3(0.0f, 0.0f, 1.0f));
  transform = glm::scale(transform,
    glm::vec3(
    transformComponent->GetPosition().x,
    transformComponent->GetPosition().y,
    transformComponent->GetPosition().z
    ));

  return transform;
}
