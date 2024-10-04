#include <raylib.h>

class SpriteAnimation
{
private:
    Texture2D spriteSheet;
    Rectangle sourceRect;
    Vector2 position;
    int frameCount;
    int currentFrame;
    float frameTime;
    float elapsedTime;

public:
    // Constructor
    SpriteAnimation(const char* imagePath, int totalFrames, float fps, Vector2 pos)
    {
        spriteSheet = LoadTexture(imagePath);
        frameCount = totalFrames;
        frameTime = 1.0f / fps;
        elapsedTime = 0.0f;
        currentFrame = 0;
        position = pos;
        sourceRect = {0, 0, (float)spriteSheet.width / frameCount, (float)spriteSheet.height};
    }

    // Destructor to unload the texture
    ~SpriteAnimation()
    {
        UnloadTexture(spriteSheet);
    }

    // Update method to handle frame switching
    void Update()
    {
        elapsedTime += GetFrameTime();
        if (elapsedTime >= frameTime)
        {
            currentFrame = (currentFrame + 1) % frameCount;
            sourceRect.x = currentFrame * (float)spriteSheet.width / frameCount;
            elapsedTime = 0.0f;
        }
    }

    // Draw method to render the current frame
    void Draw()
    {
        DrawTextureRec(spriteSheet, sourceRect, position, WHITE);
    }

    // Method to change the FPS dynamically
    void SetFPS(float fps)
    {
        frameTime = 1.0f / fps;
    }
};

int main()
{
    const int windowWidth = GetScreenWidth();
    const int windowHeight = GetScreenHeight();

    InitWindow(windowWidth, windowHeight, "OOP Sprite Animation");
    ToggleFullscreen();

    SpriteAnimation menuBackground("images/menu.png", 8, 45.0f, {0, 0});

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        menuBackground.Update();

        BeginDrawing();
        ClearBackground(WHITE);
        menuBackground.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

