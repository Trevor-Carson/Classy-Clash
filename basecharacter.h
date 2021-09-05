#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();                                 // Constructor BaseCharacter
    Vector2 getWorldPos() { return worldPos; }       // Gets the position in the world
    void undoMovement();                             // Function to undo last movement
    Rectangle GetCollisionRec();                     // Collision detection rectangle
    virtual void tick(float deltaTime);              // Tick function
    virtual Vector2 getScreenPos() = 0;              // Vector to hold current screen position
    bool getAlive() { return alive; }                // Getter method to check if currently alive
    void setAlive(bool isAlive) { alive = isAlive; } // Setter method to set if character is alive or dead

protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")}; // Holds the current texture the BaseCharacter is using
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};    // Holds the texture for the idle sprite sheet
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};      // Holds the texture for the run sprite sheet
    Vector2 screenPos{};                                                       // Position the BaseCharacter is drawn on the screen
    Vector2 worldPos{};                                                        // Position the BaseCharacter is in the world
    Vector2 worldPosLastFrame{};                                               // Holds the BaseCharacter last known map position
    float rightLeft{1.f};                                                      // Starts the BaseCharacter facing the right direction (1 : facing right, -1 : facing left)
    /// Animation variables
    float runningTime{};          // Amount of time the current frame has been drawn for
    int frame{};                  // Current frame of the sprite sheet
    int maxFrames{6};             // Max frames in the sprite sheet X-Axis
    float updateTime{1.f / 12.f}; // Cycle time per sprite sheet frame
    float speed{4.f};             // Movement speed multiplyer for the knight
    float width{};                // Width of a sprite in the spritesheet
    float height{};               // Height of the spritesheet
    float scale{4.f};             // Sets the scale of the BaseCharacter
    Vector2 velocity{};           // Contains information reguarding direction of movement and distance to move this frame

private:
    bool alive{true}; // Sets default for is character alive or dead
};

#endif