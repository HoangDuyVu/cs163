#include <iostream>
#include <raylib.h>
#include <ViewInApp.hpp>
#include <variable.hpp>

void ViewInApp::init(){
    Botton.resize(10);
    Botton[0] = button_select({0,0},{1440,810},0,(Texture2D) LoadTexture("res/textures/in_app/bg_app.png"),RAYWHITE); 
    Botton[1] = button_select({10,12},{220,43},1,(Texture2D) LoadTexture("res/textures/in_app/logo.png"),RAYWHITE);
    Botton[2] = button_select({1206,7},{48,48},1,(Texture2D) LoadTexture("res/textures/in_app/return.png"),RAYWHITE);
    Botton[3] = button_select({1273,10},{56,46},1,(Texture2D) LoadTexture("res/textures/in_app/huongdan.png"),RAYWHITE);
    Botton[4] = button_select({1348,10},{49,46},1,(Texture2D) LoadTexture("res/textures/in_app/setting.png"),RAYWHITE);
    Botton[5] = button_select({27,741},{48,52},1,(Texture2D) LoadTexture("res/textures/in_app/undo.png"),RAYWHITE);
    Botton[6] = button_select({102,741},{49,52},1,(Texture2D) LoadTexture("res/textures/in_app/redo.png"),RAYWHITE);
    Botton[7] = button_select({237,750},{49,45},1,(Texture2D) LoadTexture("res/textures/in_app/pre.png"),RAYWHITE);
    Botton[8] = button_select({294,750},{44,45},1,(Texture2D) LoadTexture("res/textures/in_app/pause.png"),RAYWHITE);
    Botton[9] = button_select({346,750},{46,45},1,(Texture2D) LoadTexture("res/textures/in_app/suff.png"),RAYWHITE);
    for (button_select v: Botton) v.Size = {(float)v.image.height,(float)v.image.width};
   //  std::cout << <co\n";
}

void ViewInApp::draw(){
    Vector2 Mouse = GetMousePosition();
    for (button_select v : Botton) {
        if (v.kind_mouse != 0 && v.CheckMouse(Mouse,3) ) v.col = 1;
        else v.col = 0;
        v.DrawBasic(0.7);
    }
}

int ViewInApp::UpdatePressOn(bool Press){
    int d = 0;
    Vector2 Mouse = GetMousePosition();
    for (button_select v : Botton) {
        if (v.kind_mouse != 0 && v.CheckMouse(Mouse,3) && Press) return d + 100;
        d++;
    }
    return -1;
}