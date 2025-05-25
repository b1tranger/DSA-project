#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Juggling Game");
    SetTargetFPS(60);

    // Paddle
    float paddleWidth = 100;
    float paddleHeight = 20;
    float paddleX = screenWidth / 2 - paddleWidth / 2;
    float paddleY = screenHeight - 50;
    float paddleSpeed = 500;

    // Ball
    Vector2 ballPos = { screenWidth / 2.0f, screenHeight / 2.0f };
    Vector2 ballVel = { 200, 0 };
    float ballRadius = 10;
    float gravity = 400;

    int score = 0;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Paddle Movement
        if (IsKeyDown(KEY_LEFT)) paddleX -= paddleSpeed * dt;
        if (IsKeyDown(KEY_RIGHT)) paddleX += paddleSpeed * dt;

        // Clamp paddle
        if (paddleX < 0) paddleX = 0;
        if (paddleX > screenWidth - paddleWidth) paddleX = screenWidth - paddleWidth;

        // Ball physics
        ballVel.y += gravity * dt;
        ballPos.x += ballVel.x * dt;
        ballPos.y += ballVel.y * dt;

        // Ball collision with paddle
        if (ballPos.y + ballRadius >= paddleY &&
            ballPos.x >= paddleX && ballPos.x <= paddleX + paddleWidth &&
            ballVel.y > 0) {
            ballVel.y *= -1;
            score++;
        }

        // Ball falls below screen
        if (ballPos.y - ballRadius > screenHeight) {
            // Reset
            ballPos = { screenWidth / 2.0f, screenHeight / 2.0f };
            ballVel = { 200, 0 };
            score = 0;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(paddleX, paddleY, paddleWidth, paddleHeight, DARKGRAY);
        DrawCircleV(ballPos, ballRadius, MAROON);

        DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
