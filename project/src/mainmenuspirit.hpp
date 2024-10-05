#pragma once
#include <raylib.h>
class SpriteAnimation
{
private:
    Texture2D spriteSheet;
    Rectangle sourceRect;
    Rectangle destRect;    
    Vector2 position;
    int frameCount;
    int currentFrame;
    float frameTime;
    float elapsedTime;
    public:
    SpriteAnimation(const char* imagePath, int totalFrames, float fps, Vector2 pos);
    ~SpriteAnimation();
    void Update();
    void Draw();
    void SetFPS(float fps);
};
class button
{
private:
    Texture2D texture;
    Vector2 position;
public:
    button(const char *p, Vector2 iamgeposition);
    void draw();
    ~button();
};
