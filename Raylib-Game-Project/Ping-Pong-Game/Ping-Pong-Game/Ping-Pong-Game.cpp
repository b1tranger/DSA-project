#include <iostream>
#include <raylib.h>
using namespace std;

class Ball {
public:
    float  x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, WHITE);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth() || x - radius <= 0) {
            speed_x *= -1;
        }

    }

};

class Paddle {
protected:
    void LimitMovement() {
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;

    void Draw() {
        DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, WHITE);
    }

    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            y = y + speed;
        }
        LimitMovement();
    }
};



Ball ball;    // Ball instances
Paddle player; //Paddle instance

int main()
{
    cout << "starting the game" << endl;
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "my Pong Game!");
    SetTargetFPS(60);


    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 6;

    //Game Loop
    while (WindowShouldClose() == false) {

        BeginDrawing();


        //updating
        ball.Update();
        player.Update();

        

        // Drawing
        ClearBackground(BLACK);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        
        //DrawCircle(screen_width/2, screen_height/2, 20, WHITE);
        DrawRectangle(10, screen_height / 2 - 60, 25, 120, WHITE);
        //DrawRectangle(screen_width - 25 - 10, screen_height / 2 - 60, 25, 120, WHITE);
        player.Draw();

        EndDrawing();
    }



    CloseWindow();



    return 0;
}