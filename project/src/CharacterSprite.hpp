// CharacterSprite.hpp

#ifndef CHARACTERSPRITE_HPP
#define CHARACTERSPRITE_HPP

#include <raylib.h>  // Include raylib for Vector2, Texture2D, etc.

class CharacterSprite {
private:
    Texture2D spriteSheet;     // Texture for the sprite sheet
    Rectangle sourceRect;      // Rectangle to define each frame of the sprite
    Rectangle destRect;        // Rectangle to define position and size on the screen
    Vector2 origin;            // Origin point for rotation
    int frameCount;            // Total number of frames in the sprite sheet
    int currentFrame;          // Current frame being displayed
    float frameTime;           // Time per frame (1/FPS)
    float elapsedTime;         // Time elapsed since last frame update

public:
    CharacterSprite(const char* imagePath, Rectangle srcRect, Rectangle dstRect, int totalFrames, float fps);
    ~CharacterSprite();

    void Update();              // Updates the animation frame
    void Draw();                // Draws the sprite with current frame and positioning
    void SetFPS(float fps);     // Allows changing FPS at runtime
    void SetPosition(Vector2 pos);     // Sets new position
    void SetDestinationSize(Vector2 size);  // Changes size of destination rectangle
};

#endif // CHARACTERSPRITE_HPP
