#include <variable.hpp>
#include <raylib.h>

const int screenWidth = 1440;
const int screenHeight = 810;
const Color ConstColor1 = {97, 91, 174, 255};
const Color ConstColor2 = {249, 150, 211,255};

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
Pos pos;
Texture2D Logo;
Font customFont;
CREATE _create;
INSERT _insert;

void init_bg(){ 
    Logo = LoadTexture("res/textures/bg/name.png");
    customFont = LoadFont("res/fonts/Roboto/Roboto-Bold.ttf");
}

void draw_bg(){
    DrawRectangle(0,0,screenWidth,screenHeight,Color {150,140,228,255});
    DrawTexture(Logo,0,0,RAYWHITE);
}

bool button_select::CheckMouse(Vector2 A,int k){
    return Postion.x <= A.x - k && Postion.x + Size.x >= A.x + k 
        && Postion.y <= A.y - k && Postion.y + Size.y >= A.y + k;  
}

bool choose::CheckMouse(Vector2 A,int k){
    return Postion.x <= A.x - k && Postion.x + Size.x >= A.x + k 
        && Postion.y <= A.y - k && Postion.y + Size.y >= A.y + k;    
}

void choose::SolvePress(){
    if (kind == Create) {
        int g = _create.getPress();
    }
}

void choose::Draw(){
    Vector2 x = GetMousePosition();
    float g = 1;
    if (CheckMouse(x,1)) g = 0.6f;
    if (press) DrawRectangleV(Postion,Size,Fade(color2,g));
    else DrawRectangleV(Postion,Size,Fade(color,g));
    int fontSize = 20;
    Vector2 textSize = MeasureTextEx(customFont, text, fontSize, 1);
    Vector2 textPosition = {
            Postion.x + (Size.x - textSize.x) / 2,
            Postion.y + (Size.y - textSize.y) / 2
        };

    DrawTextEx(customFont, text, textPosition, fontSize, 1, WHITE);
}

void choose::DrawPress(){
    if (kind == Create) {
        _create.Draw();
    }
    if (kind == Insert) {
        _insert.Draw();
    }
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

void DrawVertex(Vector2 Postion,float radius,int val, int kind_color,unsigned char a) {

    char text[4];
    snprintf(text, sizeof(text), "%d", val);
    int fontSize = 5;
    for (int i = 20 ; i <= 70 ; i++) {
        Vector2 k = MeasureTextEx(customFont, text, i, 0);
        if (std::max(k.x,k.y) <= radius*7/5) fontSize = i;
        else break;
    }

 //   std::cout << fontSize << "\n";

    Vector2 textSize = MeasureTextEx(customFont, text, fontSize, 0);

    Vector2 textPosition = {
        Postion.x - textSize.x / 2,
        Postion.y - textSize.y / 2
    };

    if (kind_color == 0) {
        DrawCircle(Postion.x,Postion.y, radius,WHITE);
        DrawRing(Postion,radius,radius*6/5.0,0,360,100.0f,{107,100,184,a});
        DrawTextEx(customFont, text, textPosition, fontSize, 0, {107,100,184,a});
    }
    else if (kind_color == 1){
        DrawCircle(Postion.x,Postion.y, radius,WHITE);
        DrawRing(Postion,radius,radius*6/5.0,0,360,100.0f,{249, 150, 211,a});
        DrawTextEx(customFont, text, textPosition, fontSize, 0, {249, 150, 211,a});
    }
    else if (kind_color == 2) {
        DrawCircle(Postion.x,Postion.y, radius,{249, 150, 211,a});
        DrawTextEx(customFont, text, textPosition, fontSize, 0,WHITE);
    }
    else if (kind_color == 4){
        DrawTextEx(customFont, text, textPosition, fontSize, 0,{107,100,184,a});
    }
}

void DrawEdge(Vector2 PostionX,Vector2 PostionY,int val, int kind_color,unsigned char a) {
    DrawLineEx(PostionX,PostionY,4.0f,{107,100,184,a});
}

