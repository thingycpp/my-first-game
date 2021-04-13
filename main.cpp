#include <iostream>
using namespace std;

#include "include/raylib.h"

typedef struct TextureHandler {
	Texture2D p_currentTex;
    Texture2D playerIdle;
    Texture2D playerRight;

    Texture2D grass;
} TextureHandler;

#define G 2000
#define GROUND_SPD 800
#define JUMP_SPD 1000
#define DASH_SPD 1200

typedef struct Player {
    Vector2 pos;
    float vel;
    bool canJump;
    bool canDash;

    void HandleMovement(Player* player, float delta, TextureHandler* texHandler, Texture2D playerTex);
} Player;


void Game(Player* player, float delta, TextureHandler* texHandler);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Green Dude");

    TextureHandler texHandler = { 0 };
    texHandler.playerIdle = LoadTexture("Assets/GD_idle.png");
    texHandler.playerRight = LoadTexture("Assets/GD_right.png");
    //Took the grass texture from codergopher's SDL2 tutorial, find him on YT at https://www.youtube.com/channel/UCfiC4q3AahU4Io-s83-CIbQ, hes a pretty cool dude.
    texHandler.grass = LoadTexture("Assets/grass.png");

    Player player = { 0 };
    player.canDash = true;
    player.canJump = false;
    player.pos = { screenWidth / 2, screenHeight / 2 };
    player.vel = 0.0f;



    SetTargetFPS(60);
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
        DrawRectangleRec(playBox, RED);
        int mouseX_overPlay = GetMouseX();
        int mouseY_overPlay = GetMouseY();
        if (mouseX_overPlay <= screenWidth / 2 + 40 && mouseX_overPlay >= screenWidth / 2 - 40 && mouseY_overPlay <= screenHeight / 2 + 20 && mouseY_overPlay >= screenHeight / 2 - 20 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Game(&player, deltaTime, &texHandler);
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

void Player::HandleMovement(Player* player, float delta, TextureHandler* texHandler)
{
    if (IsKeyDown(KEY_A)) {
        player->pos.x -= GROUND_SPD * delta;
        texHandler->p_currentTex = texHandler->playerIdle;
    }

    if (IsKeyDown(KEY_D)) {
        player->pos.x += GROUND_SPD * delta;
        texHandler->p_currentTex = texHandler->playerRight;
    }

    if (IsKeyDown(KEY_SPACE) && player->canJump)
    {
        player->vel = -JUMP_SPD;
        player->canJump = false;
    }

    if (IsKeyDown(KEY_D) && IsMouseButtonDown(MOUSE_MIDDLE_BUTTON) && player->canDash)
    {
        player->pos.x += DASH_SPD * delta;
        texHandler->p_currentTex = texHandler->playerRight;
        player->canDash = false;
    }

    if (IsKeyDown(KEY_A) && IsMouseButtonDown(MOUSE_MIDDLE_BUTTON) && player->canDash)
    {
        player->pos.x -= DASH_SPD * delta;
        texHandler->p_currentTex = texHandler->playerIdle;
        player->canDash = false;
    }

    int hit = 0;
    if (player->pos.y == 450)
    {
        hit = 1;
        player->vel = 0.0f;
        player->pos.y = 450;
    }

    if (!hit) {
        player->pos.y += player->vel * delta;
        player->vel += G * delta;
        player->canJump = false;
    }
    else {
        player->canJump = false;
        player->canDash = false;
    }

    Vector2 playerTexPos = { player->pos.x, player->pos.y };
    DrawTextureEx(texHandler->p_currentTex, playerTexPos, 0.0f, 40, WHITE);
}

void Game(Player* _player, float _delta, TextureHandler* _texHandler)
{
    // Game Shenanigans
    ClearBackground(RAYWHITE);

    _player->HandleMovement(_player, _delta, _texHandler);
}