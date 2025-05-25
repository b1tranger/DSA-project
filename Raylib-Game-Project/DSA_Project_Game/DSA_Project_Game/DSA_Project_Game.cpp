#include "raylib.h"

// Paddle Class
class Paddle {
public:
    float x, y;
    float width, height;
    float speed;

    Paddle(float screenWidth, float screenHeight) {
        width = 100;
        height = 20;
        x = screenWidth / 2 - width / 2;
        y = screenHeight - 50;
        speed = 500;
    }

    void Update(float dt, int screenWidth) {
        if (IsKeyDown(KEY_LEFT)) x -= speed * dt;
        if (IsKeyDown(KEY_RIGHT)) x += speed * dt;

        // Clamp
        if (x < 0) x = 0;
        if (x > screenWidth - width) x = screenWidth - width;
    }

    void Draw() {
        DrawRectangle((int)x, (int)y, (int)width, (int)height, DARKGRAY);
    }
};

// Ball Class
class Ball {
public:
    Vector2 position;
    Vector2 velocity;
    float radius;
    float gravity;

    Ball(float screenWidth, float screenHeight) {
        radius = 10;
        gravity = 400;
        Reset(screenWidth, screenHeight);
    }

    void Reset(float screenWidth, float screenHeight) {
        position = { screenWidth / 2.0f, screenHeight / 2.0f };
        velocity = { 200, 0 };
    }

    void Update(float dt) {
        velocity.y += gravity * dt;
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        if (position.x - radius <= 0) { //left overflow
            velocity.x *= -1;
            position.x = radius;
        }
        if (position.x + radius >= GetScreenWidth()) { // right overflow
            velocity.x *= -1;
            position.x = GetScreenWidth() - radius;

        }


    }

    void Draw() {
        DrawCircleV(position, radius, MAROON);
    }

    bool CheckCollisionWithPaddle(const Paddle& paddle) {
        return position.y + radius >= paddle.y &&
            position.x >= paddle.x &&
            position.x <= paddle.x + paddle.width &&
            velocity.y > 0;
    }

    bool IsOutOfBounds(int screenHeight) {
        return position.y - radius > screenHeight;
    }
};

// Game Class 
// Objects of Ball and Paddle decalred here
class Game {
private:
    const int screenWidth = 800;
    const int screenHeight = 600;
    Paddle paddle;
    Ball ball;
    int score;

public:
    Game() : paddle(screenWidth, screenHeight), ball(screenWidth, screenHeight), score(0) {
        InitWindow(screenWidth, screenHeight, "Juggling Game - OOP Version");
        SetTargetFPS(60);
    }

    ~Game() {
        CloseWindow();
    }

    void Run() {
        while (!WindowShouldClose()) {
            float dt = GetFrameTime();

            Update(dt);
            Draw();
        }
    }

    void Update(float dt) {
        paddle.Update(dt, screenWidth);
        ball.Update(dt);

        if (ball.CheckCollisionWithPaddle(paddle)) {
            ball.velocity.y *= -1;
            score++;
        }

        if (ball.IsOutOfBounds(screenHeight)) {
            ball.Reset(screenWidth, screenHeight);
            score = 0;
        }
    }

    void Draw() {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        paddle.Draw();
        ball.Draw();

        DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);

        EndDrawing();
    }
};

int main() {
    Game game;
    game.Run();
    return 0;
}
