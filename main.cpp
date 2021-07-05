#include "Player.h"

bool inGame = false;

typedef struct FireballEnemy {
    Vector2 pos;
    float vel;
    bool isExploaded;

    void HandleFireball(float delta, TextureHandler* texHandler);
} FireballEnemy;

void Game(Player *_player, FireballEnemy *_fireEnemy, float _delta, TextureHandler *_texHandler);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Green Dude");

    TextureHandler texHandler = {0};
    texHandler.playerIdle = LoadTexture("Assets/GD_idle.png");
    texHandler.playerRight = LoadTexture("Assets/GD_right.png");
    //Took the grass texture from codergopher's SDL2 tutorial, find him on YT at https://www.youtube.com/channel/UCfiC4q3AahU4Io-s83-CIbQ, hes a pretty cool dude.
    texHandler.grass = LoadTexture("Assets/grass.png");
    texHandler.playerTex = texHandler.playerIdle;

    FireballEnemy fireEnem = { 0 };
    fireEnem.isExploaded = false;
    fireEnem.pos = { 2000, 2000 };
    fireEnem.vel = 0.0f;

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
        
        Rectangle playBox = { screenWidth / 2-50, screenHeight / 2-50, 100, 35 };
        DrawRectangleRec(playBox, GREEN);
        int mouseX_overPlay = GetMouseX();
        int mouseY_overPlay = GetMouseY();

        if (mouseX_overPlay <= screenWidth / 2 + 50 && mouseX_overPlay >= screenWidth / 2 && mouseY_overPlay <= screenHeight / 2 + 35 && mouseY_overPlay >= screenHeight / 2 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            inGame = true;
            
        }

        if (inGame) {

            Game(&player, &fireEnem, deltaTime, &texHandler);

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

void FireballEnemy::HandleFireball(float delta, TextureHandler* texHandler)
{
    // fireball code
}

void Player::HandleMovement(Player* player, float delta, TextureHandler* texHandler)
{
    if (IsKeyDown(KEY_A)) {
        player->pos.x -= GROUND_SPD * delta;
        texHandler->playerTex = texHandler->playerIdle;
    }

    if (IsKeyDown(KEY_D)) {
        player->pos.x += GROUND_SPD * delta;
        texHandler->playerTex = texHandler->playerRight;
    }

    if (IsKeyDown(KEY_SPACE) && player->canJump)
    {
        player->vel = -JUMP_SPD;
        player->canJump = false;
    }

    if (IsKeyDown(KEY_D) && IsMouseButtonDown(MOUSE_MIDDLE_BUTTON) && player->canDash)
    {
        player->pos.x += DASH_SPD * delta;
        texHandler->playerTex = texHandler->playerRight;
        player->canDash = false;
    }

    if (IsKeyDown(KEY_A) && IsMouseButtonDown(MOUSE_MIDDLE_BUTTON) && player->canDash)
    {
        player->pos.x -= DASH_SPD * delta;
        texHandler->playerTex = texHandler->playerIdle;
        player->canDash = false;
    }

    int onFloor = 0;
    if (player->pos.y == 400)
    {
        onFloor = 1;
        player->vel = 0.0f;
        player->pos.y = 430;
    }

    if (!onFloor) {
        player->pos.y += player->vel * delta;
        player->vel += G * delta;
        player->canJump = false;
    }
    else {
        player->canJump = false;
        player->canDash = false;
    }

    Vector2 playerTexPos = { player->pos.x, player->pos.y };
    DrawTextureEx(texHandler->playerTex, playerTexPos, 0.0f, 40, WHITE);
}

void Game(Player* _player, FireballEnemy* _fireEnemy, float _delta, TextureHandler* _texHandler)
{
    // Game Shenanigans
    ClearBackground(RAYWHITE);


    _player->HandleMovement(_player, _delta, _texHandler);
    _fireEnemy->HandleFireball(_delta, _texHandler);
}
