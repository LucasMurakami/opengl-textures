#include "Sprite.h"
#include <stb_image.h>
#include <iostream>

/* Construtor da Classe Sprite
Recebe Shader, TextureID, posi��o, escala e rota��o como par�metros
Chama as fun��es setupGeometry() e updateModeMatrix() por padr�o
*/

Sprite::Sprite(Shader& shader, GLuint textureID, glm::vec3 position, glm::vec3 scale, float rotation)
    : shader(shader), textureID(textureID), position(position), scale(scale), rotation(rotation) {
    setupGeometry();
    updateModelMatrix();
}

// Fun��o para atualizar o sprite
// Chama a fun��o updateModelMatrix para recalcular a matriz de modelo
void Sprite::updateSprite() {
    updateModelMatrix();
}

// Fun��o para renderizar o sprite
// Configura o shader, textura, e desenha o sprite na tela
void Sprite::draw() const {
    shader.Use();
    shader.setMat4("model", const_cast<float*>(glm::value_ptr(modelMatrix)));  // Envia a matriz de modelo ao shader
    glActiveTexture(GL_TEXTURE0);                                              // Ativa a unidade de textura 0
    glBindTexture(GL_TEXTURE_2D, textureID);                                   // Vincula a textura ao alvo de textura 2D
    glBindVertexArray(VAO);                                                    // Vincula o Vertex Array Object (VAO)
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);                                       // Desenha os v�rtices do sprite como um tri�ngulo fan
    glBindVertexArray(0);                                                      // Desassocia o VAO
}

void Sprite::updateTextureCoords(float frames, float animations, float deltaTime) {
    // Vari�veis para manter controle da anima��o
    static float timeAccumulator = 0.0f;
    static int currentFrame = 0;

    // Atualiza a vari�vel com base no tempo delta
    timeAccumulator += deltaTime;

    // Atualiza o frame se o acumulador de tempo atingir o limite
    if (timeAccumulator >= 1.0f / frames) {
        timeAccumulator = 0.0f; // Reinicia o acumulador de tempo
        currentFrame = (currentFrame + 1) % static_cast<int>(frames); // Avan�a para o pr�ximo frame
    }

    // Calcula os deslocamentos de textura (s e t)
    float ds = 1.0f / frames;
    float dt = 1.0f / animations;
    float offsetS = currentFrame * ds;
    float offsetT = 0.0f;

    // std::cout << "Current Frame: " << currentFrame << std::endl;
    // std::cout << "Texture Coords: " << offsetS << ", " << offsetT << std::endl;

    GLfloat vertices[] = {
        //      Coordenadas        /       Cores          /    TexCoord
            -0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f,       offsetS, 0.0f,             // Lower Left corner
             0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f,       offsetS + ds, 0.0f,        // Lower right corner
             0.5f, 0.5f, 0.0f,       1.0f, 1.0f, 1.0f,       offsetS + ds, dt,          // Upper right corner
            -0.5f, 0.5f, 0.0f,       1.0f, 1.0f, 1.0f,       offsetS, dt                // Upper left corner
    };

    // Atualiza o buffer de v�rtices com os novos dados
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


// Fun��o para atualizar o sprite
// Calcula a matriz de modelo com base na posi��o, rota��o e escala do sprite
void Sprite::updateModelMatrix() {
    modelMatrix = glm::mat4(1.0f);                                                                   // Inicializa a matriz de modelo como a matriz identidade
    modelMatrix = glm::translate(modelMatrix, position);                                             // Aplica a transla��o
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0));        // Aplica a rota��o
    modelMatrix = glm::scale(modelMatrix, scale);                                                    // Aplica a escala
}

// Fun��o para retornar a ModelMatrix
glm::mat4 Sprite::getModelMatrix() const {
    return modelMatrix;
}

// Fun��o para retornar o ID da textura atribu�da
GLuint Sprite::getTextureID() const {
    return textureID;
}

// Fun��o para VAO e VBO define os atributos de posi��o, cor e coordenadas da textura
// Define os atributos de posi��o, cor e coordenadas de textura dos v�rtices e os armazena em buffers
void Sprite::setupGeometry() {
    GLfloat vertices[] = {
        //      Coordenadas        /       Cores          /    TexCoord
            -0.5f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,       0.0f, 0.0f,     // Lower Left corner
             0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,       1.0f, 0.0f,     // Lower right corner
             0.5f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f,       1.0f, 1.0f,     // Upper right corner
            -0.5f, 0.5f, 0.0f,       1.0f, 1.0f, 0.0f,       0.0f, 1.0f      // Upper left corner
    };

    glGenBuffers(1, &VBO);                                                              // Gera um buffer de v�rtices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                                 // Associa o buffer ao alvo de buffer de array
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);          // Envia os dados de v�rtices para o buffer

    glGenVertexArrays(1, &VAO);                                                         // Gera um Vertex Array Object (VAO)
    glBindVertexArray(VAO);                                                             // Vincula o VAO

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);   // Posi��o dos v�rtices
    glEnableVertexAttribArray(0);                                                       // Habilita o atributo de posi��o

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));   // Cores dos v�rtices
    glEnableVertexAttribArray(1);                                                                           // Habilita o atributo de cor

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));   // Coordenadas de textura
    glEnableVertexAttribArray(2);                                                       // Habilita o atributo de coordenadas de textura

    glBindBuffer(GL_ARRAY_BUFFER, 0);                                                   // Desassocia o buffer de v�rtices
    glBindVertexArray(0);                                                               // Desassocia o VAO
}
