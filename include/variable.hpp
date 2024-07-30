
#ifndef variable_hpp
#define variable_hpp
#include <raylib.h>
#include <iostream>
#include <vector>
#include <random>

extern std::mt19937 rng;
extern const int screenWidth;
extern const int screenHeight;
extern const Color ConstColor1;
extern const Color ConstColor2;

extern Font customFont;


extern Texture2D Logo;

enum Pos{
    MENU,
    HEAPTREE
};

enum Kind{
    Create,
    Insert
};

extern Pos pos;
void init_bg();
void draw_bg();

typedef struct _MyColor {
    unsigned char r;    // Red
    unsigned char g;    // Green
    unsigned char b;    // Blue
    unsigned char a;    // Alpha
    _MyColor(){}
    _MyColor(unsigned char r,unsigned char g,unsigned char b,unsigned char a): r(r), g(g), b(b), a(a) {}
} MyColor;

struct Pointer {
    Rectangle Rect;
    Vector2 Postion;
    Vector2 Size;
    float d;
    int k;

    void init(Vector2 _Postion, Vector2 _Size){
        d = 1;
        k = 1;
        Size = _Size;
        Postion = _Postion;
        Rect = {Postion.x,Postion.y,Size.x,Size.y};
    }

    void DrawPointer(){
        d = d + 0.002*k;
       // std::cout << d << "\n";
        if (d > 1) {
            d = 1;
            k *= -1;
        }

        if (d < 0) {
            d = 0;
            k *= -1;
        }

        DrawRectangleV(Postion,Size,Fade(WHITE,d));
    }
    
};


struct button_select {
    Vector2 Postion;
    Vector2 Size;
    int kind_mouse;
    Texture2D image; 
    Color color;
    bool col;
    bool press;
    button_select() {};
    button_select(Vector2 Postion,Vector2 Size, int kind_mouse, Texture2D image, Color color):
    Postion(Postion),
    Size(Size),
    kind_mouse(kind_mouse),
    image(image),
    color(color){}

    void DrawBasic(float g);
    bool CheckMouse(Vector2 A,int k);
    bool CheckPress(Vector2 A,int k,bool _press);
};

struct Vertex {
    Vector2 Postion;
    float radius; 
    int kind_mouse;
    bool col;
    bool press;
    int Af;
    int color;
    int val;
    Vertex() {}
    Vertex(Vector2 Postion,float radius,int kind_mouse,bool col,bool press, int color,int val):
    Postion(Postion),
    radius(radius),
    kind_mouse(kind_mouse),
    col(col),
    press(press),
    color(color),
    val(val) {}
};

struct Edge {
    Vector2 PostionX,PostionY,PostionVal;
    int Af;
    int color;
    int val;
    Edge() {}
    Edge(Vector2 PostionX,Vector2 PostionY,Vector2 PostionVal, int color,int val,int Af):
    PostionX(PostionX),
    PostionY(PostionY),
    PostionVal(PostionVal),
    color(color),
    val(val),
    Af(Af) {}
};


struct choose{

    Kind kind;
    Vector2 Postion; 
    Vector2 Size;
    const char * text; 
    Color color;
    bool press;
    Color color2;

    choose() {}
    choose(Kind kind,Vector2 postion, Vector2 size,const char * text,Color color,Color color2,bool press):
    kind(kind),
    Postion(postion),
    Size(size),
    text(text),
    color(color),
    color2(color2),
    press(press)
    {}

    bool CheckMouse(Vector2 A,int k);
    void Draw();
    void DrawPress();
    void SolvePress();
    
};

struct CREATE{
    Vector2 Postion;
    Rectangle Rect;
    Pointer Pointer_A;
    std::vector <button_select> Item;
    char a[3];
    void init(Vector2 _postion){
        Postion = _postion;
        Item.resize(3);
        Rect = {184,Postion.y,200,40};
        Pointer_A.init({239,506},{3,16});
        a[0] = '0';
        a[1] = '\0';
        Item[0] = button_select({194,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/N.png"),WHITE);
        Item[1] = button_select({285,Postion.y + 5},{30,30},1,LoadTexture("res/textures/select/Rand.png"),WHITE);
        Item[2] = button_select({331,Postion.y + 5},{42,29},1,LoadTexture("res/textures/select/OK.png"),WHITE);
      //  Item[0] = button_select({194,Postion.y + 5},{80,29},1,LoadTexture("res/textures/select/N.png"),WHITE);
    }

    void Draw(){

        Vector2 x = GetMousePosition();

        DrawRectangle(Rect.x,Rect.y,Rect.width,Rect.height,{139, 130, 252,255});
        for (button_select v: Item){
            if (v.CheckMouse(x,1)) v.col = 1;
            else v.col = 0;
            v.DrawBasic(0.8f);
        }

        if (Item[1].CheckPress(x,1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
            a[0] = rng() % 3 + '0';
            a[1] = rng() % 10 + '0';
            a[2] = '\0';

            if (a[0] == '0') {
                a[0] = a[1];
                a[1] = '\0';
            }
        }

        int key = GetCharPressed();
        while (key > 0) {
             if ((key >= 48) && (key <= 57) && strlen(a) < 2) {
                int len = strlen(a);
                a[len] = (char) key;
                a[len + 1] = '\0';
            }

            int n = 0;
            for (int i = 0 ; i < strlen(a); i++) n = n*10 + a[i] - '0';
            if (n > 30) {
                a[0] = '3'; 
                a[1] = '0';
                a[2] = '\0';
            }

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            int len = strlen(a);
            if (len > 0) a[len - 1] = '\0';
        }

        Rectangle Rec = {231,Postion.y + 5,42,29};
        int fontSize = 25;

        Vector2 textSize = MeasureTextEx(customFont, a, fontSize, 1);

        Vector2 textPosition = {
            Rec.x + (Rec.width - textSize.x) / 2,
            Rec.y + (Rec.height - textSize.y) / 2
        };

        DrawTextEx(customFont, a, textPosition, fontSize, 1, WHITE);
        Pointer_A.Postion = {textPosition.x + textSize.x + 3,textPosition.y + 4};
        Pointer_A.DrawPointer();
    }

    int getPress(){
        return -1;
    }

};

struct INSERT{
    Vector2 Postion;
    Rectangle Rect;
    Pointer Pointer_A;
    std::vector <button_select> Item;
    char a[3];
    void init(Vector2 _postion){
        Postion = _postion;
        Item.resize(3);
        Rect = {184,Postion.y,200,40};
        Pointer_A.init({239,506},{3,16});
        a[0] = '0';
        a[1] = '\0';
        Item[0] = button_select({194,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/V.png"),WHITE);
        Item[1] = button_select({285,Postion.y + 5},{30,30},1,LoadTexture("res/textures/select/Rand.png"),WHITE);
        Item[2] = button_select({331,Postion.y + 5},{42,29},1,LoadTexture("res/textures/select/OK.png"),WHITE);
      //  Item[0] = button_select({194,Postion.y + 5},{80,29},1,LoadTexture("res/textures/select/N.png"),WHITE);
    }

    void Draw(){

        Vector2 x = GetMousePosition();

        DrawRectangle(Rect.x,Rect.y,Rect.width,Rect.height,{139, 130, 252,255});
        for (button_select v: Item){
            if (v.CheckMouse(x,1)) v.col = 1;
            else v.col = 0;
            v.DrawBasic(0.8f);
        }

        if (Item[1].CheckPress(x,1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
            a[0] = rng() % 10 + '0';
            a[1] = rng() % 10 + '0';
            a[2] = '\0';

            if (a[0] == '0') {
                a[0] = a[1];
                a[1] = '\0';
            }
        }

        int key = GetCharPressed();
        while (key > 0) {
             if ((key >= 48) && (key <= 57) && strlen(a) < 2) {
                int len = strlen(a);
                a[len] = (char) key;
                a[len + 1] = '\0';
            }

            int n = 0;
            for (int i = 0 ; i < strlen(a); i++) n = n*10 + a[i] - '0';

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            int len = strlen(a);
            if (len > 0) a[len - 1] = '\0';
        }

        Rectangle Rec = {231,Postion.y + 5,42,29};
        int fontSize = 25;

        Vector2 textSize = MeasureTextEx(customFont, a, fontSize, 1);

        Vector2 textPosition = {
            Rec.x + (Rec.width - textSize.x) / 2,
            Rec.y + (Rec.height - textSize.y) / 2
        };

        DrawTextEx(customFont, a, textPosition, fontSize, 1, WHITE);
        Pointer_A.Postion = {textPosition.x + textSize.x + 3,textPosition.y + 4};
        Pointer_A.DrawPointer();
    }

    int getPress(){
        return -1;
    }

};

struct Transforms{
    float progress; 
    Vertex u,v;
    Transforms() {}
    Transforms(Vertex u,Vertex v): u(u), v(v) {}
};

struct TransformsEdge{
    float progress; 
    Edge u,v;
    TransformsEdge() {}
    TransformsEdge(Edge u,Edge v): u(u), v(v) {}
};

void DrawVertex(Vector2 Postion,float radius,int val, int kind_color,unsigned char a);
void DrawEdge(Vector2 PostionX,Vector2 PostionY,int val, int kind_color,unsigned char a);
extern CREATE _create;
extern INSERT _insert;


#endif /* node_hpp */