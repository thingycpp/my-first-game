#pragma once

#include "Textures.h"

#define G 2000
#define GROUND_SPD 800
#define JUMP_SPD 1000
#define DASH_SPD 1200

typedef struct Player
{
      Vector2 pos;
      float vel;
      bool canJump;
      bool canDash;

      void HandleMovement(Player *player, float delta, TextureHandler *texHandler);
} Player;