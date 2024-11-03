#include "mainmenuspirit.hpp"

SpriteAnimation::SpriteAnimation(const char *imagePath, int totalFrames, float fps, Vector2 pos)
{
    // Load texture once in the constructor
    spriteSheet = LoadTexture(imagePath);
    frameCount = totalFrames;
    frameTime = 1.0f / fps;
    elapsedTime = 0.0f;
    currentFrame = 0;
    position = pos;

    // Define the source rectangle for the current frame
    sourceRect = {0, 0, (float)spriteSheet.width / frameCount, (float)spriteSheet.height};

    // Define the destination rectangle to stretch the spriteSheet to full screen
    destRect = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
}

SpriteAnimation::~SpriteAnimation()
{
    // Ensure texture is unloaded when the object is destroyed
    UnloadTexture(spriteSheet);
}

void SpriteAnimation::Update()
{
    elapsedTime += GetFrameTime();
    if (elapsedTime >= frameTime)
    {
        currentFrame = (currentFrame + 1) % frameCount;
        sourceRect.x = currentFrame * (float)spriteSheet.width / frameCount;
        elapsedTime = 0.0f;
    }
}

void SpriteAnimation::Draw()
{
    // Draw using the full-screen destRect
    DrawTexturePro(spriteSheet, sourceRect, destRect, (Vector2){0, 0}, 0.0f, WHITE);
}

void SpriteAnimation::SetFPS(float fps)
{
    frameTime = 1.0f / fps;
}
