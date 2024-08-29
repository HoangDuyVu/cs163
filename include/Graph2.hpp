
#ifndef Graph2_hpp
#define Graph2_hpp
#include <raylib.h>
#include <variable.hpp>
#include <ViewInApp.hpp>
#include <activities.hpp>
#include <iostream>
#include <vector>
#include <map>

class Graph2 {

private:
    struct Select
    {
        struct CREATE{
            Vector2 Postion;
            Rectangle Rect,Rect2,Rect3;
            Pointer Pointer_A;
            std::vector <button_select> Item;
            char  a[100][100];
            int n = 0;
            void init(Vector2 _postion){
                Postion = _postion;
                Item.resize(3);
                Rect = {184,Postion.y,300,40};
                Rect2 = {184,Postion.y - 239 - 7,302,239};
                Rect3 = {184,Postion.y - 239 - 7,20,239};
                Pointer_A.init({223,214},{3,12});
                n = 0;
                a[0][0] = '\0';
                Item[0] = button_select({199,Postion.y + 12},{80,29},5,LoadTexture("res/textures/select/Matrix.png"),WHITE);
                Item[1] = button_select({384,Postion.y + 5},{30,30},1,LoadTexture("res/textures/select/Rand.png"),WHITE);
                Item[2] = button_select({433,Postion.y + 5},{42,29},1,LoadTexture("res/textures/select/OK.png"),WHITE);
            //  Item[0] = button_select({194,Postion.y + 5},{80,29},1,LoadTexture("res/textures/select/N.png"),WHITE);
                for (button_select &v : Item) {
                    v.image.height /=4;
                    v.image.width /=4;
                } 
            }

            void Draw(){

                Vector2 x = GetMousePosition();

                DrawRectangle(Rect.x,Rect.y,Rect.width,Rect.height,{139, 130, 252,255});
                DrawRectangle(Rect2.x,Rect2.y,Rect2.width,Rect2.height,{202, 198, 254,255});
                DrawRectangle(Rect3.x,Rect3.y,Rect3.width,Rect3.height,{63, 58, 123,255});
                int d = 1;
                for (button_select v: Item){
                    if (d == 0) {
                        d++;
                        const char kk[] = "Input a Matrix";
                        DrawTextEx(customFont,kk,v.Postion,25,1,WHITE);
                        //DrawTextEx()
                    }
                    else {
                        if (v.CheckMouse(x,1)) v.col = 1;
                        else v.col = 0;
                        v.DrawBasic(0.8f);
                    }
                }

                if (Item[1].CheckPress(x,1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                    n = rng() % 10;
                    int x = n + 1;
                    a[0][0] = x / 10 + '0';
                    a[0][1] = x % 10 + '0';
                    if (x < 10) {
                        a[0][0] = a[0][1];
                        a[0][1] = '\0';
                    }
                    else {
                        a[0][2] = '\0';
                    }

                    for (int i = 1 ; i <= n + 1 ; i++){
                        for (int j = 0 ; j <= n ; j++) {
                            int g = rng() % 4;
                            if (g < 1 && i != j + 1) {
                                a[i][2*j] = rng() % 10 + '0';
                                a[i][2*j + 1] = ' ';
                            }
                            else {
                                a[i][2*j] = 0 + '0';
                                a[i][2*j + 1] = ' ';
                            }
                        }

                        a[i][2*n + 1] = '\0';
                    }
                    n++;
                }

                int key = GetCharPressed();
                while (key > 0) {

                 //   std::cout << key << "\n";

                    if (key >= '0' && key <= '9'){
                        if (strlen(a[n]) >= 25) {
                            if (n < 10) {
                                n++;
                                a[n][0] = '\0';
                                a[n][strlen(a[n])] = key;
                                a[n][strlen(a[n])] = '\0';
                            }
                        }
                        else {
                            a[n][strlen(a[n])] = key;
                            a[n][strlen(a[n])] = '\0';
                        }
                    }
                    if ((key == 's' || key == KEY_ENTER) && n < 10) {
                   //  std::cout << "co\n";
                        n++;
                        a[n][0] = '\0';
                    }

                    if (key == KEY_SPACE) {
                        a[n][strlen(a[n])] = key;
                        a[n][strlen(a[n])] = '\0';
                    }
                    key = GetCharPressed();
                }

                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    if (strlen(a[n]) == 0) {
                        if (n != 0) {
                            n--;
                        }
                    }
                    else {
                        a[n][strlen(a[n]) - 1] = '\0';
                    }
                }

                int fontSize = 20;

                for (int i = 0 ; i <= n ; i++) {

                    Rectangle Rec = {212,Postion.y - 239 - 7 + (fontSize + 1)*i,42,29};
                    Vector2 textSize = MeasureTextEx(customFont, a[i], fontSize, 1);

                    Vector2 textPosition = {
                    212,
                    Rec.y + (Rec.height - textSize.y) / 2
                    };

                    Vector2 textPosition2 = {
                    189,
                    Rec.y + (Rec.height - textSize.y) / 2
                    };

                    char b[5];
                    b[0] = (i + '1');
                    if (b[0] > '9') b[0] -= 10;
                    b[1] = '\0';

                    DrawTextEx(customFont, a[i], textPosition, fontSize, 1, WHITE);
                    DrawTextEx(customFont,b,textPosition2,fontSize,1,Fade(WHITE,0.7));
                    Pointer_A.Postion = {textPosition.x + textSize.x + 3,textPosition.y + 4};
                }
                Pointer_A.DrawPointer();
            }

        };

        struct INSERT{
            Vector2 Postion;
            Rectangle Rect;
            std::vector <button_select> Item;
            char a[20];
            int check;
            void init(Vector2 _postion){
                Postion = _postion;
                Item.resize(3);
                Rect = {184,Postion.y,200 + 80,40};
                check = 0;
                a[0] = 'F';
                a[1] = 'i';
                a[2] = 'x';
                a[3] = 'e';
                a[4] = 'd';
                a[5] = ' ';
                a[6] = 'V';
                a[7] = 'e';
                a[8] = 'r';
                a[9] = 't';
                a[10] = 'e';
                a[11] = 'x';
                a[12] = 's';
                a[13] = ':';
                a[14] = ' ';
                a[15] = 'O';
                a[16] = 'F';
                a[17] = 'F';
                a[18] = '\0';
                Item[1] = button_select({285 + 85,Postion.y + 5},{30,30},1,LoadTexture("res/textures/select/Rand.png"),WHITE);
                Item[2] = button_select({331 + 82,Postion.y + 5},{42,29},1,LoadTexture("res/textures/select/OK.png"),WHITE);
            //  Item[0] = button_select({194,Postion.y + 5},{80,29},1,LoadTexture("res/textures/select/N.png"),WHITE);
                for (button_select &v : Item) {
                    v.image.height /=4;
                    v.image.width /=4;
                } 
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
                    check ^= 1;
                }

                if (check == 0) {
                    a[15] = 'O';
                    a[16] = 'F';
                    a[17] = 'F';
                    a[18] = '\0';
                } else {
                    a[15] = 'O';
                    a[16] = 'N';
                    a[17] = '\0';
                    a[18] = '\0';
                }
                


                Rectangle Rec = {211,Postion.y + 5,42,29};
                int fontSize = 20;

                Vector2 textSize = MeasureTextEx(customFont, a, fontSize, 1);

                Vector2 textPosition = {
                    200,
                    Rec.y + (Rec.height - textSize.y) / 2
                };

                DrawTextEx(customFont, a, textPosition, fontSize, 1, WHITE);
            }

        };

        struct SEARCH{
            Vector2 Postion;
            Rectangle Rect;
            Pointer Pointer_A;
            std::vector <button_select> Item;
            char a[8];
            void init(Vector2 _postion){
                Postion = _postion;
                Item.resize(1);
                Rect = {184,Postion.y, 62,40};
                Pointer_A.init({239 + 35,506},{3,16});
                a[0] = '\0';
               // Item[0] = button_select({199,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/S.png"),WHITE);
                //Item[1] = button_select({285 + 70,Postion.y + 5},{30,30},1,LoadTexture("res/textures/select/Rand.png"),WHITE);
                Item[0] = button_select({194,Postion.y + 5},{42,29},1,LoadTexture("res/textures/select/OK.png"),WHITE);

                for (button_select &v : Item) {
                    v.image.height /=4;
                    v.image.width /=4;
                } 
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

            }

        };

        struct DELETE{
            Vector2 Postion;
            Rectangle Rect;
            Pointer Pointer_A;
            std::vector <button_select> Item;
            char a[8];
            void init(Vector2 _postion){
                Postion = _postion;
                Item.resize(1);
                Rect = {184,Postion.y, 62,40};
                Pointer_A.init({239 + 35,546},{3,16});
                a[0] = '\0';
               // Item[0] = button_select({199,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/S.png"),WHITE);
                //Item[1] = button_select({285 + 70,Postion.y + 5},{30,30},1,LoadTexture("res/textures/select/Rand.png"),WHITE);
                Item[0] = button_select({194,Postion.y + 5},{42,29},1,LoadTexture("res/textures/select/OK.png"),WHITE);

                for (button_select &v : Item) {
                    v.image.height /=4;
                    v.image.width /=4;
                } 
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

            }

        };

        struct UPDATE{
            Vector2 Postion;
            Rectangle Rect;
            Pointer Pointer_A,Pointer_B;
            std::vector <button_select> Item;
            char a[3];
            char b[3];
            void init(Vector2 _postion){
                Postion = _postion;
                Item.resize(5);
                Rect = {184,Postion.y,131 + 200,40};
                Pointer_A.init({239,506},{3,16});
                Pointer_B.init({239 + 131,506},{3,16});
                a[0] = '0';
                a[1] = '\0';
                b[0] = '0';
                b[1] = '\0';
                Item[0] = button_select({199,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/N.png"),WHITE);
                Item[1] = button_select({285,Postion.y + 5},{30,30},1,LoadTexture("res/textures/select/Rand.png"),WHITE);
                Item[2] = button_select({131 + 331,Postion.y + 5},{42,29},1,LoadTexture("res/textures/select/OK.png"),WHITE);
                Item[3] = button_select({131 + 199,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/V.png"),WHITE);
                Item[4] = button_select({131 + 285,Postion.y + 5},{30,30},1,LoadTexture("res/textures/select/Rand.png"),WHITE);

                for (button_select &v : Item) {
                    v.image.height /=4;
                    v.image.width /=4;
                } 
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

                bool ggg = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

                if (Item[1].CheckPress(x,1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                    int n = rng() % 20 + 1;
                    if (n == -1) n = 0;

                    a[0] = n / 10 + '0';
                    a[1] = n % 10 + '0';
                    a[2] = '\0';

                    if (a[0] == '0') {
                        a[0] = a[1];
                        a[1] = '\0';
                    }
                }

                if (Item[4].CheckPress(x,1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                    b[0] = rng() % 4 + '0';
                    b[1] = rng() % 10 + '0';
                    b[2] = '\0';

                    if (b[0] == '0') {
                        b[0] = b[1];
                        b[1] = '\0';
                    }
                }

                if (ggg){
                    Item[0].CheckPress(x,1,1);
                    Item[3].CheckPress(x,1,1);
                }

                if (Item[0].press){
                 //  std::cout << "co\n";

                    int key = GetCharPressed();
                    while (key > 0) {
                        if ((key >= 48) && (key <= 57) && strlen(a) < 2) {
                            int len = strlen(a);
                            a[len] = (char) key;
                            a[len + 1] = '\0';
                        }

                        int n = 0;
                        for (int i = 0 ; i < strlen(a); i++) n = n*10 + a[i] - '0';

                    if (n > 40) {
                        n = std::max(0,40 - 1);
                        if (n < 9) {
                            a[0] = n + '0';
                            a[1] = '\0';
                        }
                        else {
                            a[0] = n/10 + '0';
                            a[1] = n % 10 + '0';
                            a[2] = '\0';
                        }
                    }

                        key = GetCharPressed();
                    }

                    if (IsKeyPressed(KEY_BACKSPACE))
                    {
                        int len = strlen(a);
                        if (len > 0) a[len - 1] = '\0';
                    }

                }

                if (Item[3].press){
                  //  std::cout << "coooo\n";

                    int key = GetCharPressed();
                    while (key > 0) {
                        if ((key >= 48) && (key <= 57) && strlen(b) < 2) {
                            int len = strlen(b);
                            b[len] = (char) key;
                            b[len + 1] = '\0';
                        }

                        int n = 0;
                        for (int i = 0 ; i < strlen(b); i++) n = n*10 + b[i] - '0';

                        key = GetCharPressed();
                    }

                    if (IsKeyPressed(KEY_BACKSPACE))
                    {
                        int len = strlen(b);
                        if (len > 0) b[len - 1] = '\0';
                    }

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
                if (Item[0].press){
                    Pointer_A.DrawPointer();
                   // std::cout << "co\n";
                }

                Rec = {131 + 231,Postion.y + 5,42,29};
                fontSize = 25;

                textSize = MeasureTextEx(customFont, b, fontSize, 1);

                textPosition = {
                    Rec.x + (Rec.width - textSize.x) / 2,
                    Rec.y + (Rec.height - textSize.y) / 2
                };

                DrawTextEx(customFont, b, textPosition, fontSize, 1, WHITE);
                Pointer_B.Postion = {textPosition.x + textSize.x + 3,textPosition.y + 4};
                if (Item[3].press) Pointer_B.DrawPointer();
            }

        };

        struct FILE{
            std::vector <button_select> Item;
            void init(Vector2 _postion){
                Item.resize(1);
                Item[0] = button_select({362,204},{708.5,400},0,LoadTexture("res/textures/select/dropp.png"),WHITE);
                Item[0].image.height /= 2;
                Item[0].image.width /= 2;
            }

            void Draw(){

                Vector2 x = GetMousePosition();
                for (button_select v: Item){
                    if (v.CheckMouse(x,1)) v.col = 1;
                    else v.col = 0;
                    v.DrawBasic(0.8f);
                }

                if (IsFileDropped()) {
                    Loadfile = 1;
                    FilePathList droppedFiles = LoadDroppedFiles();
                    TextCopy(pathfile,droppedFiles.paths[0]);
                    UnloadDroppedFiles(droppedFiles); 
                }
            }
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
            bool CheckMouse(Vector2 A,int k){
                return Postion.x <= A.x - k && Postion.x + Size.x >= A.x + k 
                    && Postion.y <= A.y - k && Postion.y + Size.y >= A.y + k;    
            }

            void Draw(){
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

            Kind DrawPress(){
                return kind;
            }
        
        };



        CREATE _create;
        INSERT _insert;
        SEARCH _search;
        DELETE _delete;
        UPDATE _update;
        FILE _file;
        std::vector <choose> sel;
        Texture2D Close;
        Texture2D Open;
        Texture2D Textr;
        Vector2 Postion,Size;
        int KIND;
        bool col;

        void init(){

            _create.init({184,536});
            _insert.init({184,456});
            _search.init({184,616});
            _delete.init({184,656});
            _file.init({184,496});
            _update.init({184,576});
            KIND = 1;
            Postion = {0,456};
            Close = LoadTexture("res/textures/select/Close.png");
            Open  = LoadTexture("res/textures/select/Open.png");
            Close.height /=4;
            Close.width /=4;
            Open.height /=4;
            Open.width /=4;
            Textr = Close;
            Size = {(float)Close.width,(float)Close.height};
            sel.resize(6);
            sel[0] = choose(Create, Vector2 {27,536},Vector2 {150,40},"Input",ConstColor1,ConstColor2,0);
            sel[1] = choose(Update, Vector2 {27,576},Vector2 {150,40},"Create",ConstColor1,ConstColor2,0);
            sel[2] = choose(Search, Vector2 {27,616},Vector2 {150,40},"Conected C",ConstColor1,ConstColor2,0);
            sel[3] = choose(Delete, Vector2 {27,656},Vector2 {150,40},"MST",ConstColor1,ConstColor2,0);
            sel[5] = choose(Insert, Vector2 {27,456},Vector2 {150,40},"Fixed",ConstColor1,ConstColor2,0);
            sel[4] = choose(file, Vector2 {27,496},Vector2 {150,40},"File",ConstColor1,ConstColor2,0);
        }

        bool CheckMouse(Vector2 A,int k){
            return Postion.x <= A.x - k && Postion.x + Size.x >= A.x + k 
                && Postion.y <= A.y - k && Postion.y + Size.y >= A.y + k;    
        }

        Texture2D getTexture(){
            if (!KIND) return Close;
            return Open;
        }

        void draw(){
            Vector2 x = GetMousePosition();
            float g = 1;
            if (CheckMouse(x,1)) g = 0.6f;
            DrawTextureV(getTexture(),Postion,Fade(WHITE,g));

            if (KIND == 1) {
                for (choose v : sel) {
                    v.Draw();
                    if (v.press) {
                        Kind kind = v.DrawPress();
                        if (kind == Create) _create.Draw();
                        if (kind == Insert) _insert.Draw();
                        if (kind == Search) _search.Draw();
                        if (kind == Delete) _delete.Draw();
                        if (kind == Update) _update.Draw();
                        if (kind == file)   _file.Draw();
                    }
                }
            }
        }

        int checkPressOn(bool Press);
    };

    struct key {
        Vector2 Postion;
        int Af; 
        int color;
        int val;
        int f;
        int pos;
        int con;
        Vector2 TotalF;

        key(int _val = 0) {
            Af = 255;
            val = _val;
            f = 0;
            color = 1;
            con = 0;
            if (val > 0) f = 1;
            TotalF = {0,0};
        }
    };

    struct egdeee {
        Vector2 PosX,PosY,PosMid;
        int Af; 
        int Ani;
        int color;
        int val;
        int pos;
        int f;
        int x , y;
        int print;
        egdeee() {
            Af = 0;
            val = 0;
            Ani = 0;
            f = 0;
            int x = 0;
            int y = 0;
            int print = 0;
        }
        egdeee(int _x,int _y,int _val) {
            Af = 255;
            val = _val;
            Ani = 0;
            color = 0;
            f = 1;
            x = _x;
            y = _y;
            print = 1;
            
        }
    };

    struct Transforms2{
        key u,v;
        Transforms2() {}
        Transforms2(key u,key v): u(u), v(v) {}
    };

    struct Transformse{
        egdeee u,v;
        Transformse() {}
        Transformse(egdeee u,egdeee v): u(u), v(v) {}
    };

    class TwoTFTree{
    public:

        int capacity;
        int size;
        Vector2 poscheck;
        std::vector <key> node;
        std::vector <std::vector<egdeee> > adj;
        std::vector <int> to;
        int Check;

        TwoTFTree(int cap = 0) {
            capacity = cap;
            node.clear();
            adj.clear();
            node.resize(cap + 4);
            adj.assign(cap + 4,(std::vector<egdeee>(cap + 4)));
            Check = 0;
        }

        Vector2 toVec(key A,key B) {
            return {B.Postion.x - A.Postion.x,B.Postion.y - A.Postion.y};
        }

        float dis(key A, key B) {
            Vector2 x = {B.Postion.x - A.Postion.x,B.Postion.y - A.Postion.y};
           // std::cout << x.x << " " << x.y << "\n";
            return std::max(sqrt(x.x*x.x + x.y*x.y),4.01f);
        }

        float dis3(Vector2 A) {
            Vector2 x = {A.x,A.y};
            return std::max(sqrt(x.x*x.x + x.y*x.y),4.01f);
        }

        float dis2(key A, key B){
            return dis(A,B)*dis(A,B);
        }

        Vector2 Nomal(key A,key B) {
            Vector2 g = toVec(A,B);
            return {g.x/dis3(g),g.y/dis3(g)};
        }


        void SetPostion() {

            for (int i = 1 ; i < capacity ; i++) node[i].TotalF = {0,0};
            for (int i = 1 ; i < capacity ; i++)
                for (int j = 1 ; j < capacity ; j++){
                    if (node[i].f == 0 || node[j].f == 0 || i == j) continue;
                {
                    
                    float g = (40000.0f/dis2(node[i],node[j]));
                    //std::cout << g << "\n";
                    Vector2 K = Nomal(node[i],node[j]);
                    K.x *= g;
                    K.y *= g;
                    node[i].TotalF.x -= K.x;
                    node[i].TotalF.y -= K.y;

                    node[j].TotalF.x += K.x;
                    node[j].TotalF.y += K.y;
                }

                if ((adj[i][j].f != 0 ||adj[j][i].f != 0) && node[i].f && node[j].f) {
                    float g2 = log(dis(node[i],node[j])/30.0f);
                    Vector2 K = Nomal(node[i],node[j]);
                    K.x *= g2;
                    K.y *= g2;
                //    std::cout << i << " " << j << " " << K.x << " " << K.y << "\n";
                    node[i].TotalF.x += K.x;
                    node[i].TotalF.y += K.y;

                    node[j].TotalF.x -= K.x;
                    node[j].TotalF.y -= K.y;
                }
                }

            for (int i = 1 ; i < capacity ; i++) 
                if (node[i].f) {
                    key Cen;
                    Cen.Postion = {(float)screenWidth/2,(float)screenHeight/2};
                    Vector2 K = toVec(node[i],Cen);
                    K.x *= 0.02f;
                    K.y *= 0.04f;
                    node[i].TotalF.x += K.x;
                    node[i].TotalF.y += K.y;
                }

            
            for (int i = 1 ; i < capacity ; i++)
                for (int j = 1 ; j < capacity ; j++) 
            if (node[i].f && node[j].f && (adj[i][j].f && adj[i][j].f) && i != j) {


                for (int z = 1 ; z < capacity ; z++)   
                if (node[z].f && z != i && z != j) {
                    Vector2 mid;
                    mid.x = (node[i].Postion.x + node[j].Postion.x)/2.0;
                    mid.y = (node[i].Postion.y + node[j].Postion.y)/2.0;

                    key Cen;
                    Cen.Postion = mid;

                    float g = (50.0f/(dis(node[z],Cen)*dis(node[z],Cen)));
                    Vector2 K = Nomal(node[z],Cen);
                    K.x *= g;
                    K.y *= g;

                    K.x /= 2.0;
                    K.y /= 2.0;
               //     std::cout << K.x << " " << K.y << "\n";

                    node[i].TotalF.x += K.x;
                    node[i].TotalF.y += K.y;

                    node[j].TotalF.x += K.x;
                    node[j].TotalF.y += K.y;

                    node[z].TotalF.x -= K.x*2;
                    node[z].TotalF.y -= K.y*2;
                }
            }

            float maxx = 0.0f;


            for(int i = 0; i < capacity; i++) if (node[i].f) {
                maxx = std::max(maxx, std::sqrt(node[i].TotalF.x * node[i].TotalF.x + node[i].TotalF.y * node[i].TotalF.y));
            }

            if(maxx < 0.1f) return;

            for (int i = 1 ; i < capacity ; i++) if (node[i].f) {
                node[i].TotalF.x *= 0.99f;
                node[i].TotalF.y *= 0.99f;

                node[i].Postion.x += node[i].TotalF.x;
                node[i].Postion.y += node[i].TotalF.y;
            }

            for (int i = 1 ; i < capacity ; i++)
                for (int j = 1 ; j < capacity ; j++) if (i!= j && node[i].f && node[j].f && adj[i][j].f){

                    int dd = 0;
                    if (i > j){
                        std::swap(i,j);
                        dd = 1;
                    }
                    Vector2 A = Nomal(node[i],node[j]);
                    std::swap(A.x,A.y);
                    A.x *= -1;
                    Vector2 mid;
                    mid.x = (node[i].Postion.x + node[j].Postion.x)/2.0;
                    mid.y = (node[i].Postion.y + node[j].Postion.y)/2.0;

                    mid.x += A.x*12;
                    mid.y += A.y*12;
                    if (dd == 1) std::swap(i,j);
                    adj[i][j].PosMid = mid;
                }
        }

        void Botton() {

            for (int i = 1 ; i < capacity ; i++) if (node[i].f)
                if (CheckCollisionPointCircle(GetMousePosition(),node[i].Postion,17) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                    Check = i; 
                    poscheck = GetMousePosition();
                    poscheck.x -= node[i].Postion.x;
                    poscheck.y -= node[i].Postion.y;
                //   std::cout << gtt << "\n";
                    break;
                }
            
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                Check = 0;
            }

            if (Check) {
                key &u = node[Check];
                Vector2 x = GetMousePosition();
                x.x -= u.Postion.x;
                x.y -= u.Postion.y;
                u.Postion.x += x.x - poscheck.x;
                u.Postion.y += x.y - poscheck.y;
            }
        }


        void GetUI(std::vector<Transforms2> &Ani,std::vector<Transformse> &AniE) {
            for (int i = 1 ; i <= capacity ; i++) {
                node[i].pos = i;
                Ani[i].u = Ani[i].v = node[i];
            }

            int d = 0;
            for (int i = 1 ; i <= capacity ; i++)
                for (int j = 1 ; j <= capacity ; j++) {
                    adj[i][j].pos = d;
                    AniE[d].u = AniE[d].v = adj[i][j];
                    d++; 
                }
        }

        void DFS(int u,int d,std::vector <std::vector<Transforms2> >  &Animation,std::vector <std::vector<Transformse> >  &AnimationE) {
            std::vector<Transforms2> Ani = Animation.back();
            std::vector<Transformse> AniE = AnimationE.back();
            for (Transforms2 &v : Ani) v.u = v.v;
            for (Transformse &v : AniE) v.u = v.v;

          //  std::cout << u << " " << d << "\n";

            node[u].con = d;
            Ani[u].v.color = d + 10;
            Ani[u].u.Af = 0;
            Animation.push_back(Ani);
            AnimationE.push_back(AniE);

            for (int i = 1 ; i < capacity ; i++) 
            if (node[i].f && (adj[u][i].f || adj[i][u].f)) {
                int pos = adj[u][i].pos;
                int pos2 = adj[i][u].pos;

                Ani = Animation.back();
                AniE = AnimationE.back();
                if (AniE[pos].v.Af == 0 || AniE[pos2].v.Af == 0 || AniE[pos2].v.Ani != 0 || AniE[pos].v.Ani != 0) continue;
                for (Transforms2 &v : Ani) v.u = v.v;
                for (Transformse &v : AniE) v.u = v.v;
                AniE[pos].v.color = d + 10;
                AniE[pos].v.Ani = 1;
                AniE[pos].v.print = 1;
                AniE[pos].u.print = 1;
                AniE[pos2].u.Af = 0;
                AniE[pos2].v.Af = 0;
                Animation.push_back(Ani);
                AnimationE.push_back(AniE);
                if (node[i].con == 0)
                DFS(i,d,Animation,AnimationE);
            }
        }

        void CC(std::vector <std::vector<Transforms2> >  &Animation,std::vector <std::vector<Transformse> >  &AnimationE) {
            int d = 0;
            std::vector<Transforms2> Ani = Animation.back();
            std::vector<Transformse> AniE = AnimationE.back();
            for (Transforms2 &v : Ani) v.u = v.v;
            for (Transformse &v : AniE) v.u = v.v;
            for (int i = 1 ; i < capacity ; i++) {
                if (!node[i].con && node[i].f) {
                    d++;
                    DFS(i,d,Animation,AnimationE);
                }
            }
        }

        int trace(int u) {
            if (to[u] != u) return to[u] = trace(to[u]);
            return u;
        }

        bool join(int x,int y){
            x = trace(x);
            y = trace(y);
            if (x == y) return false;
            to[x] = y;
            return true;
        }

        void MST(std::vector <std::vector<Transforms2> >  &Animation,std::vector <std::vector<Transformse> >  &AnimationE) {
            int d = 0;
            std::vector<Transforms2> Ani = Animation.back();
            std::vector<Transformse> AniE = AnimationE.back();
            std::vector <std::pair<int,int> > b;
            b.clear();
            to.resize(capacity + 1);

            for (int i = 1 ; i < capacity ; i++)
                for (int j = 1 ; j < capacity ; j++)
                if (adj[i][j].print && i != j && node[i].f && node[j].f && adj[i][j].f) {
                    b.push_back(std::make_pair(i,j));
                } 
            
            for (int i = 1 ; i < capacity ; i++) to[i] = i;

            std::sort(b.begin(),b.end(),[&](std::pair<int,int> x, std::pair<int,int> y){
                return adj[x.first][x.second].val <  adj[y.first][y.second].val;
            });

          //  std::cout << b.size() << "\n";

            for (std::pair<int,int> v : b) {
                int x = v.first;
                int y = v.second;
                for (Transforms2 &v : Ani) v.u = v.v;
                for (Transformse &v : AniE) v.u = v.v;
                Ani[x].v.color = 12;
                Ani[y].v.color = 12;
                Ani[x].u.Af = 0;
                Ani[y].u.Af = 0;
                AniE[adj[x][y].pos].v.color = 12;
                AniE[adj[x][y].pos].v.Ani = 1;
                Animation.push_back(Ani);
                AnimationE.push_back(AniE);
                if (join(x,y)) {
                    for (Transforms2 &v : Ani) v.u = v.v;
                    for (Transformse &v : AniE) v.u = v.v;
                    Ani[x].v.color = 2;
                    Ani[y].v.color = 2;
                    Ani[x].u.Af = 0;
                    Ani[y].u.Af = 0;
                    AniE[adj[x][y].pos].v.color = 1;
                    AniE[adj[x][y].pos].v.Ani = 0;
                    Animation.push_back(Ani);
                    AnimationE.push_back(AniE);
                }
                else {
                    for (Transforms2 &v : Ani) v.u = v.v;
                    for (Transformse &v : AniE) v.u = v.v;
                    Ani[x].v.color = 2;
                    Ani[y].v.color = 2;
                    Ani[x].u.Af = 0;
                    Ani[y].u.Af = 0;
                    AniE[adj[x][y].pos].v.Af = 0;
                    AniE[adj[x][y].pos].u.Ani = 0;
                    AniE[adj[x][y].pos].v.Ani = 0;
                    Animation.push_back(Ani);
                    AnimationE.push_back(AniE);        
                }
            }
        }



        void insert(std::string x,std::vector <std::vector<Transforms2> >  &Animation) {
        }

        void search(std::string x,std::vector <std::vector<Transforms2> >  &Animation) {
        }



        void Delete(std::string x,std::vector <std::vector<Transforms2> >  &Animation) {
        }
    };




    std::vector <std::vector<Transforms2> > Animation;
    std::vector <std::vector<Transformse> > Animatione;
    std::vector <std::vector <std::vector<Transforms2> > > Unre; 
    std::vector <std::vector <std::vector<Transformse> > > Unree; 
    std::vector<button_select> remote;
    std::vector <TwoTFTree> UnreAVL;
    TwoTFTree tft;
    Select select;
    double LastTime,NewTime,TotalTime;
    int pos_ani;
    button_select Persistent, NodePersistent;
    bool checkNodePer;
    int gtt;
    int pause;
    int Pos_unre;
    bool CheckNotification;
    double TimeNotification;


public:
    void create(int n);
    void insert(std::string s);
    void search(std::string v);
    void DElete(std::string v);
    void CC();
    void MST();
    void update();
    void loadfile();
    void init();
    void draw();
    void UpdatePostionNodePer();
    int UpdatePressOn();
    void Activity();
    void SelectPress(int pos);
    void SolveRemote();
    void Notification();
    Vector2 NewPos2D(Vector2 A,Vector2 B,float g);
    float NewPos1D(float x, float y, float g);
    void DrawAnimation(std::vector<Transforms2> f,std::vector<Transformse> k,double g);
    void DrawAnimationEdge(std::vector<TransformsEdge> f,double g);
};

#endif 