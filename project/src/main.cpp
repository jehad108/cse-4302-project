#include <raylib.h>
#include"mainmenuspirit.hpp"
int main()
{
    const int windowWidth = GetScreenWidth();
    const int windowHeight = GetScreenHeight();

    InitWindow(windowWidth, windowHeight, "OOP Sprite Animation");
    ToggleFullscreen();

    SpriteAnimation menuBackground("images/new2.png",38, 38.0f, {0, 0});

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
