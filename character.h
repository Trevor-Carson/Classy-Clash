#ifndef CHARACTER_H
#define CHARACTER_H

#include "basecharacter.h"
#include "raylib.h"

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);      // Constructor for character class has inputs for screen map position
    virtual void tick(float deltaTime) override; // Tick function
    virtual Vector2 getScreenPos() override;     // Return the current screen position of the character
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
    float getHealth() const { return health; }
    void takeDamage(float damage);

private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100.f};
};

#endif
