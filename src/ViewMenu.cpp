#include <iostream>
#include <raylib.h>
#include <ViewMenu.hpp>
#include <variable.hpp>

void Menu::init(){
    Botton.resize(6);
    Botton[0] = button_select({117,243},{268,240},1,(Texture2D) LoadTexture("res/textures/menu_bottom/heaptree.png"),RAYWHITE);
    Botton[1] = button_select({575,243},{268,240},1,(Texture2D) LoadTexture("res/textures/menu_bottom/avltree.png"),RAYWHITE);
    Botton[2] = button_select({1045,243},{268,240},1,(Texture2D) LoadTexture("res/textures/menu_bottom/234tree.png"),RAYWHITE);
    Botton[3] = button_select({117,523},{268,240},1,(Texture2D) LoadTexture("res/textures/menu_bottom/hashtable.png"),RAYWHITE);
    Botton[4] = button_select({575,523},{268,240},1,(Texture2D) LoadTexture("res/textures/menu_bottom/trie.png"),RAYWHITE);
    Botton[5] = button_select({1054,523},{268,240},1,(Texture2D) LoadTexture("res/textures/menu_bottom/graph.png"),RAYWHITE);

    for (button_select v: Botton) v.Size = {(float)v.image.height,(float)v.image.width};
   //  std::cout << "co\n";
}

int Menu::UpdatePressOn(){
    bool Press = 0;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) Press = 1;
   if (Press) std::cout << Press;
    Vector2 x = GetMousePosition();
    int d = 0;
    for (button_select v :Botton) {
        if (v.kind_mouse != 0 && v.CheckPress(x,10,Press)) return d;
        d++;
    }
    return -1;
}

void Menu::draw(){

    
    Vector2 Mouse = GetMousePosition();
    for (button_select v : Botton) {
        if (v.CheckMouse(Mouse,10)) v.col = 1;
        else v.col = 0;
        v.DrawBasic(0.6);
    }
}