#include "raylib.h"

// Define Player struct
struct Player
{
    Rectangle rect;
    Vector2 speed; // x and y speed
    bool canJump;
};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "My 2D Platformer");
    SetTargetFPS(60);

    // Player initialization
    Player player;
    player.rect = { 100.0f, 300.0f, 30.0f, 30.0f }; // x, y, width, height
    player.speed = { 0.0f, 0.0f };
    player.canJump = false;

    // Physics constants
    const float gravity = 800.0f; // Pixels per second squared
    const float jumpSpeed = -400.0f; // Negative for upward movement
    const float moveSpeed = 200.0f; // Horizontal movement speed

    // Game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        float deltaTime = GetFrameTime(); // Time elapsed since last frame

        // Apply gravity
        player.speed.y += gravity * deltaTime;

        // Player horizontal movement
        if (IsKeyDown(KEY_LEFT))
        {
            player.speed.x = -moveSpeed;
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            player.speed.x = moveSpeed;
        }
        else
        {
            player.speed.x = 0; // Stop horizontal movement if no key pressed
        }

        // Player jump
        if (IsKeyPressed(KEY_SPACE) && player.canJump)
        {
            player.speed.y = jumpSpeed;
            player.canJump = false; // Prevent double jumping
        }

        // Update player position
        player.rect.x += player.speed.x * deltaTime;
        player.rect.y += player.speed.y * deltaTime;

        // Keep player within screen bounds (basic collision with bottom)
        if (player.rect.y + player.rect.height >= screenHeight)
        {
            player.rect.y = screenHeight - player.rect.height;
            player.speed.y = 0; // Stop vertical movement
            player.canJump = true; // Allow jumping again
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleRec(player.rect, BLUE); // Draw the player as a blue rectangle
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();
    return 0;
}