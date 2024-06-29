#ifndef SPRITE_H
#define SPRITE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Sprite {
public:
    // Construtor: inicializa o sprite com o shader, ID da textura, posi��o, escala
    Sprite(Shader& shader, GLuint textureID, glm::vec3 position, glm::vec3 scale, float rotation);

    // Atualiza a matriz de modelo do sprite
    void updateSprite();

    // Renderiza o sprite na tela
    void draw() const;

    // Atualiza o estado da textura
    void updateTextureCoords(float frames, float animations, float deltaTime);

    // Retorna a matriz de modelo atual do sprite
    glm::mat4 getModelMatrix() const;

    // Retorna o ID da textura associada ao sprite
    GLuint getTextureID() const;


protected:
    // Vari�veis de renderiza��o do objeto Sprite
    Shader& shader;          // Refer�ncia ao shader usado pelo sprite
    GLuint textureID;        // ID da textura associada ao sprite
    glm::vec3 position;      // Posi��o do sprite
    glm::vec3 scale;         // Escala do sprite
    float rotation;          // Rota��o do sprite
    GLuint VAO;              // Vertex Array Object do sprite
    GLuint VBO;              // Vertex Buffer Object do sprite
    glm::mat4 modelMatrix;   // Matriz de modelo do sprite

    // Atualiza a matriz de modelo do sprite com base na posi��o, rota��o e escala
    void updateModelMatrix();

    // Configura a geometria do sprite definindo os atributos de v�rtices
    void setupGeometry();
};

#endif
