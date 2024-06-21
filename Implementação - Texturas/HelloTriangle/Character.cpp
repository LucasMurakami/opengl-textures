#include "Character.h"

Character::Character(Shader& shader, const std::vector<GLuint>& walkTextures, glm::vec3 position)
    : sprite(shader, idleTextures[0], position, glm::vec3(100.0f, 100.0f, 0.0f), 0.0f), walkTextures(walkTextures), position(position) {
    state = IDLE;
    animationTime = 0.0f;
    currentFrame = 0;
    positionX = position.x;
}

void Character::update(float deltaTime) {
    animationTime += deltaTime;

    // Update state and position
    if (state == WALKING_RIGHT) {
        positionX += 100.0f * deltaTime; // Adjust speed as needed
        if (positionX >= 700.0f) {
            state = WALKING_LEFT;
        }
    }
    else if (state == WALKING_LEFT) {
        positionX -= 100.0f * deltaTime;
        if (positionX <= 100.0f) {
            state = WALKING_RIGHT;
        }
    }

    // Update texture based on state
    updateTexture();

    // Update sprite position
    sprite.setPosition(glm::vec3(positionX, position.y, position.z));
    sprite.update();
}

void Character::draw() const {
    sprite.draw();
}

void Character::updateTexture() {
    if (state == IDLE) {
        if (animationTime >= 0.2f) { // Adjust frame rate as needed
            animationTime = 0.0f;
            currentFrame = (currentFrame + 1) % idleTextures.size();
            sprite.setTexture(idleTextures[currentFrame]);
        }
    }
    else {
        if (animationTime >= 0.1f) { // Adjust frame rate as needed
            animationTime = 0.0f;
            currentFrame = (currentFrame + 1) % walkTextures.size();
            sprite.setTexture(walkTextures[currentFrame]);
        }
    }
}

void Character::updatePosition(float deltaTime) {
    if (state == WALKING_RIGHT) {
        positionX += 100.0f * deltaTime; // Adjust speed as needed
        if (positionX >= 700.0f) {
            state = WALKING_LEFT;
        }
    }
    else if (state == WALKING_LEFT) {
        positionX -= 100.0f * deltaTime;
        if (positionX <= 100.0f) {
            state = WALKING_RIGHT;
        }
    }
}
