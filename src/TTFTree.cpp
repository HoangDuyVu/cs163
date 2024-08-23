#include <iostream>
#include <raylib.h>
#include <TTFTree.hpp>
#include <variable.hpp>
#include <ViewInApp.hpp>
#include <activities.hpp>
#include <variable.hpp>
#include <random>
#include <fstream>


void TTFTree::init(){
    tft = TwoTFTree(Limitnode);
    Animation.clear();
    // AnimationEdge.clear();
    Unre.clear();
    select.init(); 

    Persistent = button_select({455,761},{582,23},0,LoadTexture("res/textures/in_app/tua.png"),RAYWHITE);
    Persistent.image.height /=4;
    Persistent.image.width /=4;
    NodePersistent = button_select({693,761},{51,25},0,LoadTexture("res/textures/in_app/node_tua.png"),RAYWHITE);
    NodePersistent.image.height /=4;
    NodePersistent.image.width /=4;

    Persistent.Size.x = Persistent.image.width + 2;
    Persistent.Size.y = Persistent.image.height;
    NodePersistent.Size.x = NodePersistent.image.width;
    NodePersistent.Size.y = NodePersistent.image.height;
    Pos_unre = -1;

    remote.resize(7);
    remote[0] = button_select({71,754},{31,34},1,LoadTexture("res/textures/remote /undo.png"),RAYWHITE);
    remote[1] = button_select({132,757},{43,31},1,LoadTexture("res/textures/remote /pre.png"),RAYWHITE);
    remote[2] = button_select({272,757},{44,32},1,LoadTexture("res/textures/remote /next.png"),RAYWHITE);
    remote[3] = button_select({350,754},{31,34},1,LoadTexture("res/textures/remote /redo.png"),RAYWHITE);
    remote[4] = button_select({202,747},{44,50},1,LoadTexture("res/textures/remote /pause.png"),RAYWHITE);
    remote[5] = button_select({205,750},{37,47},1,LoadTexture("res/textures/remote /continue.png"),RAYWHITE);
    remote[6] = button_select({198,743},{52,54},1,LoadTexture("res/textures/remote /repeat.png"),RAYWHITE);
    pause = 0;
    TimeNotification = 0;
    CheckNotification = 0;
    sel_n = 0;
    sel_v = 0;
    sel_k = 0;
    sel_i = 0;
}

int TTFTree::UpdatePressOn(){
    bool Press = 0;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) Press = 1;
    int res = viewapp.UpdatePressOn(Press);
    if (res != -1) return res;

    res = select.checkPressOn(Press);

    if (res != -1) return res;
    return -1;
}

Vector2 TTFTree::NewPos2D(Vector2 A,Vector2 B,float g) {
    return {A.x + (B.x - A.x)*g,A.y + (B.y - A.y)*g};
}

float TTFTree::NewPos1D(float x, float y, float g) {
    return x + (y - x)*g;
}

void TTFTree::DrawAnimation(std::vector<Transforms2> f,double g){
    for (Transforms2 v : f) {
        Vector2 NewPostion = NewPos2D(v.u.Postion,v.v.Postion,g);
        Vector2 NewPostionE = NewPos2D(v.u.PostionE,v.v.PostionE,g);
        Vector2 NewPostionPar = NewPos2D(v.u.PostionPar,v.v.PostionPar,g);
        int NewA = (int) std::min((float)254.0,NewPos1D(v.u.Af,v.v.Af,g));
        int NewAE = (int) std::min((float)254.0,NewPos1D(v.u.AE,v.v.AE,g));
        NewA = std::max(NewA,0);
        if (v.v.par != -1){
            DrawEdge2(NewPostionE,NewPostionPar,0,v.u.colorE,255);

            if (v.u.AE == 0) {
                DrawEdge2(NewPostionE,NewPostionPar,v.v.val,v.v.colorE,NewAE);
            }
            else 
            if (v.v.colorE != v.u.colorE) {
                NewPostionE = NewPos2D(NewPostionPar,NewPostionE,g);
             //   std::cout << g << " " << NewPostionE.x << " " << NewPostionE.y << " " << NewPostionPar.x << " " << NewPostionPar.y  << "\n";
                DrawEdge2(NewPostionE,NewPostionPar,v.v.val,1,255);
            }
        }
    }

    for (Transforms2 v : f) {
        Vector2 NewPostion = NewPos2D(v.u.Postion,v.v.Postion,g);
        int NewA = (int) std::min((float)254.0,NewPos1D(v.u.Af,v.v.Af,g));
        double Newr = NewPos1D(v.u.radius,v.v.radius,g);
        NewA = std::max(NewA,0);
        if (v.v.color != v.u.color) DrawVertexL(NewPostion,Newr,v.v.val,v.u.color,255);
        DrawVertexL(NewPostion,Newr,v.v.val,v.v.color,NewA);
    }

}

void TTFTree::UpdatePostionNodePer(){

    if (NodePersistent.CheckMouse(GetMousePosition(),1) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        checkNodePer = 1; 
        if (gtt == -1e8)
        gtt = GetMousePosition().x - NodePersistent.Postion.x;
     //   std::cout << gtt << "\n";
    }
    
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        checkNodePer = 0;
        gtt = -1e8;
    }

    if (checkNodePer){
     //   std::cout << "check";
            NodePersistent.Postion.x = GetMousePosition().x - gtt;
         //   std::cout << NodePersistent.Postion.x << "\n";
            if (NodePersistent.Postion.x < Persistent.Postion.x) 
                NodePersistent.Postion.x = Persistent.Postion.x;

            if (NodePersistent.Postion.x + NodePersistent.Size.x > Persistent.Postion.x + Persistent.Size.x - 1) 
                NodePersistent.Postion.x = Persistent.Postion.x + Persistent.Size.x - NodePersistent.Size.x - 1;
          //  std::cout << NodePersistent.Postion.x << "\n";

        float TotalPer = Persistent.Size.x - NodePersistent.Size.x;
        float deltaPer = TotalPer/Animation.size();

        float NowPOS = NodePersistent.Postion.x - 455;
        pos_ani = (int) NowPOS/deltaPer;
        double gg = (NowPOS - (pos_ani*deltaPer))/(deltaPer);
        TotalTime = deltaTime*gg;
    }

}

void TTFTree::SolveRemote(){

    if (pause == 0) {
        button_select &v = remote[4];
        if (v.CheckPress(GetMousePosition(),2,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
            pause = 1;
           // std::cout << "hahahaaa";

        }
    }
    else 
    if (pause == 1) {
        button_select &v = remote[5];
        if (v.CheckPress(GetMousePosition(),2,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
            pause = 0;
        }
    }
    else
    if (pause == 2) {
        button_select &v = remote[5];
        if (v.CheckPress(GetMousePosition(),2,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
            pause = 0;
            pos_ani = 0;
            TotalTime = 0;
            LastTime = GetTime();
        }
    }
    int d = 0;
    for (button_select &v : remote) {
        if (v.CheckMouse(GetMousePosition(),2)) v.col = 1;
        else v.col = 0;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        int k = -1;
        int d = 0;
        for (button_select v : remote)
        if (v.CheckPress(GetMousePosition(),2,1)) k = d;
        else d++;

    //    std::cout << k << "\n";

        if (k == 1) {
            if (pos_ani != 0) {
                pos_ani--;
                TotalTime = 0;
            }
        }
        else 
        if (k == 2) {
            if (pos_ani + 1 < Animation.size() ){
                pos_ani++;
                TotalTime = 0;
            }
        }
        else 
        if (k == 0){
            if (Pos_unre != -1) {
                Pos_unre--;
                if (Pos_unre == -1) {
                    Animation.clear();
                    pause = 1;
                    pos_ani = Animation.size();
                    TotalTime = 0;
                }
                else {
                    Animation = Unre[Pos_unre];
                    tft = UnreAVL[Pos_unre];
                    pause = 1;
                    pos_ani = Animation.size() - 1;
                    TotalTime = deltaTime;
                }
            }
        }
        else 
        if (k == 3) {
            if (Pos_unre + 1 < Unre.size()){
                Pos_unre++;
                Animation = Unre[Pos_unre];
                tft = UnreAVL[Pos_unre];
                pause = 1;
                pos_ani = Animation.size() - 1;
                TotalTime = deltaTime - deltaTime/10;
            }
        }
    }

    if (pos_ani == 0) remote[1].col = 1;
    if (pos_ani + 1 >= Animation.size()) remote[2].col = 1;
    if (Pos_unre == -1) remote[0].col = 1;
    if (Pos_unre + 1 == Unre.size()) remote[3].col = 1;

    for (button_select v : remote) {
        d++;
        v.DrawBasic(0.6);
        if (d == 4) break;
    }

    if (pause == 0)  remote[4].DrawBasic(0.6);
    if (pause == 1)  remote[5].DrawBasic(0.6);
    if (pause == 2)  remote[6].DrawBasic(0.6);
}

void TTFTree::draw(){
    SolveRemote();
    Vector2 Mouse = GetMousePosition();
    UpdatePostionNodePer();
    Notification();
   // DrawVertex(Vector2 {500,300},25,10,1,255);
    double NowTime = GetTime();

   if (CheckNotification == 1) {
       // std::cout << "co\n";
        TimeNotification +=  NowTime - LastTime;
   } 

   //std::cout << TimeNotification << " " << deltaTime << " " << TotalTime << " " << "\n";

    if (TimeNotification >= 0.00005f) {
        CheckNotification = 0;
        TimeNotification = 0;

    }

    if (Animation.size() > 0) {

        if (pause != 1){
            TotalTime += NowTime - LastTime;
        }

       // std::cout << NowTime - LastTime << "\n";
        if (TotalTime > deltaTime && pause != 1) {
            if (pos_ani + 1 < Animation.size()) {
                pos_ani++;
                TotalTime = 0;
                if (pause == 2) pause = 1;
            } else {
                TotalTime = deltaTime;
                pause = 2;
            }
        }

        LastTime = NowTime;

        double G = std::min((double)1.0,(double)TotalTime/deltaTime);
 
        DrawAnimation(Animation[pos_ani],G);

        float TotalPer = Persistent.Size.x - NodePersistent.Size.x;
        float deltaPer = TotalPer/Animation.size();

        float PostFir = pos_ani*deltaPer + G*deltaPer;
        NodePersistent.Postion = {455 + PostFir,761};

    }
    else NodePersistent.Postion = {455,761};

    Persistent.DrawBasic(1.0f); 
    NodePersistent.DrawBasic(1.0f);

    float Speed = 1.0/deltaTime - 0.1;
    char textBuffer[7];
    snprintf(textBuffer, sizeof(textBuffer), "%.1f", Speed);
    int Iz = strlen(textBuffer);
    textBuffer[Iz] = ' ';
    textBuffer[Iz + 1] = 'x';
    textBuffer[Iz + 2] = '\0';
    DrawTextEx(customFont,textBuffer,{1356,762},23,0,{220,249,243,255});

    select.draw();
}

int TTFTree::Select::checkPressOn(bool Press){
            if (Press && CheckMouse(GetMousePosition(),1)) return 0;
            int d = 1;

            if (KIND == 1) for (choose v : sel) {
                if (Press && v.CheckMouse(GetMousePosition(),1)) return d;
                d++;
            }


            if (KIND == 1) {
                for (choose &v : sel){
                    if (v.press) {
                        if (v.kind == Create && _create.Item[2].CheckPress(GetMousePosition(),1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                            v.press = 0;
                            KIND = 0;
                            int n = 0;
                            for (int i = 0 ; _create.a[i] != '\0' ; i++)
                                n = n * 10 + _create.a[i] - '0';
                            sel_n = n;
                           // std::cout << "create" << " " << sel_n << "\n";
                            return 200;
                        } 

                        if (v.kind == Insert && _insert.Item[2].CheckPress(GetMousePosition(),1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                            v.press = 0;
                            KIND = 0;

                            int n = 0;
                            for (int i = 0 ; _insert.a[i] != '\0' ; i++)
                                n = n * 10 + _insert.a[i] - '0';
                            sel_v = n;
                            return 201;
                        }

                        if (v.kind == Search && _search.Item[2].CheckPress(GetMousePosition(),1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                            v.press = 0;
                            KIND = 0;
                            int n = 0;
                            for (int i = 0 ; _search.a[i] != '\0' ; i++)
                                n = n * 10 + _search.a[i] - '0';
                            sel_k = n;
                            return 202;
                        }

                        if (v.kind == Delete && _delete.Item[2].CheckPress(GetMousePosition(),1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                            v.press = 0;
                            KIND = 0;
                            int n = 0;
                            for (int i = 0 ; _delete.a[i] != '\0' ; i++)
                                n = n * 10 + _delete.a[i] - '0';
                            sel_k = n;
                            return 203;
                        }
                        if (v.kind == Update && _update.Item[2].CheckPress(GetMousePosition(),1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                            v.press = 0;
                            KIND = 0;
                            int n = 0;
                            for (int i = 0 ; _update.a[i] != '\0' ; i++)
                                n = n * 10 + _update.a[i] - '0';
                            sel_i = n;

                            n = 0;
                            for (int i = 0 ; _update.b[i] != '\0' ; i++)
                                n = n * 10 + _update.b[i] - '0';

                            sel_v = n;
                            return 204;
                        } 
                        else if (v.kind == file && Loadfile == 1) {
                            v.press = 0;
                            KIND = 0;
                            Loadfile = 0;
                            return 205;
                        }
                    }
                }
            }
            return -1;
        }

void TTFTree::Activity(){

 //   LimitNode = avl.GetSize();
    int g = UpdatePressOn();
    if (g == 101 || g == 102) {
        pos = MENU;
        return ;
    } 

    if (g == 0) {
        if (select.KIND == 0) {
            select.KIND ^= 1;
            select.Textr = select.Open;
        }
        else {
            select.KIND ^= 1;
            select.Textr = select.Close;
        }
    }

    if (g == 200) {
        create(sel_n);
    }
    else if (g == 201) {
        insert(sel_v);
    }
    else if (g == 202) {
        search(sel_k);
    }
    else if (g == 203) {
        Select(sel_k);
    }
    else if (g == 205){
        loadfile();
    }
    

    if (g >= 1 && g <= 5) {
        SelectPress(g - 1);
    }

   // if (g != -1) std::cout << g << "\n";
}

void TTFTree::SelectPress(int pos) {
    select.sel[pos].press ^= 1;
    if (select.sel[pos].press)
    for (int i = 0 ; i < 5 ; i++)
        if (i != pos) select.sel[i].press = 0;
}

void TTFTree::loadfile() {
    tft = TwoTFTree(LimitNode + 30);
    Animation.clear();
    std::vector<Transforms2> Anima(tft.Pos.size());
    tft.SetPostion();
    tft.GetUI(tft.root,Anima);
    Animation.push_back(Anima);

    std::ifstream fin;
    fin.open(pathfile);
    int n;
    fin >> n;
    n = std::min(n,50);
    for (int i = 0 ; i < n ; i++) {
        int x;
        fin >> x;
        tft.insert(x,Animation);
    //    avl.root = avl.Insert(avl.root,-1,0,x,Animation,// AnimationEdge);
    }

    Animation.erase(Animation.begin());

    fin.close();

    pause = 0;
    pos_ani = 0;
    LastTime = GetTime();
    TotalTime = 0;

    while (Unre.size() > 0 && Pos_unre + 1 < Unre.size()){
        Unre.pop_back();
        UnreAVL.pop_back();
    }

    Pos_unre++;

    Unre.push_back(Animation);
    TwoTFTree tft2 = tft;
    tft2.root = tft2.Save(tft2.root);
    UnreAVL.push_back(tft2);
}

void TTFTree::create(int n){
    tft = TwoTFTree(LimitNode + 30);
    Animation.clear();
    std::vector<Transforms2> Anima(tft.Pos.size());
    tft.SetPostion();
    tft.GetUI(tft.root,Anima);
    Animation.push_back(Anima);
    for (int i = 0 ; i < n ; i++) {
        int x = rng() % 100;
        tft.insert(x,Animation);
    }

    Animation.erase(Animation.begin());

    pause = 0;
    pos_ani = 0;
    LastTime = GetTime();
    TotalTime = 0;

    while (Unre.size() > 0 && Pos_unre + 1 < Unre.size()){
        Unre.pop_back();
        UnreAVL.pop_back();
    }

    Pos_unre++;

    Unre.push_back(Animation);
    TwoTFTree tft2 = tft;
    tft2.root = tft2.Save(tft2.root);
    UnreAVL.push_back(tft2);
}


void TTFTree::insert(int v){

    Animation.clear();
    std::vector<Transforms2> Anima(tft.Pos.size());
    tft.SetPostion();
    tft.GetUI(tft.root,Anima);
    Animation.push_back(Anima);
    tft.insert(v,Animation);
    Animation.erase(Animation.begin());
    pause = 0;
    pos_ani = 0;
    LastTime = GetTime();
    TotalTime = 0;

    while (Unre.size() > 0 && Pos_unre + 1 < Unre.size()){
        Unre.pop_back();
        UnreAVL.pop_back();
    }

    Pos_unre++;

    Unre.push_back(Animation);

    TwoTFTree tft2 = tft;
    tft2.root = tft2.Save(tft2.root);
    UnreAVL.push_back(tft2);
}

void TTFTree::search(int v){

    Animation.clear();
    std::vector<Transforms2> Anima(tft.Pos.size());
    tft.SetPostion();
    tft.GetUI(tft.root,Anima);
    Animation.push_back(Anima);
    tft.search(v,Animation);
    Animation.erase(Animation.begin());
    pause = 0;
    pos_ani = 0;
    LastTime = GetTime();
    TotalTime = 0;

    while (Unre.size() > 0 && Pos_unre + 1 < Unre.size()){
        Unre.pop_back();
        UnreAVL.pop_back();
    }

    Pos_unre++;

    Unre.push_back(Animation);

    TwoTFTree tft2 = tft;
    tft2.root = tft2.Save(tft2.root);
    UnreAVL.push_back(tft2);
}

void TTFTree::Select(int k){

  //  if (k > avl.GetSize()) return ;
    Animation.clear();
    // AnimationEdge.clear();


 //   avl.select(avl.root,-1,0,k,Animation,// AnimationEdge);
    pause = 0;
    pos_ani = 0;
    LastTime = GetTime();
    TotalTime = 0;

    while (Unre.size() > 0 && Pos_unre + 1 < Unre.size()){
        Unre.pop_back();
        UnreAVL.pop_back();
    }

    Pos_unre++;

    Unre.push_back(Animation);
    UnreAVL.push_back(tft);
}


void TTFTree::Notification(){

    if (!CheckNotification) return ;
    const char *message = "You have reached the node of the tree";
    float fontSize = 50.0f;
    float spacing = 2.0f;  
    Vector2 textSize = MeasureTextEx(customFont, message, fontSize, spacing);
    Vector2 position = {
        (GetScreenWidth() - textSize.x) / 2,
        (GetScreenHeight() - textSize.y) / 2 + 200
    };
    
    DrawTextEx(customFont, message, position, fontSize, spacing, ConstColor2);

    LastTime = GetTime();
}

