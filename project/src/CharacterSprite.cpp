#include "CharacterSprite.hpp"

playersprite::playersprite(const char *imagePath, int totalFrames, float fps,Vector2 pos)
{
    spriteSheet = LoadTexture(imagePath);
    frameCount = totalFrames;
    frameTime = 1.0f / fps;
    elapsedTime = 0.0f;
    position = pos;
}

void playersprite::Update()
{
    elapsedTime += GetFrameTime();
    if (elapsedTime >= frameTime)
    {
        elapsedTime = 0.0f;
        currentFrame++;
        if (currentFrame > frameCount - 1)
            currentFrame = 0;
    }
    sourceRect.x = static_cast<float>(currentFrame) * static_cast<float>(spriteSheet.width / frameCount);
    sourceRect.y = 0;
    sourceRect.width = 64;
    sourceRect.height = 64;
}

void playersprite::Draw(Rectangle destrect)
{
    DrawTexturePro(spriteSheet, sourceRect, destrect, {destrect.width / 2, destrect.height / 2}, 0, WHITE);
}

void playersprite::Reset()
{
    currentFrame = 0;
    elapsedTime = 0.0f;
    sourceRect.x = 0;
}

playersprite::~playersprite()
{
    UnloadTexture(spriteSheet);
}
