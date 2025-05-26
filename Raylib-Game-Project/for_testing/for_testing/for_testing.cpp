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
    //int highScore;
    //GameState state;
    int highScore;
    bool isNewHigh;
    bool hasHighScore; // to avoid showinf on first time
    int gameCount = 0;



public:

    enum GameState {
        MENU,
        PLAYING
    };

    GameState state;


    Game() : paddle(screenWidth, screenHeight), ball(screenWidth, screenHeight), score(0), highScore(0), hasHighScore(false), isNewHigh(false), state(MENU) {
        InitWindow(screenWidth, screenHeight, "2D Juggling Game for DSA Project");
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

        if (state == MENU && IsKeyPressed(KEY_ENTER)) {
            score = 0;
            isNewHigh = false;
            ball.Reset(screenWidth, screenHeight);
            state = PLAYING;
        }
        if (state == MENU) {
            if (IsKeyPressed(KEY_ENTER)) {
                state = PLAYING;
                score = 0;
                ball.Reset(screenWidth, screenHeight);
                
            }
        }
        else if (state == PLAYING) {
            paddle.Update(dt, screenWidth);
            ball.Update(dt);

            if (ball.CheckCollisionWithPaddle(paddle)) {
                ball.velocity.y *= -1;
                score++;

                if (score > highScore) {
                    highScore = score;
                    isNewHigh = true;
                    hasHighScore = true;
                }

            }


            if (ball.IsOutOfBounds(screenHeight)) {
                state = MENU;  // Go back to menu
                gameCount++;
            }
        }
    }


    void Draw() {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        


        if (state == MENU) {
            DrawText("JUGGLING GAME", screenWidth / 2 - 120, screenHeight / 2 - 60, 30, DARKGRAY);
            DrawText("Press [ENTER] to Start", screenWidth / 2 - 130, screenHeight / 2, 20, GRAY);
        }
        else if (state == PLAYING) {
            paddle.Draw();
            ball.Draw();
            // Draw current score
            DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);

            // Draw high score (changes color and size if it’s a new high)
            /*int highScoreFontSize = isNewHigh ? 30 : 20;
            Color highScoreColor = isNewHigh ? RED : DARKGRAY;*/
            if (hasHighScore && gameCount>0) {
                int highScoreFontSize = isNewHigh ? 30 : 20;
                Color highScoreColor = isNewHigh ? RED : DARKGRAY;
                DrawText(TextFormat("Highest Score: %d", highScore), 10, 40, highScoreFontSize, highScoreColor);
            }


            /*DrawText(TextFormat("High Score: %d", highScore), 10, 40, highScoreFontSize, highScoreColor);*/

        }

        EndDrawing();
    }

};

int main() {
    Game game;
    game.Run();
    return 0;
}
