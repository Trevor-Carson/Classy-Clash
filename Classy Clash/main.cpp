/****************************************************************************************************
*** File Name:      main.cpp
*** Description:    Main C++ file for Classy Clash
*** Author:         Trevor Carson
*** Date:           2021-08-30
*****************************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "enemy.h"
#include <string>

int main()
{
    int const windowWidth{384};
    int const windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/world_map.png"); // Texture to hold the level map
    Vector2 mapPos{0.f, 0.f};                                    // Vector2 to store the maps starting position
    float const mapScale{4.f};                                   // Float used to scale the map size

    Character knight{windowWidth, windowHeight};

    // Array for map props
    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")},
    };

    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};
    goblin.setTarget(&knight);

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};
    goblin.setTarget(&knight);

    Enemy *enemies[]{
        &goblin,
        &slime};

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    // // Array for enemies
    // Enemy enemies[1]
    // {
    //     Enemy{Vector2{200.f, 200.f}, LoadTexture("characters\\goblin_idle_spritesheet.png"), LoadTexture("characters\\goblin_run_spritesheet.png")}
    // };

    /// Main game loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPos, 0.f, mapScale, WHITE);

        // Draw the props
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive()) // Character is not alive
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else // Character is alive
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.tick(GetFrameTime());
        // Check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // Check knight and prop collision
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.GetCollisionRec(knight.getWorldPos()), knight.GetCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->GetCollisionRec(), knight.GetCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        // // Check knight and enemy collision
        // for (auto enemy : enemies)
        // {
        //     if (CheckCollisionRecs(enemy.GetCollisionRec(), knight.GetCollisionRec()))
        //     {
        //         knight.undoMovement();
        //         enemy.undoMovement();
        //     }
        // }

        goblin.tick(GetFrameTime());

        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}
