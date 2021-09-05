#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);             // Consctuctor for map location and texture
    void Render(Vector2 knightPos);               // Calculates the distance from character
    Rectangle GetCollisionRec(Vector2 knightPos); // Collision detection rectangle for props

private:
    Vector2 worldPos{};  // Sets the map position of the prop
    Texture2D texture{}; // Sets the texture of the prop
    float scale{4.f};    // Sets the scale of the prop
};
