#include <variable.hpp>
#include <raylib.h>

const int screenWidth = 1440;
const int screenHeight = 810;
const Color ConstColor1 = {97, 91, 174, 255};
const Color ConstColor2 = {249, 150, 211,255};
const int Limitnode = 40;

int sel_n;
int sel_v;
int sel_k;
int sel_i;
std::string sel_s;
Texture2D L1,L2,L3;
int LimitNode;
char pathfile[40];
bool Loadfile;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
Pos pos;
Texture2D Logo;
Font customFont;

double deltaTime = 0.5f;

void init_bg(){ 
    L1 = LoadTexture("res/textures/node/node1.png");
    L2 = LoadTexture("res/textures/node/node2.png");
    L3 = LoadTexture("res/textures/node/node3.png");
    Logo = LoadTexture("res/textures/bg/name.png");
    customFont = LoadFontEx("res/fonts/Roboto/Roboto-Bold.ttf",100,nullptr,0); // Path to your custom font file

    // Set texture filter for better text rendering
    SetTextureFilter(customFont.texture, TEXTURE_FILTER_POINT); // Or TEXTURE_FILTER_BILINEAR for smoother text
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

void DrawVertex(Vector2 Postion,float radius,int val, int kind_color,unsigned char a) {

    char text[7];
    snprintf(text, sizeof(text), "%d", val);
    int fontSize = 10;
    for (int i = 11 ; i <= 70 ; i++) {
        Vector2 k = MeasureTextEx(customFont, text, i, 0);
        if (std::max(k.x,k.y) <= radius*7/5) fontSize = i;
        else break;
    }

    Vector2 textSize = MeasureTextEx(customFont, text, fontSize, 0);

    Vector2 textPosition = {
        Postion.x - textSize.x / 2,
        Postion.y - textSize.y / 2
    };

    if (kind_color == 0) {
        DrawCircle(Postion.x,Postion.y, radius,Fade(WHITE,1.0*a/255.0));
        DrawRing(Postion,radius,radius*6/5.0,2,365,200.0f,{107,100,184,a});
        DrawTextEx(customFont, text, textPosition, fontSize, 0, {107,100,184,a});
    }
    else if (kind_color == 1){
        DrawCircle(Postion.x,Postion.y, radius,Fade(WHITE,1.0*a/255.0));
        DrawRing(Postion,radius,radius*6/5.0,2,365,200.0f,{249, 150, 211,a});
        DrawTextEx(customFont, text, textPosition, fontSize, 0, {249, 150, 211,a});
    }
    else if (kind_color == 2) {
        DrawCircle(Postion.x,Postion.y, radius*6/5.0,{249, 150, 211,a});
        DrawTextEx(customFont, text, textPosition, fontSize, 0,Fade(WHITE,1.0*a/255.0));
    }
    else if (kind_color == 4){
        DrawTextEx(customFont, text, textPosition, fontSize, 0,{107,100,184,a});
    }
}

void DrawVertexText2(Vector2 Postion,float radius,char* text, int kind_color,unsigned char a) {
    int fontSize = 10;
    for (int i = 11 ; i <= 70 ; i++) {
        Vector2 k = MeasureTextEx(customFont, text, i, 0);
        if (std::max(k.x,k.y) <= radius*7/5) fontSize = i;
        else break;
    }

    Vector2 textSize = MeasureTextEx(customFont, text, fontSize, 0);

    Vector2 textPosition = {
        Postion.x - textSize.x / 2,
        Postion.y - textSize.y / 2
    };

    if (kind_color == 0) {
        DrawCircle(Postion.x,Postion.y, radius,Fade(WHITE,1.0*a/255.0));
        DrawRing(Postion,radius,radius*6/5.0,2,365,200.0f,{107,100,184,a});
        DrawTextEx(customFont, text, textPosition, fontSize, 0, {107,100,184,a});
    }
    else if (kind_color == 1){
        DrawCircle(Postion.x,Postion.y, radius,Fade(WHITE,1.0*a/255.0));
        DrawRing(Postion,radius,radius*6/5.0,2,365,200.0f,{249, 150, 211,a});
        DrawTextEx(customFont, text, textPosition, fontSize, 0, {249, 150, 211,a});
    }
    else if (kind_color == 2) {
        DrawCircle(Postion.x,Postion.y, radius*6/5.0,{249, 150, 211,a});
        DrawTextEx(customFont, text, textPosition, fontSize, 0,Fade(WHITE,1.0*a/255.0));
    }
    else if (kind_color == 4){
        DrawTextEx(customFont, text, textPosition, fontSize, 0,{107,100,184,a});
    }
}

void DrawVertexText(Vector2 Postion,float radius,char *text, int fontSize,unsigned char a) {
    Vector2 textSize = MeasureTextEx(customFont, text, fontSize, 0);
    Vector2 textPosition = {
        Postion.x - textSize.x / 2,
        Postion.y - textSize.y / 2
    };

    DrawTextEx(customFont, text, textPosition, fontSize, 0,Fade(RED,1.0*a/255.0));
}


void DrawEdge(Vector2 PostionX,Vector2 PostionY,int val, int kind_color,unsigned char a) {
    if (kind_color == 0) DrawLineEx(PostionX,PostionY,4.0f,{107,100,184,a});
    else if (kind_color == 1) DrawLineEx(PostionX,PostionY,4.0f,ConstColor2);
}

void DrawEdge2(Vector2 PostionX,Vector2 PostionY,int val, int kind_color,unsigned char a) {
    if (kind_color == 0) DrawLineEx(PostionX,PostionY,4.0f,{107,100,184,a});
    else if (kind_color == 1) DrawLineEx(PostionX,PostionY,4.0f,{255, 143, 183,a});
}

void DrawVertexRoot(Vector2 Postion,float radius,int val, int kind_color,unsigned char a) {

  //  std::cout << kind_color << "\n";
    char text[4];
    snprintf(text, sizeof(text), "%d", val);
    int fontSize = 20;
    for (int i = 20 ; i <= 70 ; i++) {
        Vector2 k = MeasureTextEx(customFont, text, i, 0);
        if (std::max(k.x,k.y) <= radius*7/5) fontSize = i;
        else break;
    }

    Rectangle rect = { Postion.x - radius, Postion.y - radius, radius*2, radius*2 }; // x, y, width, height
    float roundness = 0.2f;
    int segments = 4;

 //   std::cout << fontSize << "\n";

    Vector2 textSize = MeasureTextEx(customFont, text, fontSize, 0);

    Vector2 textPosition = {
        Postion.x - textSize.x / 2,
        Postion.y - textSize.y / 2
    };

    if (kind_color == 0) {
        DrawRectangleRounded(rect, roundness, segments, {107,100,184,a});
        DrawTextEx(customFont, text, textPosition, fontSize, 0, WHITE);
    }
    else if (kind_color == 1){
        DrawRectangleRounded(rect, roundness, segments, {107,100,184,255});
        DrawRectangleRounded(rect, roundness, segments, {249, 150, 211,a});
        DrawTextEx(customFont, text, textPosition, fontSize, 0, WHITE);
    }
    else if (kind_color == 2) {
        DrawCircle(Postion.x,Postion.y, radius*6/5.0,{249, 150, 211,a});
        DrawTextEx(customFont, text, textPosition, fontSize, 0,Fade(WHITE,1.0*a/255.0));
    }
    else if (kind_color == 4){
        DrawTextEx(customFont, text, textPosition, fontSize, 0,{107,100,184,a});
    }
}

void DrawVertexL(Vector2 Postion,float radius,int val, int kind_color,unsigned char a) {

    char text[7];
    snprintf(text, sizeof(text), "%d", val);
    int fontSize = 10;
    for (int i = 11 ; i <= 70 ; i++) {
        Vector2 k = MeasureTextEx(customFont, text, i, 0);
        if (std::max(k.x,k.y) <= radius*7/5) fontSize = i;
        else break;
    }

    Vector2 textSize = MeasureTextEx(customFont, text, fontSize, 0);

    Vector2 textPosition = {
        Postion.x - textSize.x / 2,
        Postion.y - textSize.y / 2
    };

    Texture2D PH;
    if (kind_color == 0) PH = L1;
    if (kind_color == 1) PH = L2;
    if (kind_color == 2) PH = L3;

    double g = PH.height;
    PH.height *= (radius*2 + 14 - (10*(21.4-radius)/21.4))/PH.height;
    PH.width *= (radius*2 + 14 -  (10*(21.4-radius)/21.4))/g;

    if (kind_color == 0) {
        DrawTexture(PH,Postion.x - PH.width/2.0,Postion.y - PH.height/2.0,Fade(WHITE,1.0*a/255.0));
        DrawTextEx(customFont, text, textPosition, fontSize, 0, {107,100,184,a});
    }
    else if (kind_color == 1){
        DrawTexture(PH,Postion.x - PH.width/2.0,Postion.y - PH.height/2.0,Fade(WHITE,1.0*a/255.0));
        DrawTextEx(customFont, text, textPosition, fontSize, 0,{255, 143, 183,a});
    }
    else if (kind_color < 4) {
        DrawTexture(PH,Postion.x - PH.width/2.0,Postion.y - PH.height/2.0,Fade(WHITE,1.0*a/255.0));
        DrawTextEx(customFont, text, textPosition, fontSize, 0,Fade(WHITE,1.0*a/255.0));
    }
    else if (kind_color == 4){
        DrawTextEx(customFont, text, textPosition, fontSize, 0,{107,100,184,a});
    }
}

