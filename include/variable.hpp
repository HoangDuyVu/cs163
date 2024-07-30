
#ifndef variable_hpp
#define variable_hpp
#include <raylib.h>
#include <iostream>

extern const int screenWidth;
extern const int screenHeight;

extern Texture2D Logo;

enum Pos{
    MENU,
    HEAPTREE
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
    MyColor color;
    int val;
    Vertex() {}
    Vertex(Vector2 Postion,float radius,int kind_mouse,bool col,bool press, MyColor color,int val):
    Postion(Postion),
    radius(radius),
    kind_mouse(kind_mouse),
    col(col),
    press(press),
    color(color),
    val(val) {}
};

struct Transforms{
    float progress; 
    Vertex u,v;
    Transforms() {}
    Transforms(Vertex u,Vertex v): u(u), v(v) {}
};


#endif /* node_hpp */