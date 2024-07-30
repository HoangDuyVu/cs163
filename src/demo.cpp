

#include <raylib.h>
#include <variable.hpp>
#include <node.hpp>

namespace test {
int main(void)
{

    const int screenWidth = 1440;
    const int screenHeight = 810;
	

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	Texture2D B = LoadTexture("res/textures/bottun.png");
	Texture2D C = LoadTexture("res/textures/name.png");
	Rectangle D = {400,0,500,500};


    while (!WindowShouldClose())   
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);
			DrawRectangle(0,0,screenWidth,screenHeight,Color {150,140,228,255});
			//DrawTexture(B, 0, 0, RAYWHITE);
			DrawTextureRec(B,D,{0,0},RAYWHITE);
			DrawTexture(C, 0, 0, RAYWHITE);

        EndDrawing();

    }

    CloseWindow();       


    return 0;
}
};