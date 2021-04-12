#include <iostream>
using namespace std;

#include "include/raylib.h"

#define G 2000
#define GROUND_SPD 800
#define JUMP_SPD 1000
#define DASH_SPD 1200

typedef struct Player {
    Vector2 pos;
    float vel;
    bool canJump;
    bool canDash;
} Player;

typedef struct Collidable {
    Rectangle rec;
    int blocking;
    Color color;
} Collidable;


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Green Dude");

    Player player = { 0 };
    player.canDash = true;
    player.canJump = false;
    player.pos = { screenWidth / 2, screenHeight / 2 };
    player.vel = 0.0f;

    SetTargetFPS(GetMonitorRefreshRate());
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        float deltaTime = GetFrameTime();


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(GRAY);
        
        Rectangle playBox = { screenWidth / 2, screenHeight / 2, 80, 40 };
        DrawRectangle(playBox.x, playBox.y, playBox.width, playBox.height, RED);
        int mouseX_overPlay = GetMouseX();
        int mouseY_overPlay = GetMouseY();
        if (mouseX_overPlay <= screenWidth / 2 + 40 && mouseX_overPlay >= screenWidth / 2 - 40 && mouseY_overPlay <= screenHeight / 2 + 20 && mouseY_overPlay >= screenHeight / 2 - 20 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Game(&player, deltaTime);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void Game(Player* player, float delta)
{
    // Game Shenanigans
    ClearBackground(RAYWHITE);
    Rectangle playerRec = { player->pos.x, player->pos.y, 40, 40 };
    DrawRectangleRec(playerRec, GREEN);

    if (IsKeyDown(KEY_A)) player->pos.x -= GROUND_SPD * delta;
    if (IsKeyDown(KEY_D)) player->pos.x += GROUND_SPD * delta;

    if (IsKeyDown(KEY_SPACE) && player->canJump)
    {
        player->vel = -JUMP_SPD;
        player->canJump = false;
    }

    if (IsKeyDown(KEY_D) && IsKeyDown(KEY_F) && player->canDash)
    {
        player->pos.x += DASH_SPD*delta;
        player->canDash = false;
    }

}