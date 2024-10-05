#include "mainmenuspirit.hpp"
#include <bits/stdc++.h>
using namespace std;
SpriteAnimation ::SpriteAnimation(const char *imagePath, int totalFrames, float fps, Vector2 pos)
{
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
    UnloadTexture(spriteSheet);
}
void SpriteAnimation ::Update()
{
    elapsedTime += GetFrameTime();
    if (elapsedTime >= frameTime)
    {
        currentFrame = (currentFrame + 1) % frameCount;
        sourceRect.x = currentFrame * (float)spriteSheet.width / frameCount;
        elapsedTime = 0.0f;
    }
}
void SpriteAnimation ::Draw()
{
    DrawTexturePro(spriteSheet, sourceRect, destRect, (Vector2){0, 0}, 0.0f, WHITE);
}
void SpriteAnimation ::SetFPS(float fps)
{
    frameTime = 1.0f / fps;
}
button::button(const char *p, Vector2 imageposition)
{
    texture = LoadTexture(p);
    position = imageposition;
}

void button::draw()
{
    DrawTextureV(texture, position, WHITE);
}

button::~button()
{
    UnloadTexture(texture);
}