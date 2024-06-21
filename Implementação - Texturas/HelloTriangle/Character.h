#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include "Sprite.h"

class Character {
public:
    Character(Shader& shader, const std::vector<GLuint>& walkTextures, glm::vec3 position);

    void update(float deltaTime);
    void draw() const;

private:
    enum State { IDLE, WALKING_RIGHT, WALKING_LEFT } state;
    float animationTime;
    float positionX;
    glm::vec3 position;

    Sprite sprite;
    std::vector<GLuint> idleTextures;
    std::vector<GLuint> walkTextures;
    size_t currentFrame;

    void updateTexture();
    void updatePosition(float deltaTime);
};

#endif
