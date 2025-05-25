// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "raylib.h"
using namespace std;

int main()
{
    std::cout << "Starting the game" << std::endl;
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Game for DSA Project");
    SetTargetFPS(60);
    while (WindowShouldClose() == false) {
        BeginDrawing();






        EndDrawing();
    }

    CloseWindow();
    return 0;
}