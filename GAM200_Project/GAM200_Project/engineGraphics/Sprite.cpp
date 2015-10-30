#include "Sprite.h"

GLuint Sprite::shaderID = 0;
GLuint Sprite::atlasID = 0;
std::vector<GLfloat> Sprite::vertices = {};
std::vector<GLfloat> Sprite::texCoords = {};
std::vector<GLfloat> Sprite::colors = {};
GLuint Sprite::vertexArray = 0;
GLuint Sprite::vertexBuffer = 0;
GLuint Sprite::textureBuffer = 0;
GLuint Sprite::colorBuffer = 0;

//**********************
//Function    : Sprite
//Input       : none
//Output      : Sprite - The constructed Sprite 
//Description : Constructor for the sprite class 
//**********************
Sprite::Sprite()
{
	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

//**********************
//Function    : Sprite
//Input       : none
//Output      : none
//Description : deConstructor for sprite, frees resources
//**********************
Sprite::~Sprite()
{
}


//**********************
//Function    : Sprite.draw
//Input       : none
//Output      : none
//Description : animated sprite if necessary, draws sprite on screen 
//**********************
void Sprite::Update(float dt)
{
  glm::vec4 transformedPosition, initialPosition;
  glm::vec3 scale;

  glBindVertexArray(vertexArray);
  glUseProgram(shaderID);

  //Initialize vars I'm gonna need
  Transform *transform = GetOwner()->has(Transform);
  glm::mat4 transformMatrix = transform->calculateTransformMatrix();
  initialPosition = glm::vec4(
    transform->GetPosition().x,
    transform->GetPosition().y,
    transform->GetPosition().z,
    0);

  scale = glm::vec3(
    transform->GetScale().x,
    transform->GetScale().y,
    transform->GetScale().z);

  //Vertex 1
  transformedPosition = glm::vec4(transformMatrix * glm::vec4(
     0.5, //* scale.x,
    - 0.5, //* scale.y,
    0, 1));
  pushVertices(transformedPosition);

  //Vertex 2
  transformedPosition = glm::vec4(transformMatrix * glm::vec4(
    - 0.5,// * scale.x,
     0.5,// * scale.y,
    0, 1));
  pushVertices(transformedPosition);

  //Vertex 3
  transformedPosition = glm::vec4(transformMatrix * glm::vec4(
    - 0.5, //* scale.x,
    - 0.5, // * scale.y,
    0, 1));
  pushVertices(transformedPosition);

  //Vertex 4
  transformedPosition = glm::vec4(transformMatrix * glm::vec4(
     0.5, // * scale.x,
    - 0.5, // * scale.y,
    0, 1));
  pushVertices(transformedPosition);

  //Vertex 5
  transformedPosition = glm::vec4(transformMatrix * glm::vec4(
     0.5, // * scale.x,
     0.5, // * scale.y,
    0, 1));
  pushVertices(transformedPosition);

  //Vertex 6
  transformedPosition = glm::vec4(transformMatrix * glm::vec4(
    - 0.5, // * scale.x,
     0.5, //* scale.y,
    0, 1));
  pushVertices(transformedPosition);

  //Pushes tex coords 
  texture.updateAnimation();
  for (int i = 0; i < 12; ++i)
    texCoords.push_back(texture.textureCoordinates[i]);

  //Pushes Color
  //For each of the 6 verts
  for (int i = 0; i < 6; ++i)
  {
    colors.push_back(color.x);
    colors.push_back(color.y);
    colors.push_back(color.z);
    colors.push_back(color.w);
  }

  //Unbind Stuff
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
  
}

void Sprite::initSprites(const Shader& shader, const TextureAtlas& atlas)
{
  //Generates Static Members
  glGenVertexArrays(1, &vertexArray);
  glGenBuffers(1, &vertexBuffer);
  glGenBuffers(1, &textureBuffer);
  glGenBuffers(1, &colorBuffer);

  //Binds VA and vertex buffer
  glBindVertexArray(vertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

  //Set up vertex buffer information
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

  //Set up texture buffer information
  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

  //Set up the color buffer information
  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

  shaderID = shader.Program;
  atlasID = atlas.ID;

  //Unbind stuff
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Sprite::pushVertices(const glm::vec4 &verts)
{
  //W is not used. It's only a vec4 b/c of matrix mult
  vertices.push_back(verts.x);
  vertices.push_back(verts.y);
  vertices.push_back(verts.z);
}

void Sprite::drawAllSprites()
{
  glUseProgram(shaderID);

  glBindTexture(GL_TEXTURE_2D, atlasID);

  glBindVertexArray(vertexArray);
  //Sends Verts to gfx card
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STREAM_DRAW);

  //Sends tex coords to gfx card
  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(GLfloat), texCoords.data(), GL_STREAM_DRAW);

  //Sends color to gfx card
  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), colors.data(), GL_STREAM_DRAW);

  //draws
  glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3.0f);
  glBindVertexArray(0);

  vertices.clear();
  texCoords.clear();
}

void Sprite::SendMessages(Message * message)
{
  if (flipSprite)
  {
    switch (message->MessageId)
    {
    case Mid::CharacterKey:
    {
      MessageCharacterKey* keyMsg = (MessageCharacterKey*)message;
      Transform* tform = GetOwner()->has(Transform);
      switch (keyMsg->character)
      {
      case 'a':
      {
        if (!facingRight)
        {
          facingRight = true;
          tform->SetScaleX(tform->GetScale().x * -1.0f);
        }
      }
      case 'd':
      {
        if (facingRight)
        {
          facingRight = false;
          tform->SetScaleX(tform->GetScale().x * -1.0f);
        }
      }

      }
    }
    }
  }
}