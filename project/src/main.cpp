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

    // idleTextureN = LoadTexture("characters/gamecharacters/idle-n.png");
    playersprite idleSpriteS("characters/gamecharacters/idle-S.png", 4, 20.0f, {0, 0});
    playersprite idleSpriteE("characters/gamecharacters/idle-se.png", 4, 20.0f, {0, 0});
    playersprite idleSpriteW("characters/gamecharacters/idle-ne.png", 4, 20.0f, {0, 0});
    playersprite idleSpriteN("characters/gamecharacters/idle-n.png", 4, 20.0f, {0, 0});
    playersprite walkSpriteN("characters/gamecharacters/walk-n.png", 8, 30.0f, {0, 0});
    playersprite walkSpriteS("characters/gamecharacters/walk-s.png", 8, 30.0f, {0, 0});
    playersprite walkSpriteE("characters/gamecharacters/walk.png", 8, 30.0f, {0, 0});
    playersprite walkSpriteW("characters/gamecharacters/walk-ne.png", 8, 30.0f, {0, 0});

    mapTexture = LoadTexture("characters/map/map_demo.png");

    SpriteAnimation menuBackground("images/new2.png", 38, 38.0f, {0, 0});
    InitAudioDevice();
    Button startButton{"buttons/start.png", {0, 500}, 0.65};
    Button exitButton{"buttons/exit.png", {0, 650}, 0.65};
    sound click("sounds/button.mp3");
    SetTargetFPS(60);

    playersprite currentIdleSprite = idleSpriteS;

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
                currentIdleSprite = idleSpriteN;
                currentIdleSprite.Reset();
            }
            else if (IsKeyDown(KEY_S))
            {
                playerMoving = playermovingdown = true;
                destrect.y += playerSpeed;
                currentIdleSprite = idleSpriteS;
                currentIdleSprite.Reset();
            }
            else if (IsKeyDown(KEY_A))
            {
                playerMoving = playermovingleft = true;
                destrect.x -= playerSpeed;
                currentIdleSprite = idleSpriteW;
                currentIdleSprite.Reset();
            }
            else if (IsKeyDown(KEY_D))
            {
                playerMoving = playermovingright = true;
                destrect.x += playerSpeed;
                currentIdleSprite = idleSpriteE;
                currentIdleSprite.Reset();
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
                if (playermovingup)
                {
                    walkSpriteN.Update();
                    walkSpriteN.Draw(destrect);
                }
                else if (playermovingdown)
                {
                    walkSpriteS.Update();
                    walkSpriteS.Draw(destrect);
                }
                else if (playermovingleft)
                {
                    walkSpriteW.Update();
                    walkSpriteW.Draw(destrect);
                }
                else if (playermovingright)
                {
                    walkSpriteE.Update();
                    walkSpriteE.Draw(destrect);
                }
            }
            else
            {
                currentIdleSprite.Update();
                currentIdleSprite.Draw(destrect);
            }

            EndMode2D();
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
