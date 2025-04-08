#include <stdio.h>
#include <raylib.h>

static const int screenWidth = 800;
static const int screenHeight = 600;

typedef struct ball
{
    bool is_active;
    Vector2 size;
    Vector2 position;
    Vector2 speed;
    Color color;
    int radius;
} ball_t;

typedef struct player
{
    Vector2 position;
    Vector2 size;
    int center;
    Color color;
    Vector4 edges;
} player_t;

typedef struct brick
{
    Vector2 position;
    Vector2 size;
    Color color;
} brick_t;

static brick_t brick = {0};
static player_t player = {0};
static ball_t ball = {0};

void InitGame()
{
    brick.size = (Vector2){16, 30};

    ball.is_active = false;
    ball.speed = (Vector2){2, 2};
    ball.size = (Vector2){10, 10};
    ball.radius = 10;
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
    if (IsKeyPressed(KEY_SPACE))
    {
        ball.is_active = true;
    }

    if (ball.is_active)
    {
        ball.position.x += ball.speed.x;
        ball.position.y -= ball.speed.y;

        if (((ball.position.x + ball.radius) >= screenWidth) || ((ball.position.x - ball.radius) <= 0))
            ball.speed.x *= -1;
        if ((ball.position.y - ball.radius) <= 0)
            ball.speed.y *= -1;

        if (IsKeyDown(KEY_A) && player.position.x > 1)
            player.position.x -= 4;
        if (IsKeyDown(KEY_D) && player.position.x + player.size.x < screenWidth)
            player.position.x += 4;
        if (IsKeyDown(KEY_A) && player.position.x > 1 && IsKeyDown(KEY_LEFT_SHIFT))
            player.position.x -= 4 * 2;
        if (IsKeyDown(KEY_D) && player.position.x + player.size.x < screenWidth && IsKeyDown(KEY_LEFT_SHIFT))
            player.position.x += 4 * 2;
    }
    else
    {
        ball.position = (Vector2){player.position.x + 10, player.position.y - 20};
    }
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
