#include "basecharacter.h"
#include "raylib.h"
#include "character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture); // Constructor for enemy class has inputs for screen map position
    virtual void tick(float deltaTime) override;                     // Tick function
    void setTarget(Character *character) { target = character; }
    virtual Vector2 getScreenPos() override;

private:
    Character *target;
    float damagePerSec{10.f};
    float radius{25.f};
};
