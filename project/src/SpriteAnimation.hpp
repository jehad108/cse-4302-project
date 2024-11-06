#pragma once
#include <raylib.h>
#include <string>

using namespace std;

class SpriteAnimation {
private:
    Texture2D texture;
    int frameCount;
    int currentFrame;
    int frameSpeed;
    Rectangle sourceRect;
    Vector2 position;

public:
    SpriteAnimation(const string& textureFile, int frames, float speed, Vector2 startPosition)
        : frameCount(frames), currentFrame(0), frameSpeed(static_cast<int>(speed)), position(startPosition) {
        texture = LoadTexture(textureFile.c_str());
        sourceRect = {0, 0, static_cast<float>(texture.width) / frameCount, static_cast<float>(texture.height)};
    }

    void Update() {
        currentFrame = (currentFrame + 1) % frameCount;
        sourceRect.x = currentFrame * sourceRect.width;
    }

    void Draw() const {
        DrawTextureRec(texture, sourceRect, position, WHITE);
    }

    ~SpriteAnimation() {
        UnloadTexture(texture);
    }
};