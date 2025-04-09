#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include <raymath.h>

static const int screenWidth = 800;
static const int screenHeight = 600;

#define ROWS 5
#define BRICKS_PER_ROW 15

typedef struct ball
{
    bool is_active;
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
    bool active;
    Vector2 position;
} brick_t;

static player_t player = {0};
static ball_t ball = {0};
int hitTotal = 0;
Sound hitSound = {0};
static brick_t brick[ROWS][BRICKS_PER_ROW] = {0};
static Vector2 brick_size = {0};

void InitWin()
{
    InitWindow(screenWidth, screenHeight, "Brick Breaker");
    InitAudioDevice();
    SetTargetFPS(60);
}

void InitGame()
{
    hitSound = LoadSound("src/hit.wav");
    hitTotal = 0;

    brick_size = (Vector2){screenWidth / BRICKS_PER_ROW, 30};

    ball.is_active = false;
    ball.speed = (Vector2){4, 4};
    ball.radius = 10;
    ball.color = PURPLE;

    player.color = WHITE;
    player.size = (Vector2){80, 5};
    player.center = player.size.x / 2;
    player.position = (Vector2){screenWidth / 2 - player.center, screenHeight - 10};

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < BRICKS_PER_ROW; j++)
        {
            brick[i][j].position = (Vector2){j * brick_size.x + brick_size.x / 2, i * brick_size.y + 35};
            brick[i][j].active = true;
        }
    }
};

void DrawBricks()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < BRICKS_PER_ROW; j++)
        {
            if (brick[i][j].active == true)
            {
                if ((i + j) % 2 == 0)
                    DrawRectangle(brick[i][j].position.x - brick_size.x / 2, brick[i][j].position.y - brick_size.y / 2, brick_size.x, brick_size.y, PINK);
                else
                    DrawRectangle(brick[i][j].position.x - brick_size.x / 2, brick[i][j].position.y - brick_size.y / 2, brick_size.x, brick_size.y, BLUE);
            }
        }
    }
}

void UpdateGame()
{

    if (IsKeyDown(KEY_A) && player.position.x > 1)
        player.position.x -= 4;
    if (IsKeyDown(KEY_D) && player.position.x + player.size.x < screenWidth)
        player.position.x += 4;
    if (IsKeyDown(KEY_A) && player.position.x > 1 && IsKeyDown(KEY_LEFT_SHIFT))
        player.position.x -= 8;
    if (IsKeyDown(KEY_D) && player.position.x + player.size.x < screenWidth && IsKeyDown(KEY_LEFT_SHIFT))
        player.position.x += 8;
    if (IsKeyPressed(KEY_SPACE))
    {
        ball.is_active = true;
    }

    if (ball.is_active)
    {
        ball.position.y -= ball.speed.y;
        ball.position.x += ball.speed.x;

        if (ball.speed.y > 4)
            ball.speed.y -= 1;

        if (CheckCollisionCircleRec(ball.position, ball.radius, (Rectangle){player.position.x, player.position.y, player.size.x, player.size.y}))
        {
            hitTotal += 1;
            if (IsSoundPlaying)
                PlaySound(hitSound);
            ball.speed.y *= -2;
            ball.speed.x = (ball.position.x - (player.position.x + player.size.x / 2)) / (player.size.x / 2) * 2;
        }

        if (((ball.position.x + ball.radius) >= screenWidth) || ((ball.position.x - ball.radius) <= 0))
            ball.speed.x *= -1;

        if ((ball.position.y - ball.radius) <= 0)
            ball.speed.y *= -1;
        if ((ball.position.y + ball.radius) >= screenHeight || IsKeyPressed(KEY_R))
            InitGame();
    }
    else
    {
        ball.position = (Vector2){player.position.x + player.center, player.position.y - 20};
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < BRICKS_PER_ROW; j++)
        {
            if (brick[i][j].active && CheckCollisionCircleRec(ball.position, ball.radius, (Rectangle){brick[i][j].position.x, brick[i][j].position.y, brick_size.x, brick_size.y}))
            {

                brick[i][j].active = false;
                ball.speed.y *= -1;
            }
        }
    }

    DrawBricks();
}

void DrawGame()
{
    HideCursor();
    BeginDrawing();
    ClearBackground(GRAY);
    DrawRectangle(player.position.x - 2, player.position.y - 2, player.size.x, player.size.y, BLACK);
    DrawRectangle(player.position.x, player.position.y, player.size.x, player.size.y, player.color);
    DrawCircle(ball.position.x - 1, ball.position.y, ball.radius + 2, BLACK);
    DrawCircle(ball.position.x, ball.position.y, ball.radius, ball.color);
    UpdateGame();

    // DrawText(TextFormat("Total Hits: %02i", hitTotal), screenWidth / 40, screenHeight / 40, 30, BLACK);
    EndDrawing();
}

int main()
{
    InitWin();
    InitGame();
    while (!WindowShouldClose())
    {
        DrawGame();
    }
    CloseWindow();
    return 0;
}
