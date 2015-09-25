#include "text.h"

/* THIS CURRENTLY DOES NOT WORK .*/





Shader* Text::shader = nullptr;
std::map<GLchar, Character> Text::characters = {};
GLuint Text::vertexArray = 0;
GLuint Text::vertexBuffer = 0;

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

  //Try to load a glypg from our font. 
  if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    std::cout << "Failed to load test Glyph X" << std::endl;
  else
    std::cout << "Succssfully accessed glyph from font." << std::endl;

  //Sets up the Height and width of our font 
  FT_Set_Pixel_Sizes(face, 0, 48);
  //Normally, openGL will align textures to 4 bytes, but we want it to be 1 
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
      face->glyph->bitmap.width, face->glyph->bitmap.rows, 0,
      GL_RGBA, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

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

  // Configure VAO/VBO for texture quads
  glGenVertexArrays(1, &vertexArray);
  glGenBuffers(1, &vertexBuffer);
  glBindVertexArray(vertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  //6 times 4 cause six verts in a quad, 4 
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  Text::shader = &shader;

  glm::mat4 projection = 
    glm::ortho(0.0f, static_cast<GLfloat>(WINDOWWIDTH), 0.0f, static_cast<GLfloat>(WINDOWHEIGHT));
  shader.Use();
  glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}

void Text::Update()
{
  // Activate corresponding render state	
  shader->Use();
  glUniform3f(glGetUniformLocation(shader->Program, "textColor"), 1.0f, 1.0f, 1.0f);
  //glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(vertexArray);

  // Iterate through all characters
  std::string::const_iterator c;
  for (c = message.begin(); c != message.end(); c++)
  {
    Character ch = characters[*c];

    GLfloat xpos = translation.x + ch.bearing.x * scale;
    GLfloat ypos = translation.y - (ch.size.y - ch.bearing.y) * scale;

    GLfloat w = ch.size.x * scale;
    GLfloat h = ch.size.y * scale;

    GLfloat vertices[6][4] = {
        { xpos, ypos + h, 0.0, 0.0 },
        { xpos, ypos, 0.0, 1.0 },
        { xpos + w, ypos, 1.0, 1.0 },

        { xpos, ypos + h, 0.0, 0.0 },
        { xpos + w, ypos, 1.0, 1.0 },
        { xpos + w, ypos + h, 1.0, 0.0 }
    };

    glBindTexture(GL_TEXTURE_2D, ch.textureID);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    translation.x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

Text::Text()
{
  std::cout << "This default constructor ain't shit but hoes and tricks" << std::endl;
}

Text::~Text()
{
  std::cout << "This destructor ain't shit but hoes and tricks" << std::endl;
}

Text::Text(std::string initialMessage)
{
  message = initialMessage;
  color = glm::vec3(1.0f, 1.0f, 1.0f);
  translation = glm::vec3(0.0f, 0.0f, 0.0f);
  scale = 1.0f;
}