#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H

#include "Sprite.h"

class CharacterController : public Sprite {
public:
    CharacterController(Shader& shader, GLuint textureID, glm::vec3 position, glm::vec3 scale, float rotation);

    void moveRight(float deltaTime);  // Move o personagem para a direita
    void moveLeft(float deltaTime);   // Move o personagem para a esquerda
    void jump(float deltaTime);       // Faz o personagem pular
    void updateCharacter(float deltaTime);     // Atualiza o estado do personagem


private:
    bool isJumping = false;             // Indica se o personagem est� pulando
    bool isFalling = false;             // Indica se o personagem est� caindo
    float positionY = 0.0f;             // Posi��o Y atual do personagem
    float jumpStrength = 100.0f;        // For�a do pulo
    float gravity = 45.0f;              // Gravidade que afeta o personagem
    float velocityY = 0.0f;             // Velocidade vertical do personagem
    const float speed = 200.0f;         // Velocidade de movimento horizontal do personagem

    int nx_frames;                      // N�mero de frames na horizontal
    int ny_frames;                      // N�mero de frames na vertical
};

#endif