#ifndef SPRITE_H
#define SPRITE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Sprite {
public:
    // Construtor: inicializa o sprite com o shader, ID da textura, posição, escala e rotação
    Sprite(Shader& shader, GLuint textureID, glm::vec3 position, glm::vec3 scale, float rotation);

    // Define a posição do sprite e atualiza a matriz de modelo
    void setPosition(const glm::vec3& position);

    // Define a escala do sprite e atualiza a matriz de modelo
    void setScale(const glm::vec3& scale);

    // Define a rotação do sprite e atualiza a matriz de modelo
    void setRotation(float rotation);

    // Define a textura do sprite
    void setTexture(GLuint textureID);

    // Atualiza a matriz de modelo do sprite
    void update();

    // Renderiza o sprite na tela
    void draw() const;

    // Retorna a matriz de modelo atual do sprite
    glm::mat4 getModelMatrix() const;

    // Retorna o ID da textura associada ao sprite
    GLuint getTextureID() const;

private:
    Shader& shader;          // Referência ao shader usado pelo sprite
    GLuint textureID;        // ID da textura associada ao sprite
    glm::vec3 position;      // Posição do sprite
    glm::vec3 scale;         // Escala do sprite
    float rotation;          // Rotação do sprite
    GLuint VAO;              // Vertex Array Object do sprite

    // Atualiza a matriz de modelo do sprite com base na posição, rotação e escala
    void updateModelMatrix();

    glm::mat4 modelMatrix;   // Matriz de modelo do sprite

    // Configura a geometria do sprite definindo os atributos de vértices
    void setupGeometry();
};

#endif
