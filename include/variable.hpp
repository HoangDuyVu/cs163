
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
extern const int Limitnode;
extern bool Loadfile;

extern Font customFont;
extern double deltaTime;

extern Color Col[7];
extern  int sel_n;
extern  int sel_v;
extern  int sel_k;
extern  int sel_i;
extern  int sel_check;
extern  std::string sel_s;
extern  int LimitNode;
extern char pathfile[40];
extern std::vector<std::vector<int> > adj;

extern Texture2D Logo;

enum Pos{
    MENU,
    HEAPTREE,
    AVLTREE,
    HASHTABLE,
    TRIE,
    GRAPH,
    TTFTREE
};

enum Kind{
    Create,
    Insert,
    Delete,
    Extract,
    Update,
    Search,
    file
};

extern Pos pos;
extern Texture2D L1,L2,L3;
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
        d = d + 0.04*k;
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
    int Ani;
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
void DrawVertexText2(Vector2 Postion,float radius,char* text, int kind_color,unsigned char a);
void DrawVertexText(Vector2 Postion,float radius,char *text, int fontSize,unsigned char a);
void DrawEdge(Vector2 PostionX,Vector2 PostionY,int val, int kind_color,unsigned char a);
void DrawEdge2(Vector2 PostionX,Vector2 PostionY,int val, int kind_color,unsigned char a);
void DrawVertexRoot(Vector2 Postion,float radius,int val, int kind_color,unsigned char a);
void DrawVertexL(Vector2 Postion,float radius,int val, int kind_color,unsigned char a);



#endif /* node_hpp */