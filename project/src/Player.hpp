

#pragma once
#include <raylib.h>
#include <string>
#include "SpriteAnimation.hpp"

using namespace std;

class Player {
private:
    SpriteAnimation walkNorth, walkSouth, walkEast, walkWest;
    SpriteAnimation idleNorth, idleSouth, idleEast, idleWest;
    Vector2 position;
    float speed;
    SpriteAnimation* currentAnimation;

public:
    Player(const string& idleN, const string& idleS, const string& idleE, const string& idleW,
           const string& walkN, const string& walkS, const string& walkE, const string& walkW,
           Vector2 startPosition, float playerSpeed)
        : idleNorth(idleN, 4, 4.0f, startPosition), idleSouth(idleS, 4, 4.0f, startPosition),
          idleEast(idleE, 4, 4.0f, startPosition), idleWest(idleW, 4, 4.0f, startPosition),
          walkNorth(walkN, 8, 8.0f, startPosition), walkSouth(walkS, 8, 8.0f, startPosition),
          walkEast(walkE, 8, 8.0f, startPosition), walkWest(walkW, 8, 8.0f, startPosition),
          position(startPosition), speed(playerSpeed), currentAnimation(&idleSouth) {}

    void Update() {
        bool isMoving = false;
        if (IsKeyDown(KEY_W)) {
            position.y -= speed;
            currentAnimation = &walkNorth;
            isMoving = true;
        } else if (IsKeyDown(KEY_S)) {
            position.y += speed;
            currentAnimation = &walkSouth;
            isMoving = true;
        } else if (IsKeyDown(KEY_A)) {
            position.x -= speed;
            currentAnimation = &walkWest;
            isMoving = true;
        } else if (IsKeyDown(KEY_D)) {
            position.x += speed;
            currentAnimation = &walkEast;
            isMoving = true;
        }

        if (!isMoving) {
            if (currentAnimation == &walkNorth) currentAnimation = &idleNorth;
            else if (currentAnimation == &walkSouth) currentAnimation = &idleSouth;
            else if (currentAnimation == &walkEast) currentAnimation = &idleEast;
            else if (currentAnimation == &walkWest) currentAnimation = &idleWest;
        }

        currentAnimation->Update();
    }

    void Draw() const {
        currentAnimation->Draw();
    }

    Vector2 GetPosition() const {
        return position;
    }
};
