#include "SpriteText.h"

GLuint SpriteText::shaderID = 0;
GLuint SpriteText::vertexArray = 0;
GLuint SpriteText::vertexBuffer = 0;
GLuint SpriteText::textureBuffer = 0;
Texture* SpriteText::pFont = 0;
std::vector<GLfloat> SpriteText::vertices = {};
std::vector<GLfloat> SpriteText::texCoords = {};
std::map<char, glm::vec2> SpriteText::offsets = {};

void SpriteText::initText(const Shader& shader, Texture* font)
{
  //Generates static members 
  glGenVertexArrays(1, &vertexArray);
  glGenBuffers(1, &vertexBuffer);
  glGenBuffers(1, &textureBuffer);

  //Binds VA and vertex buffer
  glBindVertexArray(vertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    //Sets up vertex buffer information
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

  //Sets up texture buffer information
  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

  //pShader = &shader;
  shaderID = shader.Program;
  pFont = font;

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  loadCharacters();
}

void SpriteText::loadCharacters()
{
  //Lowercase Letters
  for (int i = 97; i <= 122; ++i)
    offsets.insert(std::pair<char, glm::vec2>(i, glm::vec2(43 * (i - 97), 0)));

  //Uppercase Letters
  for (int i = 65; i <= 132; ++i)
    offsets.insert(std::pair<char, glm::vec2>(i, glm::vec2(43 * (i - 65), 83)));
  
  //Numbers 
  for (int i = 48; i <= 57; ++i)
    offsets.insert(std::pair<char, glm::vec2>(i, glm::vec2(43 * (i - 48), 166)));

  //Punctuation ( I should have ordered this more logically. aligned to ascii )
  offsets.insert(std::pair<char, glm::vec2>('`', glm::vec2(43 * 10, 166)));
  offsets.insert(std::pair<char, glm::vec2>('~', glm::vec2(43 * 11, 166)));
  offsets.insert(std::pair<char, glm::vec2>('!', glm::vec2(43 * 12, 166)));
  offsets.insert(std::pair<char, glm::vec2>('@', glm::vec2(43 * 13, 166)));
  offsets.insert(std::pair<char, glm::vec2>('#', glm::vec2(43 * 14, 166)));
  offsets.insert(std::pair<char, glm::vec2>('$', glm::vec2(43 * 15, 166)));
  offsets.insert(std::pair<char, glm::vec2>('^', glm::vec2(43 * 16, 166)));
  offsets.insert(std::pair<char, glm::vec2>('&', glm::vec2(43 * 17, 166)));
  offsets.insert(std::pair<char, glm::vec2>('*', glm::vec2(43 * 18, 166)));
  offsets.insert(std::pair<char, glm::vec2>('(', glm::vec2(43 * 19, 166)));
  offsets.insert(std::pair<char, glm::vec2>(')', glm::vec2(43 * 20, 166)));
  offsets.insert(std::pair<char, glm::vec2>('_', glm::vec2(43 * 21, 166)));
  offsets.insert(std::pair<char, glm::vec2>('-', glm::vec2(43 * 22, 166)));
  offsets.insert(std::pair<char, glm::vec2>('+', glm::vec2(43 * 23, 166)));
  offsets.insert(std::pair<char, glm::vec2>('=', glm::vec2(43 * 24, 166)));
  offsets.insert(std::pair<char, glm::vec2>('|', glm::vec2(43 * 25, 166)));
  //Punctuation some more, but this time, one row down. 
  offsets.insert(std::pair<char, glm::vec2>('[', glm::vec2(43 * 0, 249)));
  offsets.insert(std::pair<char, glm::vec2>(']', glm::vec2(43 * 1, 249)));
  offsets.insert(std::pair<char, glm::vec2>('{', glm::vec2(43 * 2, 249)));
  offsets.insert(std::pair<char, glm::vec2>('}', glm::vec2(43 * 3, 249)));
  offsets.insert(std::pair<char, glm::vec2>(':', glm::vec2(43 * 4, 249)));
  offsets.insert(std::pair<char, glm::vec2>(';', glm::vec2(43 * 5, 249)));
  offsets.insert(std::pair<char, glm::vec2>('\'', glm::vec2(43 * 6, 249)));
  offsets.insert(std::pair<char, glm::vec2>('/', glm::vec2(43 * 7, 249)));
  offsets.insert(std::pair<char, glm::vec2>('?', glm::vec2(43 * 8, 249)));
  offsets.insert(std::pair<char, glm::vec2>('<', glm::vec2(43 * 9, 249)));
  offsets.insert(std::pair<char, glm::vec2>('>', glm::vec2(43 * 10, 249)));
  offsets.insert(std::pair<char, glm::vec2>(',', glm::vec2(43 * 11, 249)));
  offsets.insert(std::pair<char, glm::vec2>('.', glm::vec2(43 * 12, 249)));
  offsets.insert(std::pair<char, glm::vec2>('%', glm::vec2(43 * 13, 249)));
}


void SpriteText::drawAllText()
{
  glUseProgram(shaderID); 

  glBindTexture(GL_TEXTURE_2D, pFont->ID);

  glBindVertexArray(vertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STREAM_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(GLfloat), texCoords.data(), GL_STREAM_DRAW);

  glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3.0f);
  glBindVertexArray(0);

  vertices.clear();
  texCoords.clear();
}

SpriteText::SpriteText(std::string initialMessage)
{
  message = initialMessage;
}

void SpriteText::Update()
{
  std::string::const_iterator characterIt;
  glm::vec3 initialTranslation, initialScale;
  glm::vec4 transformedPosition;
  glm::mat4 transform;
  int newLines = 0;
  int newLinePos = 0;

  glBindVertexArray(vertexArray);
  glUseProgram(shaderID);

  //saves initial translation since its gonna be moved over each time for diffferent letters
  Transform *transformComponent = GetOwner()->has(Transform)

  initialTranslation = glm::vec3(
    transformComponent->GetPosition().x,
    transformComponent->GetPosition().y,
    transformComponent->GetPosition().z);

  initialScale = glm::vec3(
    transformComponent->GetScale().x,
    transformComponent->GetScale().y,
    transformComponent->GetScale().z);

  for (characterIt = message.begin(); characterIt != message.end(); ++characterIt)
  {
    //Deals with Position
    //I do a bit of wonky stuff here, so let me explain
    //I get the translation of the thing, then calculate the 
    //transformation matrix. I apply the transformation matrix
    //on the points now, not in the shader. In the shader, all 
    //text will use an idenity matrix, but the vertices should 
    //already be transformed here 
    //The other kinda wonky thing with text is that as I walk down the word
    //you want to write, I offset the translation by whatever the X scale is 
    //And I added another wornky thing where I offset the initialTranslation
    //by a bunch of halves and negative halves. This is just to make up 
    int characterOffset = characterIt - message.begin() - newLinePos;

    //Handles special cases 
    if (*characterIt == ' ')
      continue;
    else if (*characterIt == '\n')
    {
      ++newLines;
      newLinePos = characterIt - message.begin() + 1;
      continue;
    }

    //Makes a transformation matrix
    //Sets up our fake transformation matrix position and scale
    glm::vec3 newPosition = glm::vec3(
      initialTranslation +
      glm::vec3((characterOffset * transformComponent->GetScale().x), 
        (-newLines * transformComponent->GetScale().y), 0));

    transformComponent->SetPosition(
      newPosition.x,
      newPosition.y,
      newPosition.z);
  
    transformComponent->SetScale(1, 1, 1);
    transform = transformComponent->calculateTransformMatrix();

    //Reset this stuff, it was only for the transformation matrix 
    transformComponent->SetScale(initialScale.x, initialScale.y, initialScale.z);
    transformComponent->SetPosition(initialTranslation.x, initialTranslation.y, initialTranslation.z);

    //Vertex 1
    transformedPosition = (transform * glm::vec4(
      newPosition.x + 0.5*initialScale.x, newPosition.y - 0.5*initialScale.y, 
      newPosition.z, 0));
    vertices.push_back(transformedPosition.x);
    vertices.push_back(transformedPosition.y);
    vertices.push_back(transformedPosition.z);

    //Vertex 2
    transformedPosition = (transform * glm::vec4(
      newPosition.x - 0.5*initialScale.x, newPosition.y + 0.5*initialScale.y, 
      newPosition.z, 0));
    vertices.push_back(transformedPosition.x);
    vertices.push_back(transformedPosition.y);
    vertices.push_back(transformedPosition.z);

    //Vertex 3
    transformedPosition = (transform * glm::vec4(
      newPosition.x - 0.5*initialScale.x, newPosition.y - 0.5*initialScale.y,
      newPosition.z, 0));
    vertices.push_back(transformedPosition.x);
    vertices.push_back(transformedPosition.y);
    vertices.push_back(transformedPosition.z);

    //Vertex 4
    transformedPosition = (transform * glm::vec4(
      newPosition.x + 0.5*initialScale.x, newPosition.y - 0.5*initialScale.y,
      newPosition.z, 0));
    vertices.push_back(transformedPosition.x);
    vertices.push_back(transformedPosition.y);
    vertices.push_back(transformedPosition.z);

    //Vertex 5
    transformedPosition = (transform * glm::vec4(
      newPosition.x + 0.5*initialScale.x, newPosition.y + 0.5*initialScale.y,
      newPosition.z, 0));
    vertices.push_back(transformedPosition.x);
    vertices.push_back(transformedPosition.y);
    vertices.push_back(transformedPosition.z);

    //Vertex 6
    transformedPosition = (transform * glm::vec4(
      newPosition.x - 0.5*initialScale.x, newPosition.y + 0.5*initialScale.y,
      newPosition.z, 0));
    vertices.push_back(transformedPosition.x);
    vertices.push_back(transformedPosition.y);
    vertices.push_back(transformedPosition.z);

    //Deals with tex coords
    pFont->offsetXBytes = offsets[*characterIt].x,
    pFont->offsetYBytes = offsets[*characterIt].y;
    pFont->updateAnimation();

    for (int i = 0; i < 12; ++i)
      texCoords.push_back(pFont->textureCoordinates[i]);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  pFont->offsetXBytes = 0;
  pFont->offsetYBytes = 0;
}

void SpriteText::renderText(std::string message, Vector3 position, Vector3 scale)
{
  std::string::const_iterator characterIt;
  glm::vec3 initialTranslation, initialScale;
  glm::vec4 transformedPosition;
  glm::mat4 transform;
  int newLines = 0;
  int newLinePos = 0;

  glBindVertexArray(vertexArray);
  glUseProgram(shaderID);

  //saves initial translation and scale 
  initialTranslation = glm::vec3(position.x, position.y, position.z);
  initialScale = glm::vec3(scale.x, scale.y, scale.z);

  for (characterIt = message.begin(); characterIt != message.end(); ++characterIt)
  {
    //A lot of convuluted stuff is done in here but its really the same as 
    //the Text's update function so I'm not gonna explain it again here. 
    int characterOffset = characterIt - message.begin() - newLinePos;

    //Handles special cases 
    if (*characterIt == ' ')
      continue;
    else if (*characterIt == '\n')
    {
      ++newLines;
      newLinePos = characterIt - message.begin() + 1;
      continue;
    }

    //Calculates a new position, accounting for offset in the word
    glm::vec3 newPosition = glm::vec3(
      initialTranslation +
      glm::vec3((characterOffset * scale.x), (-newLines * scale.y), 0));

    //Calculates a transformation matrix
    transform = glm::translate(transform,
      glm::vec3(newPosition.x, newPosition.y, newPosition.z));
    transform = glm::rotate(transform, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(1, 1, 1));

    //Vertex 1
    glm::vec4 transformedPosition = (transform * glm::vec4(
      newPosition.x + 0.5*initialScale.x, newPosition.y - 0.5*initialScale.y,
      newPosition.z, 0));
    vertices.push_back(transformedPosition.x);
    vertices.push_back(transformedPosition.y);
    vertices.push_back(transformedPosition.z);

    //Vertex 2
    transformedPosition = (transform * glm::vec4(
      newPosition.x - 0.5*initialScale.x, newPosition.y + 0.5*initialScale.y,
      newPosition.z, 0));
    vertices.push_back(transformedPosition.x);
    vertices.push_back(transformedPosition.y);
    vertices.push_back(transformedPosition.z);

    //Vertex 3
    transformedPosition = (transform * glm::vec4(
      newPosition.x - 0.5*initialScale.x, newPosition.y - 0.5*initialScale.y,
      newPosition.z, 0));
    vertices.push_back(transformedPosition.x);
    vertices.push_back(transformedPosition.y);
    vertices.push_back(transformedPosition.z);

    //Vertex 4
    transformedPosition = (transform * glm::vec4(
      newPosition.x + 0.5*initialScale.x, newPosition.y - 0.5*initialScale.y,
      newPosition.z, 0));
    vertices.push_back(transformedPosition.x);
    vertices.push_back(transformedPosition.y);
    vertices.push_back(transformedPosition.z);

    //Vertex 5
    transformedPosition = (transform * glm::vec4(
      newPosition.x + 0.5*initialScale.x, newPosition.y + 0.5*initialScale.y,
      newPosition.z, 0));
    vertices.push_back(transformedPosition.x);
    vertices.push_back(transformedPosition.y);
    vertices.push_back(transformedPosition.z);

    //Vertex 6
    transformedPosition = (transform * glm::vec4(
      newPosition.x - 0.5*initialScale.x, newPosition.y + 0.5*initialScale.y,
      newPosition.z, 0));
    vertices.push_back(transformedPosition.x);
    vertices.push_back(transformedPosition.y);
    vertices.push_back(transformedPosition.z);

    //Deals with tex coords
    pFont->offsetXBytes = offsets[*characterIt].x,
      pFont->offsetYBytes = offsets[*characterIt].y;
    pFont->updateAnimation();

    for (int i = 0; i < 12; ++i)
      texCoords.push_back(pFont->textureCoordinates[i]);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    pFont->offsetXBytes = 0;
    pFont->offsetYBytes = 0;
  }
}

