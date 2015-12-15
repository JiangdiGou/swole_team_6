/*****************************************************************************/
/*!
\file    Sprite.cpp
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  Implementation of Sprite, which is the core graphical component of our game
\remarks 
  

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#include "Sprite.h"

GLuint Sprite::shaderID = 0;
GLuint Sprite::atlasID = 0;
std::vector<GLfloat> Sprite::vertices[NUMLAYERS] = {};
std::vector<GLfloat> Sprite::texCoords[NUMLAYERS] = {};
std::vector<GLfloat> Sprite::colors[NUMLAYERS] = {};
GLuint Sprite::vertexArray = 0;
GLuint Sprite::vertexBuffer = 0;
GLuint Sprite::textureBuffer = 0;
GLuint Sprite::colorBuffer = 0;
TextureAtlas* Sprite::atlas = 0;

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

void Sprite::Initialize()
{
  //std::cout << initialTextureName;

}

void Sprite::SerializeRead(Serializer& str)
{
  //???????????????
  StreamRead(str, color.x);
  StreamRead(str, color.y);
  StreamRead(str, color.z);
  StreamRead(str, color.w);
  
  std::string initialTexture = std::string();
  StreamRead(str, initialTexture);
  texture = (atlas->textures)[initialTexture];

  StreamRead(str, flipSprite);
  StreamRead(str, layer);
}
void Sprite::SerializeWrite(Serializer& str)
{
  StreamWrite(str, (int&)TypeId);
  StreamWrite(str);
  StreamWrite(str, color.x);
  StreamWrite(str, color.y);
  StreamWrite(str, color.z);
  StreamWrite(str, color.w);
  StreamWrite(str);
  StreamWrite(str, texture.textureName);
  StreamWrite(str);
  StreamWrite(str, flipSprite);
  StreamWrite(str);
  StreamWrite(str, layer);
  StreamWrite(str);
}

//**********************
//Function    : Sprite.draw
//Input       : none
//Output      : none
//Description : animated sprite if necessary, draws sprite on screen 
//**********************
void Sprite::Update(float dt)
{
  if (!visible)
    return;

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

  /*
  std::cout << "My Texture: " << texture.textureName << std::endl;
  std::cout << "MY scl " << transform->GetScale() << std::endl;
  std::cout << "MY rot " << transform->GetRotation() << std::endl;
  std::cout << "MY pos " << transform->GetPosition() << std::endl;
*/
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
    texCoords[layer].push_back(texture.textureCoordinates[i]);

  //Pushes Color
  //For each of the 6 verts
  for (int i = 0; i < 6; ++i)
  {
    colors[layer].push_back(color.x);
    colors[layer].push_back(color.y);
    colors[layer].push_back(color.z);
    colors[layer].push_back(color.w);
  }

  //Unbind Stuff
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
  
}

void Sprite::initSprites(const Shader& shader, TextureAtlas* spriteAtlas)
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
  atlasID = spriteAtlas->ID;
  atlas = spriteAtlas;

  //Unbind stuff
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Sprite::pushVertices(const glm::vec4 &verts)
{
  //W is not used. It's only a vec4 b/c of matrix mult
  vertices[layer].push_back(verts.x);
  vertices[layer].push_back(verts.y);
  vertices[layer].push_back(verts.z);
}

void Sprite::drawAllSprites()
{
  std::vector<GLfloat> allverts = combineLayers(vertices);
  std::vector<GLfloat> allTextCoords = combineLayers(texCoords);
  std::vector<GLfloat> allColors = combineLayers(colors);

  glUseProgram(shaderID);
  glBindTexture(GL_TEXTURE_2D, atlasID);

  glBindVertexArray(vertexArray);
  //Sends Verts to gfx card
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, allverts.size() * sizeof(GLfloat), allverts.data(), GL_STREAM_DRAW);

  //Sends tex coords to gfx card
  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  glBufferData(GL_ARRAY_BUFFER, allTextCoords.size() * sizeof(GLfloat), allTextCoords.data(), GL_STREAM_DRAW);

  //Sends color to gfx card
  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, allColors.size() * sizeof(GLfloat), allColors.data(), GL_STREAM_DRAW);

  //draws
  glDrawArrays(GL_TRIANGLES, 0, allverts.size() / 3.0f);
  glBindVertexArray(0);

  for (int i = 0; i < NUMLAYERS; ++i)
  {
    vertices[i].clear();
    texCoords[i].clear();
    colors[i].clear();
  }
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

float Sprite::GetColorX()
{
  return color.x;
}
float Sprite::GetColorY()
{
  return color.y;
}
float Sprite::GetColorZ()
{
  return color.z;
}
float Sprite::GetColorW()
{
  return color.w;
}
void Sprite::SetColorX(float val)
{
  color.x = val;
}
void Sprite::SetColorY(float val)
{
  color.y = val;
}
void Sprite::SetColorZ(float val)
{
  color.z = val;
}
void Sprite::SetColorW(float val)
{
  color.w = val;
}

std::vector<GLfloat> Sprite::combineLayers(std::vector<GLfloat> layers[NUMLAYERS])
{
  std::vector<GLfloat> output;

  for (int i = NUMLAYERS - 1; i >= 0; --i)
  {
    output.insert(output.end(), layers[i].begin(), layers[i].end());
  }

  return output;
}

ZilchDefineType(Sprite, "Sprite", ZLib_Internal, builder, type)
{
  type->HandleManager = ZilchManagerId(PointerManager);
  //ZilchBindConstructor(builder, type, Sprite, ZilchNoNames);
  //ZilchBindDestructor(builder, type, Sprite);


  //ZilchBindField(builder, type, &Sprite::texture.textureName, "textureName", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Sprite::flipSprite, "flipSprite", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Sprite::visible, "visible", PropertyBinding::GetSet);

  ZilchBindMethod(builder, type, &Sprite::GetColorX, ZilchNoOverload, "GetColorX", ZilchNoNames);
  ZilchBindMethod(builder, type, &Sprite::GetColorX, ZilchNoOverload, "GetColorY", ZilchNoNames);
  ZilchBindMethod(builder, type, &Sprite::GetColorX, ZilchNoOverload, "GetColorZ", ZilchNoNames);
  ZilchBindMethod(builder, type, &Sprite::GetColorX, ZilchNoOverload, "GetColorW", ZilchNoNames);

  ZilchBindMethod(builder, type, &Sprite::GetColorX, ZilchNoOverload, "GetColorX", ZilchNoNames);
  ZilchBindMethod(builder, type, &Sprite::GetColorX, ZilchNoOverload, "GetColorY", ZilchNoNames);
  ZilchBindMethod(builder, type, &Sprite::GetColorX, ZilchNoOverload, "GetColorZ", ZilchNoNames);
  ZilchBindMethod(builder, type, &Sprite::GetColorX, ZilchNoOverload, "GetColorW", ZilchNoNames);

  //glm::vec4 color;
  //AtlasTexture texture;
}
