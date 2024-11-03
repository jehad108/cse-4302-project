#include <raylib.h>
#include <bits/stdc++.h>
#include "mainmenuspirit.hpp"
#include "button.hpp"
#include "sound.hpp"
using namespace std;
int main()
{
    bool exit = false;
    const int windowWidth = GetScreenWidth();
    const int windowHeight = GetScreenHeight();

    InitWindow(windowWidth, windowHeight, "OOP Sprite Animation");
    ToggleFullscreen();

    SpriteAnimation menuBackground("images/new2.png", 38, 38.0f, {0, 0});
    InitAudioDevice();
     Button startButton{"buttons/start.png", {0, 500}, 0.65};
    Button exitButton{"buttons/exit.png", {0, 650}, 0.65};
    sound click("sounds/button.mp3");
    SetTargetFPS(60);

    while (!WindowShouldClose() && exit == false)
    {
        menuBackground.Update();
        BeginDrawing();
        ClearBackground(WHITE);
        menuBackground.Draw();
        startButton.Draw();
        exitButton.Draw();
        if (exitButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
        {
            exitButton.stopSound();
            click.playSound();
            exit = true;
        }
        EndDrawing();
    }
    CloseWindow();

    return 0;
}