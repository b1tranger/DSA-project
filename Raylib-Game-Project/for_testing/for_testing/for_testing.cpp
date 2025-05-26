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

    void Draw(int level) {
        if (level == 1) {
            DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8,0, DARKBLUE);
            //DrawRectangle((int)x, (int)y, (int)width, (int)height, SKYBLUE);
        }
        else if (level == 2) {
            DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, DARKGRAY);
            //DrawRectangle((int)x, (int)y, (int)width, (int)height, DARKGRAY);
        }
        else if (level == 3) {
            DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, YELLOW);
            //DrawRectangle((int)x, (int)y, (int)width, (int)height, YELLOW);
        }
        
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

    void Draw(int level) {

        if (level == 1) {
            DrawCircleV(position, radius, BLACK);
        }
        else if (level == 2) {
            DrawCircleV(position, radius, BLUE);
        }
        else if (level == 3) {
            DrawCircleV(position, radius, RED);
        }
        
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
    Ball ball1;
    Ball ball2;
    int score;
    //int highScore;
    //GameState state;
    int highScore;
    bool isNewHigh;
    bool hasHighScore; // to avoid showinf on first time
    int gameCount = 0;
    bool waitForKeyRelease;

    // checking for new levels
    bool ball1Active = false;
    bool ball2Active = false;
    //int level = 1;
    bool levelUpAvailable = false;

    // checking out of bounds
    bool b1 = false;
    bool b2 = false;
    bool b3 = false;

    // resetting high score highlight
    //bool HighShown = false;

public:

    int level = 1; // public for theming

    enum GameState {
        MENU,
        PLAYING,
        GAME_OVER
    };


    GameState state;


    Game() : paddle(screenWidth, screenHeight), ball(screenWidth, screenHeight), ball1(screenWidth, screenHeight), ball2(screenWidth, screenHeight), score(0), highScore(0), hasHighScore(false), isNewHigh(false), state(MENU) {
        InitWindow(screenWidth, screenHeight, "2D Juggling Game for DSA Project");
        SetTargetFPS(60);
        waitForKeyRelease = false;

        ball1.position.y = 100;  // level 1 height
        ball2.position.y = 50;   // level 2 height

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

        /* if (state == MENU && IsKeyPressed(KEY_ENTER)) {
             score = 0;
             isNewHigh = false;
             ball.Reset(screenWidth, screenHeight);
             state = PLAYING;
         }*/
         // to not start playing again instantly
         // go to menu first
        if (waitForKeyRelease) {
            if (!IsKeyDown(KEY_ENTER)) {
                waitForKeyRelease = false; // key released
            }
            return; // skip rest of update
        }

        if (state == MENU) {
            if (IsKeyPressed(KEY_ENTER)) {
                state = PLAYING;
                //state = MENU;
                score = 0;
                ball.Reset(screenWidth, screenHeight);
                ball.Reset(screenWidth, screenHeight);
                ball1.Reset(screenWidth, screenHeight);
                ball2.Reset(screenWidth, screenHeight);
                ball1.position.y = 100;
                ball2.position.y = 50;

                ball1Active = false;
                ball2Active = false;
                level = 1;

            }
        }
        else if (state == PLAYING) {
            paddle.Update(dt, screenWidth);
            ball.Update(dt);

            if (!ball.IsOutOfBounds(screenHeight) && ball.CheckCollisionWithPaddle(paddle)) {
                ball.velocity.y *= -1;
                
                /*if (b1 == true) {
                    return;
                }*/
                score++;

                if (score > highScore) {
                    highScore = score;
                    isNewHigh = true;
                    hasHighScore = true;
                }

            }
            //new level balls

            if (ball1Active) {
                ball1.Update(dt);
                if (!ball1.IsOutOfBounds(screenHeight) && ball1.CheckCollisionWithPaddle(paddle)) {
                    ball1.velocity.y *= -1;
                    /*if (b2 == true) {
                        return;
                    }*/
                    score++;
                    if (score > highScore) {
                        highScore = score;
                        isNewHigh = true;
                        hasHighScore = true;
                    }
                }

            }

            if (ball2Active) {
                ball2.Update(dt);
                if (!ball2.IsOutOfBounds(screenHeight) && ball2.CheckCollisionWithPaddle(paddle)) {
                    ball2.velocity.y *= -1;
                    score++;
                    if (score > highScore) {
                        highScore = score;
                        isNewHigh = true;
                        hasHighScore = true;
                    }
                }
                /*if (b3 == true) {
                    return;
                }*/
            }

            if (ball.IsOutOfBounds(screenHeight) || ball1.IsOutOfBounds(screenHeight) || ball2.IsOutOfBounds(screenHeight)) {
                /*state = MENU;*/  // Go back to menu
                if (ball.IsOutOfBounds(screenHeight) || ball1.IsOutOfBounds(screenHeight) || ball2.IsOutOfBounds(screenHeight)) {
                    state = GAME_OVER;
                    level = 1;
                }
                



                gameCount++;
            }

            if (score % 5 == 0 && score > 0) {
                if (score >= 5 && !ball1Active) {
                    levelUpAvailable = true;
                }
                else if (score >= 10 && !ball2Active) {
                    levelUpAvailable = true;
                }
                /* if ((score == 5 && !ball1Active) || (score == 10 && !ball2Active)) {
                     levelUpAvailable = true;
                 }*/
            }

            if (levelUpAvailable && IsKeyPressed(KEY_SPACE)) {
                if (!ball1Active) {
                    ball1Active = true;
                    level++;
                    levelUpAvailable = false;
                }
                else if (!ball2Active) {
                    ball2Active = true;
                    level++;
                    levelUpAvailable = false;
                }
            }



        }
        else if (state == GAME_OVER && IsKeyPressed(KEY_ENTER)) {
            score = 0;
            isNewHigh = false;
            //b1 = b2 = b3 = false;
            
            /*HighShown = false;*/ // reset highlight
            ball.Reset(screenWidth, screenHeight);
            state = MENU;
        }
    }


    void Draw() {
        BeginDrawing();
        
        //ClearBackground(RAYWHITE);


        // background color
        
        if (level == 1) {
ClearBackground(RAYWHITE);

        }
        else if (level == 2) {
            ClearBackground(RAYWHITE);
        }
        else if (level == 3) {
            ClearBackground(DARKGRAY);
        }




        if (state == MENU) {
            DrawText("JUGGLING GAME", screenWidth / 2 - 240, screenHeight / 2 - 120, 60, DARKGRAY);
            DrawText("Press [ENTER] to Start", screenWidth / 2 - 120, screenHeight / 2 + 30, 20, GRAY);

            DrawText("UITS ID: 0432410005101088", screenWidth - 780, screenHeight - 100, 20, BLACK);
            DrawText("Prototype for DSA Project", screenWidth - 780, screenHeight - 70, 20, BLACK);
            DrawText("made by @b1tranger using Raylib", screenWidth - 780, screenHeight - 40, 20, GRAY);

            if (gameCount > 0) {
                DrawText(TextFormat("Current Record: %d", highScore), screenWidth / 2 - 130, screenHeight / 2 - 20, 30, GRAY);
            }
        }
        else if (state == PLAYING) {

            paddle.Draw(level);

            ball.Draw(level);
            if (ball1Active) ball1.Draw(level); // new balls
            if (ball2Active) ball2.Draw(level);

            
            // Draw current score
            DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);

            // level show
            DrawText(TextFormat("Level: %d", level), 10, 70, 20, BLACK);

            // level up prompt
            if (levelUpAvailable) {
                DrawText("Level Up Available! Press [SPACE]", screenWidth / 2 - 160, 20, 20, ORANGE);
            }

          
            if (hasHighScore && gameCount > 0) {
                int highScoreFontSize = isNewHigh ? 30 : 20;
                int PositionX= isNewHigh ? 300 : 10;
                Color highScoreColor = isNewHigh ? RED : DARKGRAY;
                DrawText(TextFormat("Highest Score: %d", highScore), PositionX, 40, highScoreFontSize, highScoreColor);
               
            }


        }
        else if (state == GAME_OVER) {
            DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 60, 40, RED);
            DrawText(TextFormat("Score: %d", score), screenWidth / 2 - 60, screenHeight / 2, 30, BLACK);

            if (isNewHigh) {
                DrawText("New High Score!", screenWidth / 2 - 80, screenHeight / 2 + 40, 20, RED);
            }

            DrawText("Press [ENTER] to return to Menu", screenWidth / 2 - 160, screenHeight / 2 + 80, 20, DARKGRAY);
        }


        EndDrawing();
    }

};

int main() {
    Game game;
    game.Run();
    return 0;
}
