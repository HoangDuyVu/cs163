#include <iostream>
#include <raylib.h>
#include <ViewInApp.hpp>
#include <variable.hpp>

void ViewInApp::init(){
    Botton.resize(5);
    gtt = -1e8;
    Botton[0] = button_select({0,0},{1440,810},0,(Texture2D) LoadTexture("res/textures/in_app/bg_app.png"),RAYWHITE); 
    Botton[1] = button_select({-100,-4},{220,43},1,(Texture2D) LoadTexture("res/textures/bg/name.png"),RAYWHITE);
    Botton[2] = button_select({1206,7},{48,48},1,(Texture2D) LoadTexture("res/textures/in_app/return.png"),RAYWHITE);
    Botton[3] = button_select({1273,10},{56,46},1,(Texture2D) LoadTexture("res/textures/in_app/huongdan.png"),RAYWHITE);
    Botton[4] = button_select({1348,10},{49,46},1,(Texture2D) LoadTexture("res/textures/in_app/setting.png"),RAYWHITE);
  //  Botton[5] = button_select({27,741},{48,52},1,(Texture2D) LoadTexture("res/textures/in_app/undo.png"),RAYWHITE);
   // Botton[6] = button_select({102,741},{49,52},1,(Texture2D) LoadTexture("res/textures/in_app/redo.png"),RAYWHITE);
   // Botton[7] = button_select({237,750},{49,45},1,(Texture2D) LoadTexture("res/textures/in_app/pre.png"),RAYWHITE);
   // Botton[8] = button_select({294,750},{44,45},1,(Texture2D) LoadTexture("res/textures/in_app/pause.png"),RAYWHITE);
   // Botton[9] = button_select({346,750},{46,45},1,(Texture2D) LoadTexture("res/textures/in_app/suff.png"),RAYWHITE);
    Speed = button_select({1111,762},{237,22},1,LoadTexture("res/textures/in_app/speed.png"),RAYWHITE);
    NodeSpeed = button_select({1188,762},{42,22},1,LoadTexture("res/textures/in_app/node_speed.png"),RAYWHITE);
    Botton[1].image.height /=3.5;
    Botton[1].image.width /=3.5; 
    Speed.image.height /= 4;
    Speed.image.width /=4;
    NodeSpeed.image.height /= 4;
    NodeSpeed.image.width /=4;
    Speed.Size.x = Speed.image.width + 2;
    Speed.Size.y = Speed.image.height;
    NodeSpeed.Size.x = NodeSpeed.image.width;
    NodeSpeed.Size.y = NodeSpeed.image.height;
    for (button_select v: Botton) v.Size = {(float)v.image.height,(float)v.image.width};
    bool checkNodeSpeed = 0;
   //  std::cout << <co\n";
}

void ViewInApp::draw(){
    Vector2 Mouse = GetMousePosition();
    for (button_select v : Botton) {
        if (v.kind_mouse != 0 && v.CheckMouse(Mouse,3) ) v.col = 1;
        else v.col = 0;
        v.DrawBasic(0.7);
    }

    Speed.DrawBasic(1);
    NodeSpeed.DrawBasic(1);
}

int ViewInApp::UpdatePressOn(bool Press){
    int d = 0;
    Vector2 Mouse = GetMousePosition();
    for (button_select v : Botton) {
        if (v.kind_mouse != 0 && v.CheckMouse(Mouse,3) && Press) return d + 100;
        d++;
    }

    if (NodeSpeed.CheckMouse(GetMousePosition(),1) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        checkNodeSpeed = 1; 
        if (gtt == -1e8)
        gtt = GetMousePosition().x - NodeSpeed.Postion.x;
        std::cout << gtt << "\n";
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        checkNodeSpeed = 0;
        gtt = -1e8;
    }

    if (checkNodeSpeed){
            NodeSpeed.Postion.x = GetMousePosition().x - gtt;
            std::cout << NodeSpeed.Postion.x << "\n";
            if (NodeSpeed.Postion.x < Speed.Postion.x) 
                NodeSpeed.Postion.x = Speed.Postion.x;

            if (NodeSpeed.Postion.x + NodeSpeed.Size.x > Speed.Postion.x + Speed.Size.x) 
                NodeSpeed.Postion.x = Speed.Postion.x + Speed.Size.x - NodeSpeed.Size.x;
            std::cout << NodeSpeed.Postion.x << "\n";
    }

    float total = 237/2.0;
    float Nowpos = NodeSpeed.Postion.x + NodeSpeed.Size.x - Speed.Postion.x;
    if (Nowpos <= total) {
        float x = Nowpos / (total / 10.0);
        deltaTime = 1.0/(0.1*x);
    }
    else {
        Nowpos -= total;
        float x = Nowpos / (total /15.0);
        deltaTime = 1.0/(1.0 + 1.0*x);
    }

    return -1;
}