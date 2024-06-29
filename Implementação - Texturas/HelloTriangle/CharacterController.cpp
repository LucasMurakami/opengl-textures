#include "CharacterController.h"

// Construtor da classe CharacterController
CharacterController::CharacterController(Shader& shader, GLuint textureID, glm::vec3 position, glm::vec3 scale, float rotation)
    : Sprite(shader, textureID, position, scale, rotation), isJumping(false), positionY(position.y) {}

// Move o personagem para a direita
void CharacterController::moveRight(float deltaTime) {
    position.x += speed * deltaTime;  // Atualiza a posi��o X
    scale.x = abs(scale.x);  // Coloca a escala para x positivo
    updateSprite();  // Atualiza o sprite
}

// Move o personagem para a esquerda
void CharacterController::moveLeft(float deltaTime) {
    position.x -= speed * deltaTime;  // Atualiza a posi��o X
    scale.x = -abs(scale.x);  // Inverte a escala para x negativo
    updateSprite();  // Atualiza o sprite
}

// Faz o personagem pular
void CharacterController::jump(float deltaTime) {
    if (!isJumping && !isFalling) {
        isJumping = true;          // Indica que o personagem est� pulando
        velocityY = jumpStrength;  // Define a velocidade vertical inicial do pulo
    }
}

// Atualiza o estado do personagem
void CharacterController::updateCharacter(float deltaTime) {
    if (isJumping || isFalling) {
        positionY += velocityY * deltaTime;     // Atualiza a posi��o Y com base na velocidade vertical
        velocityY -= gravity * deltaTime;       // Aplica a gravidade na velocidade vertical

        if (positionY <= 0) {
            positionY = 200;                    // Garante que o personagem n�o des�a abaixo do n�vel do ch�o, TELEPORTA (APENAS PARA TESTE)
            isFalling = false;                  // Indica que o personagem n�o est� mais caindo
            velocityY = 0;                      // Reseta a velocidade vertical
        }
        else if (velocityY < 0) {
            isJumping = false;                  // Indica que o personagem n�o est� mais subindo
            isFalling = true;                   // Indica que o personagem est� caindo
        }
    }

    position.y = positionY;  // Atualiza a posi��o Y do personagem
    updateSprite();  // Atualiza o sprite
}