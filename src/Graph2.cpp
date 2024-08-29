#include <iostream>
#include <raylib.h>
#include <Graph2.hpp>
#include <variable.hpp>
#include <ViewInApp.hpp>
#include <activities.hpp>
#include <variable.hpp>
#include <random>
#include <fstream>


void Graph2::init(){
    tft = TwoTFTree(40);
    Animation.clear();
    Unre.clear();
    Unree.clear();
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

int Graph2::UpdatePressOn(){
    bool Press = 0;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) Press = 1;
    int res = viewapp.UpdatePressOn(Press);
    if (res != -1) return res;

    res = select.checkPressOn(Press);

    if (res != -1) return res;
    return -1;
}

Vector2 Graph2::NewPos2D(Vector2 A,Vector2 B,float g) {
    return {A.x + (B.x - A.x)*g,A.y + (B.y - A.y)*g};
}

float Graph2::NewPos1D(float x, float y, float g) {
    return x + (y - x)*g;
}

void Graph2::DrawAnimation(std::vector<Transforms2> f,std::vector<Transformse> k,double g){
    if (sel_check == 0) tft.SetPostion();

    for (Transformse v : k) if (v.u.f) {

        if (!v.u.print) continue;
        int NewA = (int) std::min((float)254.0,NewPos1D(v.u.Af,v.v.Af,g));
        NewA = std::max(NewA,0);
        int x = v.u.x;
        int y = v.u.y;
        if (NewA == 0) continue;

        DrawEdge(tft.node[x].Postion,tft.node[y].Postion,0,v.u.color,NewA);
        if (v.v.Ani == 1 && v.u.Ani != 1) {
            Vector2 NewPostion = NewPos2D(tft.node[x].Postion,tft.node[y].Postion,g);
            DrawEdge(tft.node[x].Postion,NewPostion,0,v.v.color,NewA);
        }

        if (v.v.color == 0) v.v.color = 10;
        if (v.v.color == 1) v.v.color = 11;
        DrawVertex(tft.adj[v.u.x][v.u.y].PosMid,13,v.v.val,v.v.color + 100,NewA);
    }


    for (Transforms2 v : f) if (v.u.f){
        int NewA = (int) std::min((float)254.0,NewPos1D(v.u.Af,v.v.Af,g));
        NewA = std::max(NewA,0);
    //    std::cout << v.u.pos << " " << NewA << " " << tft.node[v.v.pos].Postion.x << " " << tft.node[v.v.pos].Postion.y << "\n";
        if (v.v.color != v.u.color && NewA < 200)  DrawVertex(tft.node[v.v.pos].Postion,17,tft.node[v.v.pos].val,v.u.color,255);
        DrawVertex(tft.node[v.v.pos].Postion,17,tft.node[v.v.pos].val,v.v.color,NewA);
    }

     //           exit(0);

 //   for ()

}

void Graph2::UpdatePostionNodePer(){

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

void Graph2::SolveRemote(){

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
                    Animatione = Unree[Pos_unre];
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
                Animatione = Unree[Pos_unre];
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

void Graph2::draw(){
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
 
        DrawAnimation(Animation[pos_ani],Animatione[pos_ani],G);

        float TotalPer = Persistent.Size.x - NodePersistent.Size.x;
        float deltaPer = TotalPer/Animation.size();

        float PostFir = pos_ani*deltaPer + G*deltaPer;
        NodePersistent.Postion = {455 + PostFir,761};

    }
    else NodePersistent.Postion = {455,761};

    Persistent.DrawBasic(1.0f); 
    NodePersistent.DrawBasic(1.0f);

    float Speed = 0.25/deltaTime - 0.1f;
    char textBuffer[7];
    snprintf(textBuffer, sizeof(textBuffer), "%.1f", Speed);
    int Iz = strlen(textBuffer);
    textBuffer[Iz] = ' ';
    textBuffer[Iz + 1] = 'x';
    textBuffer[Iz + 2] = '\0';
    DrawTextEx(customFont,textBuffer,{1356,762},23,0,{220,249,243,255});

    select.draw();
}

int Graph2::Select::checkPressOn(bool Press){
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
                            for (int i = 0 ; _create.a[0][i] != '\0' ; i++) 
                            n = n*10 + _create.a[0][i] - '0';
                            sel_n = n;
                            adj.assign(n + 1,std::vector<int>(n + 1,0));
                            int d = 1 , m = 1;
                            int val = 0;
                            for (int i = 1 ; i <= n ; i++) {
                                _create.a[i][strlen(_create.a[i])] = ' ';
                                for (int j = 0 ; _create.a[i][j] != '\0' ; j++) {
                                    if (j != 0 && _create.a[i][j] == ' ' &&  _create.a[i][j - 1] != ' '){
                                        if (d <= n){
                                            adj[d][m] = val; 

                                          // std::cout << "d and m :" << d << " " << m << " " << adj[d][m] << "\n";
                                        }
                                        m++;
                                        if (m > n) {
                                            m = 1;
                                            d++;
                                        }
                                        val = 0;
                                    } else if (_create.a[i][j] != ' ') {
                                        val = val * 10 + _create.a[i][j] - '0';
                                    }
                                }
                            }
                            return 200;
                        } 

                        if (v.kind == Insert && _insert.Item[2].CheckPress(GetMousePosition(),1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                            v.press = 0;
                            KIND = 0;
                            sel_check = _insert.check;
                            return 300;
                        }

                        if (v.kind == Search && _search.Item[0].CheckPress(GetMousePosition(),1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                            v.press = 0;
                            KIND = 0;
                            return 202;
                        }

                        if (v.kind == Delete && _delete.Item[0].CheckPress(GetMousePosition(),1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                            v.press = 0;
                            KIND = 0;
                            return 203;
                        }
                        if (v.kind == Update && _update.Item[2].CheckPress(GetMousePosition(),1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                            v.press = 0;
                            KIND = 0;
                            int n = 0;
                            for (int i = 0 ; _update.a[i] != '\0' ; i++)
                                n = n * 10 + _update.a[i] - '0';
                            sel_n = n;

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

void Graph2::Activity(){

 //   LimitNode = avl.GetSize();
    tft.Botton();
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
        insert(sel_s);
    }
    else if (g == 202) {
        CC();
    }
    else if (g == 203) {
        MST();
    }
    else if (g == 204) {
        update();
    }
    else if (g == 205){
        loadfile();
    }
    

    if (g >= 1 && g <= 6) {
        SelectPress(g - 1);
    }

   // if (g != -1) std::cout << g << "\n";
}

void Graph2::SelectPress(int pos) {
    select.sel[pos].press ^= 1;
    if (select.sel[pos].press)
    for (int i = 0 ; i < 6 ; i++)
        if (i != pos) select.sel[i].press = 0;
}

void Graph2::loadfile() {
    tft = TwoTFTree(40);
    std::ifstream fin;
    fin.open(pathfile);
    fin >> sel_n;
    if (sel_n == 0) return ;
    for (int i = 1 ; i <= sel_n ; i++) {
        tft.node[i] = Graph2::key(i);
        tft.node[i].Postion = {(float)(rng() % screenWidth),(float)(rng() % screenHeight)};
       // std::cout << tft.node[i].f << "  " << tft.node[i].val << "\n";
    }

    for (int i = 1 ; i <= sel_n ; i++)
        for (int j = 1 ; j <= sel_n ; j++) {
            int x;
            fin >> x;

            if (i >= j) continue;

            if (x > 0) {
                tft.adj[i][j] =  Graph2::egdeee(i,j,x);
                tft.adj[j][i] =  Graph2::egdeee(j,i,x);
                tft.adj[j][i].print = 0;
            }
        }

    for (int i = 1 ; i <= sel_v ; i++) {
        int x = rng() % sel_n + 1;
        int y = rng() % sel_n + 1;
        while (x == y && sel_n > 1) {
                y = rng() % sel_n + 1;
        }

        int tt = rng() % 100;
        tft.adj[x][y] =  Graph2::egdeee(x,y,tt);
        tft.adj[y][x] =  Graph2::egdeee(y,x,tt);
        tft.adj[y][x].print = 0;
    }

    fin.close();
   // exit(0);

  //  std::cout << tft.node.size() << "\n";

    Animation.clear();
    Animatione.clear();

    std::vector<Transforms2> Ani(42);

    std::vector<Transformse> AniE(1600);
    tft.GetUI(Ani,AniE);
    Animation.push_back(Ani);
    Animatione.push_back(AniE);
    pause = 0;
    pos_ani = 0;
    LastTime = GetTime();
    TotalTime = 0;

    while (Unre.size() > 0 && Pos_unre + 1 < Unre.size()){
        Unre.pop_back();
        Unree.pop_back();
        UnreAVL.pop_back();
    }

    Pos_unre++;

    Unre.push_back(Animation);
    Unree.push_back(Animatione);
    TwoTFTree tft2 = tft;
    UnreAVL.push_back(tft2);

}

void Graph2::create(int n){
    tft = TwoTFTree(40);

    for (int i = 1 ; i <= sel_n ; i++) {
        tft.node[i] = Graph2::key(i);
        tft.node[i].Postion = {(float)(rng() % screenWidth),(float)(rng() % screenHeight)};
       // std::cout << tft.node[i].f << "  " << tft.node[i].val << "\n";
    }


    for (int i = 1 ; i <= sel_n ; i++)
        for (int j = i + 1 ; j <= sel_n ; j++) {
            if (adj[i][j] > 0) {
              //  std::cout << i << " " << j << " " <<  adj[i][j] << "\n";
                tft.adj[i][j] = Graph2::egdeee(i,j,adj[i][j]);
                tft.adj[j][i] = Graph2::egdeee(j,i,adj[i][j]);
                tft.adj[j][i].print = 0;
            }
            else tft.adj[i][j].f = 0;
        }
   // exit(0);

   // std::cout << tft.node.size() << "\n";

    Animation.clear();
    Animatione.clear();

    std::vector<Transforms2> Ani(42);

    std::vector<Transformse> AniE(1600);
    tft.GetUI(Ani,AniE);
    Animation.push_back(Ani);
    Animatione.push_back(AniE);

    pause = 0;
    pos_ani = 0;
    LastTime = GetTime();
    TotalTime = 0;

    while (Unre.size() > 0 && Pos_unre + 1 < Unre.size()){
        Unre.pop_back();
        Unree.pop_back();
        UnreAVL.pop_back();
    }

    Pos_unre++;

    Unre.push_back(Animation);
    Unree.push_back(Animatione);
    TwoTFTree tft2 = tft;
    UnreAVL.push_back(tft2);
}

void Graph2::update(){

    tft = TwoTFTree(40);
    if (sel_n == 0) return ;
    for (int i = 1 ; i <= sel_n ; i++) {
        tft.node[i] = Graph2::key(i);
        tft.node[i].Postion = {(float)(rng() % screenWidth),(float)(rng() % screenHeight)};
       // std::cout << tft.node[i].f << "  " << tft.node[i].val << "\n";
    }

    for (int i = 1 ; i <= sel_v ; i++) {
        int x = rng() % sel_n + 1;
        int y = rng() % sel_n + 1;
        while (x == y && sel_n > 1) {
                y = rng() % sel_n + 1;
        }

        int tt = rng() % 100;
        tft.adj[x][y] =  Graph2::egdeee(x,y,tt);
        tft.adj[y][x] =  Graph2::egdeee(y,x,tt);
        tft.adj[y][x].print = 0;
    }
   // exit(0);

  //  std::cout << tft.node.size() << "\n";

    Animation.clear();
    Animatione.clear();

    std::vector<Transforms2> Ani(42);

    std::vector<Transformse> AniE(1600);
    tft.GetUI(Ani,AniE);
    Animation.push_back(Ani);
    Animatione.push_back(AniE);
    pause = 0;
    pos_ani = 0;
    LastTime = GetTime();
    TotalTime = 0;

    while (Unre.size() > 0 && Pos_unre + 1 < Unre.size()){
        Unre.pop_back();
        Unree.pop_back();
        UnreAVL.pop_back();
    }

    Pos_unre++;

    Unre.push_back(Animation);
    Unree.push_back(Animatione);
    TwoTFTree tft2 = tft;
    UnreAVL.push_back(tft2);
}

void Graph2::CC(){
    if (sel_n == 0) return ;

    Animation.clear();
    Animatione.clear();

    std::vector<Transforms2> Ani(42);
    std::vector<Transformse> AniE(1600);

    for (int i = 0 ; i < tft.capacity ; i++) tft.node[i].con = 0;
    tft.GetUI(Ani,AniE);
    for (Transforms2 &v : Ani) {
        v.v.color = 0;
        v.u.Af = 0;
    }
    Animation.push_back(Ani);
    Animatione.push_back(AniE);

    tft.CC(Animation,Animatione);

    pause = 0;
    pos_ani = 0;
    LastTime = GetTime();
    TotalTime = 0;

    while (Unre.size() > 0 && Pos_unre + 1 < Unre.size()){
        Unre.pop_back();
        Unree.pop_back();
        UnreAVL.pop_back();
    }

    Pos_unre++;

    Unre.push_back(Animation);
    Unree.push_back(Animatione);
    TwoTFTree tft2 = tft;
    UnreAVL.push_back(tft2);
}

void Graph2::MST(){
    if (sel_n == 0) return ;

    Animation.clear();
    Animatione.clear();

    std::vector<Transforms2> Ani(42);
    std::vector<Transformse> AniE(1600);

    for (int i = 0 ; i < tft.capacity ; i++) tft.node[i].con = 0;
    tft.GetUI(Ani,AniE);
    for (Transforms2 &v : Ani) {
        v.v.color = 0;
        v.u.Af = 0;
    }
    Animation.push_back(Ani);
    Animatione.push_back(AniE);

    tft.MST(Animation,Animatione);

    pause = 0;
    pos_ani = 0;
    LastTime = GetTime();
    TotalTime = 0;

    while (Unre.size() > 0 && Pos_unre + 1 < Unre.size()){
        Unre.pop_back();
        Unree.pop_back();
        UnreAVL.pop_back();
    }

    Pos_unre++;

    Unre.push_back(Animation);
    Unree.push_back(Animatione);
    TwoTFTree tft2 = tft;
    UnreAVL.push_back(tft2);
}

void Graph2::insert(std::string s){
    Animation.clear();
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
    UnreAVL.push_back(tft2);
 }

 void Graph2::search(std::string v){
    Animation.clear();
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
    UnreAVL.push_back(tft2);
}

void Graph2::DElete(std::string v){
    Animation.clear();

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
    UnreAVL.push_back(tft2);
}



void Graph2::Notification(){

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

