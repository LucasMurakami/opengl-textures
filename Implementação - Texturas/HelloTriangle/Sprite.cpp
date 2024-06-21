#include "Sprite.h"
#include <stb_image.h>
#include <iostream>

/* Construtor da Classe Sprite 
Recebe Shader, TextureID, posição, escala e rotação como parâmetros
Chama as funções setupGeometry() e updateModeMatrix() por padrão
*/

Sprite::Sprite(Shader& shader, GLuint textureID, glm::vec3 position, glm::vec3 scale, float rotation)
    : shader(shader), textureID(textureID), position(position), scale(scale), rotation(rotation) {
    setupGeometry();        // Configura a geometria do sprite
    updateModelMatrix();    // Atualiza a matriz de modelo para refletir a posição, escala e rotação inicial
}

// Função para definir a posição
// Atualiza a posição do sprite e recalcula a matriz de modelo
void Sprite::setPosition(const glm::vec3& position) {
    this->position = position;
    update();
}

// Função para definir a escala
// Atualiza a escala do sprite e recalcula a matriz de modelo
void Sprite::setScale(const glm::vec3& scale) {
    this->scale = scale;
    update();
}

// Função para definir a rotação
// Atualiza a rotação do sprite e recalcula a matriz de modelo
void Sprite::setRotation(float rotation) {
    this->rotation = rotation;
    update();
}

// Função para definir a textura
// Atualiza a textura do Sprite
void Sprite::setTexture(GLuint textureID) {
    this->textureID = textureID;
}

// Função para atualizar o sprite
// Chama a função updateModelMatrix para recalcular a matriz de modelo
void Sprite::update() {
    updateModelMatrix();
}

// Função para renderizar o sprite
// Configura o shader, textura, e desenha o sprite na tela
void Sprite::draw() const {
    shader.Use();
    shader.setMat4("model", const_cast<float*>(glm::value_ptr(modelMatrix)));  // Envia a matriz de modelo ao shader
    glActiveTexture(GL_TEXTURE0);                                              // Ativa a unidade de textura 0
    glBindTexture(GL_TEXTURE_2D, textureID);                                   // Vincula a textura ao alvo de textura 2D
    glBindVertexArray(VAO);                                                    // Vincula o Vertex Array Object (VAO)
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);                                       // Desenha os vértices do sprite como um triângulo fan
    glBindVertexArray(0);                                                      // Desassocia o VAO
}

// Função para atualizar o sprite
// Calcula a matriz de modelo com base na posição, rotação e escala do sprite
void Sprite::updateModelMatrix() {
    modelMatrix = glm::mat4(1.0f);                                                                   // Inicializa a matriz de modelo como a matriz identidade
    modelMatrix = glm::translate(modelMatrix, position);                                             // Aplica a translação
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0));        // Aplica a rotação
    modelMatrix = glm::scale(modelMatrix, scale);                                                    // Aplica a escala
}

// Função para retornar a ModelMatrix
glm::mat4 Sprite::getModelMatrix() const {
    return modelMatrix;
}

// Função para retornar o ID da textura atribuída
GLuint Sprite::getTextureID() const {
    return textureID;
}

// Função para VAO e VBO define os atributos de posição, cor e coordenadas da textura
// Define os atributos de posição, cor e coordenadas de textura dos vértices e os armazena em buffers
void Sprite::setupGeometry() {
    GLfloat vertices[] = {
    //      Coordenadas        /       Cores          /    TexCoord
        -0.5f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,       0.0f, 0.0f,     // Lower Left corner
        0.5f, -0.5f, 0.0f,       0.0f, 1.0f, 0.0f,       1.0f, 0.0f,     // Lower right corner
        0.5f, 0.5f, 0.0f,        0.0f, 0.0f, 1.0f,       1.0f, 1.0f,     // Upper right corner
        -0.5f, 0.5f, 0.0f,       1.0f, 1.0f, 0.0f,       0.0f, 1.0f      // Upper left corner
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);                                                              // Gera um buffer de vértices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                                 // Associa o buffer ao alvo de buffer de array
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);          // Envia os dados de vértices para o buffer

    glGenVertexArrays(1, &VAO);                                                         // Gera um Vertex Array Object (VAO)
    glBindVertexArray(VAO);                                                             // Vincula o VAO

    // Define os atributos de vértices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);   // Posição dos vértices
    glEnableVertexAttribArray(0);                                                       // Habilita o atributo de posição

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));   // Cores dos vértices
    glEnableVertexAttribArray(1);                                                                           // Habilita o atributo de cor

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));   // Coordenadas de textura
    glEnableVertexAttribArray(2);                                                       // Habilita o atributo de coordenadas de textura

    glBindBuffer(GL_ARRAY_BUFFER, 0);                                                   // Desassocia o buffer de vértices
    glBindVertexArray(0);                                                               // Desassocia o VAO
}
