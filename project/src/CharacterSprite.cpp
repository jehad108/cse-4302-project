// CharacterSprite.cpp

#include "CharacterSprite.hpp"

// Constructor to initialize all parameters
CharacterSprite::CharacterSprite(const char* imagePath, Rectangle srcRect, Rectangle dstRect, int totalFrames, float fps)
    : sourceRect(srcRect), destRect(dstRect), frameCount(totalFrames), currentFrame(0), elapsedTime(0.0f) {
    spriteSheet = LoadTexture(imagePath);    // Load the sprite sheet
    frameTime = 1.0f / fps;                  // Calculate time per frame based on FPS

    // Set the origin to the center of the destination rectangle for rotation
    origin = { destRect.width / 2, destRect.height / 2 };
}

// Destructor to unload the texture when the object is destroyed
CharacterSprite::~CharacterSprite() {
    UnloadTexture(spriteSheet);
}

// Updates the animation frame based on elapsed time
void CharacterSprite::Update() {
    elapsedTime += GetFrameTime();
    if (elapsedTime >= frameTime) {
        currentFrame = (currentFrame + 1) % frameCount;  // Move to next frame, loop back if needed
        sourceRect.x = currentFrame * sourceRect.width;  // Update sourceRect to select next frame
        elapsedTime = 0.0f;  // Reset elapsed time
    }
}

// Draws the current frame of the sprite at the destination rectangle
void CharacterSprite::Draw() {
    DrawTexturePro(
        spriteSheet,
        sourceRect,           // Source rectangle (current frame)
        destRect,             // Destination rectangle on the screen
        origin,               // Rotate around the center
        0.0f,                 // No rotation (modify as needed)
        WHITE                 // No tint
    );
}

// Sets a new frame rate (FPS) and recalculates frame time
void CharacterSprite::SetFPS(float fps) {
    frameTime = 1.0f / fps;
}

// Sets a new position by updating the destination rectangle
void CharacterSprite::SetPosition(Vector2 pos) {
    destRect.x = pos.x;
    destRect.y = pos.y;
}

// Changes the size of the destination rectangle, allowing the sprite to scale
void CharacterSprite::SetDestinationSize(Vector2 size) {
    destRect.width = size.x;
    destRect.height = size.y;
}
