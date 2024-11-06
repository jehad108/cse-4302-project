#include <raylib.h>
#include <bits/stdc++.h>
#include "mainmenuspirit.hpp"
#include "button.hpp"
#include "sound.hpp"
#include "charactersprite.hpp"
using namespace std;

enum class GameScreen
{
    MainMenu,
    Game,
    GameOver
};

float playerSpeed = 3.0f;
Rectangle sourcerect = {96, 0, 64, 64};
Rectangle destrect = {500, 500, 128, 128};
Camera2D gamecamera;
int framcount = 0;
int playerframe = 0;
Rectangle sourcerectidle = {0, 0, 64, 64};

// Load all textures once
Texture idleTextureN, idleTextureS, idleTextureE, idleTextureW;
Texture walkTextureN, walkTextureS, walkTextureE, walkTextureW;
Texture mapTexture;

int main()
{
    GameScreen currentScreen = GameScreen::MainMenu;
    bool exit = false;
    const int windowWidth = GetScreenWidth();
    const int windowHeight = GetScreenHeight();

    InitWindow(windowWidth, windowHeight, "OOP Sprite Animation");
    ToggleFullscreen();

    // Load all textures once
    idleTextureN = LoadTexture("characters/gamecharacters/idle-n.png");
    idleTextureS = LoadTexture("characters/gamecharacters/idle-s.png");
    idleTextureE = LoadTexture("characters/gamecharacters/idle-se.png");
    idleTextureW = LoadTexture("characters/gamecharacters/idle-ne.png");

    walkTextureN = LoadTexture("characters/gamecharacters/walk-n.png");
    walkTextureS = LoadTexture("characters/gamecharacters/walk-s.png");
    walkTextureE = LoadTexture("characters/gamecharacters/walk.png");
    walkTextureW = LoadTexture("characters/gamecharacters/walk-ne.png");

    mapTexture = LoadTexture("characters/map/map_demo.png");

    SpriteAnimation menuBackground("images/new2.png", 38, 38.0f, {0, 0});
    InitAudioDevice();
    Button startButton{"buttons/start.png", {0, 500}, 0.65};
    Button exitButton{"buttons/exit.png", {0, 650}, 0.65};
    sound click("sounds/button.mp3");
    SetTargetFPS(60);

    Texture currentIdleTexture = idleTextureS;

    while (!WindowShouldClose() && exit == false)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentScreen == GameScreen::MainMenu)
        {
            menuBackground.Update();
            menuBackground.Draw();
            startButton.Draw();
            exitButton.Draw();
            if (startButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
            {
                click.playSound();
                currentScreen = GameScreen::Game;
            }
            if (exitButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
            {
                click.playSound();
                exit = true;
            }
        }
        else if (currentScreen == GameScreen::Game)
        {
            bool playerMoving = false;
            bool playermovingup = false, playermovingdown = false, playermovingleft = false, playermovingright = false;

            if (IsKeyDown(KEY_W))
            {
                playerMoving = playermovingup = true;
                destrect.y -= playerSpeed;
                currentIdleTexture = idleTextureN;
            }
            else if (IsKeyDown(KEY_S))
            {
                playerMoving = playermovingdown = true;
                destrect.y += playerSpeed;
                currentIdleTexture = idleTextureS;
            }
            else if (IsKeyDown(KEY_A))
            {
                playerMoving = playermovingleft = true;
                destrect.x -= playerSpeed;
                currentIdleTexture = idleTextureW;
            }
            else if (IsKeyDown(KEY_D))
            {
                playerMoving = playermovingright = true;
                destrect.x += playerSpeed;
                currentIdleTexture = idleTextureE;
            }

            if (IsKeyDown(KEY_M))
                currentScreen = GameScreen::MainMenu;

            gamecamera.target = {destrect.x + destrect.width / 2, destrect.y + destrect.height / 2};
            gamecamera.offset = {static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2)};
            gamecamera.rotation = 0.0f;
            gamecamera.zoom = 3.0f;

            BeginMode2D(gamecamera);
            DrawTexture(mapTexture, 200, 200, WHITE);

            if (playerMoving)
            {
                framcount++;
                if (framcount % 3 == 0)
                {
                    playerframe++;
                    if (playerframe > 8)
                        playerframe = 0;
                    sourcerect.x = 96 * playerframe;
                }
                if (playermovingup)
                    DrawTexturePro(walkTextureN, sourcerect, destrect, {destrect.width / 2, destrect.height / 2}, 0, WHITE);
                else if (playermovingdown)
                    DrawTexturePro(walkTextureS, sourcerect, destrect, {destrect.width / 2, destrect.height / 2}, 0, WHITE);
                else if (playermovingleft)
                    DrawTexturePro(walkTextureW, sourcerect, destrect, {destrect.width / 2, destrect.height / 2}, 0, WHITE);
                else if (playermovingright)
                    DrawTexturePro(walkTextureE, sourcerect, destrect, {destrect.width / 2, destrect.height / 2}, 0, WHITE);
            }
            else
            {
                framcount++;
                if (framcount % 4 == 0)
                {
                    playerframe++;
                    if (playerframe > 3)
                        playerframe = 0;
                    sourcerectidle.x = 96 * playerframe;
                }
                DrawTexturePro(currentIdleTexture, sourcerectidle, destrect, {destrect.width / 2, destrect.height / 2}, 0, WHITE);
            }

            EndMode2D();
        }

        EndDrawing();
    }

    // Unload textures when done
    UnloadTexture(idleTextureN);
    UnloadTexture(idleTextureS);
    UnloadTexture(idleTextureE);
    UnloadTexture(idleTextureW);
    UnloadTexture(walkTextureN);
    UnloadTexture(walkTextureS);
    UnloadTexture(walkTextureE);
    UnloadTexture(walkTextureW);
    UnloadTexture(mapTexture);

    CloseWindow();

    return 0;
}
