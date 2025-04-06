#include <stdio.h>
#include <raylib.h>

static const int screenWidth = 800;
static const int screenHeight = 600;

typedef struct ball
{
    Vector2 size;
    Vector2 position;
    Color color;
} ball_t;

typedef struct player
{
    Vector2 position;
    Vector2 size;
    int center;
    Color color;
} player_t;

typedef struct brick
{
    Vector2 position;
    Vector2 size;
    Color color;
} brick_t;

static player_t player = {0};
static ball_t ball = {0};

void InitGame()
{
    ball.position = (Vector2){screenWidth / 2, screenHeight / 2};
    ball.size = (Vector2){10, 10};
    ball.color = RED;
    player.color = BLACK;
    player.size = (Vector2){40, 15};
    player.center = player.size.x / 2;
    player.position = (Vector2){screenWidth / 2 - player.center, 500};
    InitWindow(screenWidth, screenHeight, "Brick Breaker");
    SetTargetFPS(60);
}

void UpdateGame()
{
    // int key_pressed = GetKeyPressed();
    // int key_held = IsKeyDown(key_pressed);
    // switch (key_pressed)
    // {
    // case KEY_A:
    //     if (player.position.x > 1)
    //     {
    //         player.position.x -= 4;
    //     }
    // case KEY_D:
    //     if (player.position.x + player.size.x < screenWidth)
    //     {
    //         player.position.x += 4;
    //     }
    // default:
    //     break;
    // }

    if (IsKeyDown(KEY_A) && player.position.x > 1)
        player.position.x -= 4;
    if (IsKeyDown(KEY_D) && player.position.x + player.size.x < screenWidth)
        player.position.x += 4;
    if (IsKeyDown(KEY_A) && player.position.x > 1 && IsKeyDown(KEY_LEFT_SHIFT))
        player.position.x -= 8;
    if (IsKeyDown(KEY_D) && player.position.x + player.size.x < screenWidth && IsKeyDown(KEY_LEFT_SHIFT))
        player.position.x += 8;
}

void DrawGame()
{
    HideCursor();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangle(player.position.x, player.position.y, player.size.x, player.size.y, player.color);
    DrawRectangle(ball.position.x, ball.position.y, ball.size.x, ball.size.y, ball.color);
    UpdateGame();
    EndDrawing();
}

int main()
{
    InitGame();
    while (!WindowShouldClose())
    {
        DrawGame();
    }
    CloseWindow();
    return 0;
}
