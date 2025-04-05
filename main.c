#include <stdio.h>
#include <raylib.h>

static const int screenWidth = 800;
static const int screenHeight = 600;

typedef struct player
{
    Vector2 position;
    Vector2 size;
} player_t;

static player_t player = {0};

void DrawGame()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangle(player.position.x, player.position.y, player.size.x, player.size.y, BLACK);
    EndDrawing();
}

int main()
{
    player.position = (Vector2){screenWidth / 10, screenHeight * 7 / 8};
    player.size = (Vector2){40, 40};
    InitWindow(screenWidth, screenHeight, "Brick Breaker");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        DrawGame();
    }
    CloseWindow();
    return 0;
}
