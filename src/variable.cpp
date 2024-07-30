#include <variable.hpp>
#include <raylib.h>

const int screenWidth = 1440;
const int screenHeight = 810;

Pos pos;
Texture2D Logo;
void init_bg(){ 
    Logo = LoadTexture("res/textures/bg/name.png");
}

void draw_bg(){
    DrawRectangle(0,0,screenWidth,screenHeight,Color {150,140,228,255});
    DrawTexture(Logo,0,0,RAYWHITE);
}

bool button_select::CheckMouse(Vector2 A,int k){
    return Postion.x <= A.x - k && Postion.x + Size.x >= A.x + k 
        && Postion.y <= A.y - k && Postion.y + Size.y >= A.y + k;  
}

bool button_select::CheckPress(Vector2 A,int k,bool _press){
    press = 0;
    if (!_press) return false;
    if (CheckMouse(A,k)) {
        press = 1;
        return true;
    }

    return false;
}
   
void button_select::DrawBasic(float g){
    float k = 1;
    if (col) k = g;
    DrawTexture(image,Postion.x,Postion.y,Fade(color,k));
}