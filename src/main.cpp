#include <iostream>
#include <raylib.h>
#include <node.hpp>
#include <variable.hpp>
#include <ViewMenu.hpp>
#include <activities.hpp>


int main(void) {
    InitWindow(screenWidth, screenHeight, "CS 162");
    init_bg();
    init();
    pos = MENU;

    while (!WindowShouldClose())   
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            Activities();
            draw();
        EndDrawing();
    }

    CloseWindow();       
    return 0;
}