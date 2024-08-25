
#ifndef Graph_hpp
#define Graph_hpp
#include <raylib.h>
#include <variable.hpp>
#include <ViewInApp.hpp>
#include <activities.hpp>
#include <iostream>
#include <vector>
#include <map>

class Graph {

private:
    struct Select
    {
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
                Item[0] = button_select({199,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/N.png"),WHITE);
                Item[1] = button_select({285,Postion.y + 5},{30,30},1,LoadTexture("res/textures/select/Rand.png"),WHITE);
                Item[2] = button_select({331,Postion.y + 5},{42,29},1,LoadTexture("res/textures/select/OK.png"),WHITE);
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
                    int n = rng() % (Limitnode - 10 + 1);
                    if (n == -1) n = 0;

                    a[0] = n / 10 + '0';
                    a[1] = n % 10 + '0';
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
                    if (n > Limitnode - 10) {
                    if (n == -1) n = 0;
                        n = Limitnode - 10;
                        a[0] = n / 10 + '0';
                        a[1] = n % 10 + '0';
                        a[2] = '\0';

                        if (a[0] == '0') {
                            a[0] = a[1];
                            a[1] = '\0';
                        }
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

        };

        struct INSERT{
            Vector2 Postion;
            Rectangle Rect;
            Pointer Pointer_A;
            std::vector <button_select> Item;
            char a[10];
            void init(Vector2 _postion){
                Postion = _postion;
                Item.resize(3);
                Rect = {184,Postion.y,200 + 70,40};
                Pointer_A.init({239 + 35,506},{3,16});
                a[0] = '\0';
                Item[0] = button_select({199,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/S.png"),WHITE);
                Item[1] = button_select({285 + 70,Postion.y + 5},{30,30},1,LoadTexture("res/textures/select/Rand.png"),WHITE);
                Item[2] = button_select({331 + 70,Postion.y + 5},{42,29},1,LoadTexture("res/textures/select/OK.png"),WHITE);
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

                    int n = rng() % 6 + 1;

                    for (int i = 0 ; i < n ; i++) a[i] = rng() % 26 + 'a';
                    a[n] = '\0';

                }

                int key = GetCharPressed();
                while (key > 0) {
                    if ((((key >= 48) && (key <= 57)) || (key >= 'a' && key <= 'z')) && strlen(a) < 6) {
                        int len = strlen(a);
                        a[len] = (char) key;
                        a[len + 1] = '\0';
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
                    247,
                    Rec.y + (Rec.height - textSize.y) / 2
                };

                DrawTextEx(customFont, a, textPosition, fontSize, 1, WHITE);
                Pointer_A.Postion = {textPosition.x + textSize.x + 3,textPosition.y + 4};
                Pointer_A.DrawPointer();
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
                Item.resize(3);
                Rect = {184,Postion.y,200 + 70,40};
                Pointer_A.init({239 + 35,506},{3,16});
                a[0] = '\0';
                Item[0] = button_select({199,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/S.png"),WHITE);
                Item[1] = button_select({285 + 70,Postion.y + 5},{30,30},1,LoadTexture("res/textures/select/Rand.png"),WHITE);
                Item[2] = button_select({331 + 70,Postion.y + 5},{42,29},1,LoadTexture("res/textures/select/OK.png"),WHITE);

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

                if (Item[1].CheckPress(x,1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){

                    int n = rng() % 6 + 1;

                    for (int i = 0 ; i < n ; i++) a[i] = rng() % 26 + 'a';
                    a[n] = '\0';

                }

                int key = GetCharPressed();
                while (key > 0) {
                    if ((((key >= 48) && (key <= 57)) || (key >= 'a' && key <= 'z')) && strlen(a) < 6) {
                        int len = strlen(a);
                        a[len] = (char) key;
                        a[len + 1] = '\0';
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
                    247,
                    Rec.y + (Rec.height - textSize.y) / 2
                };

                DrawTextEx(customFont, a, textPosition, fontSize, 1, WHITE);
                Pointer_A.Postion = {textPosition.x + textSize.x + 3,textPosition.y + 4};
                Pointer_A.DrawPointer();
            }

        };

        struct DELETE{
            Vector2 Postion;
            Rectangle Rect;
            Pointer Pointer_A;
            std::vector <button_select> Item;
            char a[10];
            void init(Vector2 _postion){
                Postion = _postion;
                Item.resize(3);
                Rect = {184,Postion.y,200 + 70,40};
                Pointer_A.init({239 + 35,506},{3,16});
                a[0] = '\0';
                Item[0] = button_select({199,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/S.png"),WHITE);
                Item[1] = button_select({285 + 70,Postion.y + 5},{30,30},1,LoadTexture("res/textures/select/Rand.png"),WHITE);
                Item[2] = button_select({331 + 70,Postion.y + 5},{42,29},1,LoadTexture("res/textures/select/OK.png"),WHITE);

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

                if (Item[1].CheckPress(x,1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){

                    int n = rng() % 6 + 1;

                    for (int i = 0 ; i < n ; i++) a[i] = rng() % 26 + 'a';
                    a[n] = '\0';

                }

                int key = GetCharPressed();
                while (key > 0) {
                    if ((((key >= 48) && (key <= 57)) || (key >= 'a' && key <= 'z')) && strlen(a) < 6) {
                        int len = strlen(a);
                        a[len] = (char) key;
                        a[len + 1] = '\0';
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
                    247,
                    Rec.y + (Rec.height - textSize.y) / 2
                };

                DrawTextEx(customFont, a, textPosition, fontSize, 1, WHITE);
                Pointer_A.Postion = {textPosition.x + textSize.x + 3,textPosition.y + 4};
                Pointer_A.DrawPointer();
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
                Item[0] = button_select({199,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/I.png"),WHITE);
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
                    int n = rng() % (LimitNode + 1) - 1;
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
                    b[0] = rng() % 10 + '0';
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

                    if (n > LimitNode) {
                        n = std::max(0,LimitNode - 1);
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
            _insert.init({184,576});
            _search.init({184,616});
            _delete.init({184,656});
            _file.init({184,496});
           // _update.init({184,656});
            KIND = 1;
            Postion = {0,496};
            Close = LoadTexture("res/textures/select/CloseNew.png");
            Open  = LoadTexture("res/textures/select/OpenNew.png");
            Close.height /=4;
            Close.width /=4;
            Open.height /=4;
            Open.width /=4;
            Textr = Close;
            Size = {(float)Close.width,(float)Close.height};
            sel.resize(5);
            sel[0] = choose(Create, Vector2 {27,536},Vector2 {150,40},"Create",ConstColor1,ConstColor2,0);
            sel[1] = choose(Insert, Vector2 {27,576},Vector2 {150,40},"Insert",ConstColor1,ConstColor2,0);
            sel[2] = choose(Search, Vector2 {27,616},Vector2 {150,40},"Search",ConstColor1,ConstColor2,0);
            sel[3] = choose(Delete, Vector2 {27,656},Vector2 {150,40},"Delete",ConstColor1,ConstColor2,0);
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
        Vector2 PostionPar;
        Vector2 PostionE;
        int Af , AE;
        int color, colorE;
        int pos;
        char val;
        int par;
        int f;
        int end;
        int radius;
        int posVal;
        key(char _val = 0) {
            val = _val;
            color = 0;
            colorE = 0;
            par = -1;
            Af = 255;
            AE = 255;
            f = 0;
            end = 0;
            pos = -1;
        }
    };

    struct Transforms2{
        key u,v;
        Transforms2() {}
        Transforms2(key u,key v): u(u), v(v) {}
    };

    struct Vertex2 {
        Vector2 Postion;
        float radius; 
        bool death;
        int leaf;
        int poss = 0;
        float midx;
        
        key keys;
        std::vector <Vertex2*> childs; 
        int numKeys;   

        Vertex2(int val = 0) {
            keys = key(val);
            numKeys = 0;
            death = 0;
            childs.clear();
        }

        Vertex2(Vector2 Postion,float radius,bool death):
        Postion(Postion),
        radius(radius),
        death(death)
        {}
    };

    class TwoTFTree{
    public:

        int capacity;
        int size;
        Vertex2 *root;
        std::map<int,int> Pos;

        TwoTFTree(int cap = 0) {
            root = new Vertex2(-1);
            Pos.clear();
            root->keys.pos = find();
            Pos[root->keys.pos] = 1;
        }

        int find() {
            int u = 0;
            while (true) {
                if (Pos[u] == 0) {
                    return u;
                }
                u++;
            }
        }

        int CountKey(Vertex2 *u) {
            if (u == nullptr) return 0;
            int d = u->numKeys;
            for (int i = 0 ; i <= u->numKeys ; i++) 
                d += CountKey(u->childs[i]);
            return d;
        }

        Vertex2 *Save(Vertex2* u) {
            if (u == nullptr) return u;
            Vertex2* p = new Vertex2();
            p->leaf = u->leaf;
            p->numKeys = u->numKeys;
            p->keys = u->keys;
            p->childs = u->childs;
            for (int i = 0 ; i < p->childs.size() ; i++) p->childs[i] = Save(p->childs[i]);
            return p;
        }

        float FindPostion(Vertex2* u,float t,float f,float h,float delh,float r) {
            if (u == nullptr) return 0;

            float g = t;
            float mid = -1;
            int dd = 0;

            for (Vertex2 * v : u->childs) {
                g = FindPostion(v,g,f,h + delh,delh,r);
            }

            if (mid == -1)  mid = (std::max(g  - f - 2*r,t) + t) / 2.0;

            u->keys.Postion = {mid,h};
            u->keys.radius = r;
            if (u->keys.pos == 0) u->keys.Postion.y -= 50;

           // std::cout << u->keys.val << " " << 

            return std::max(g,mid + 3*r);
        }

        void PostionEdge(Vertex2 * u,Vertex2 * par) {
            if (u == nullptr) return ;

            if (par == nullptr) 
                u->keys.par = -1;
            else {
                u->keys.par = 1;
                u->keys.PostionE = u->keys.Postion;
                u->keys.PostionPar = par->keys.Postion;
            }
            for (Vertex2 *v : u->childs) 
                PostionEdge(v,u);

        }

        void SetPostion() {
            float r = 21.4;
            float dis = 40;
            float k = 0;
            for (int i = r ; i >= 5 ; i--) {
                dis -= 3;
                r-= 0.6;
                k = screenWidth - (FindPostion(root,0,dis,150,70,r) - dis - 2*r);
                if (k > 30) break;
            }

            std::cout << "-----\n";
            FindPostion(root,k/2.0,dis,150,70,r);
            PostionEdge(root,nullptr);
        }

        void GetUI(Vertex2* u,std::vector<Transforms2> &Anima){
            if (u == nullptr) return ;
            key v = u->keys;
            Anima[v.pos].u = Anima[v.pos].v = v;
            for (Vertex2* v : u->childs) 
            GetUI(v,Anima);
        }

        void IN(Vertex2 *u,int id,std::string &s,std::vector <std::vector<Transforms2> >  &Animation) {
            std::vector<Transforms2> Anima = Animation.back();
            for (Transforms2 & v : Anima) v.u = v.v;
            Anima[u->keys.pos].v.color = 1;
            Anima[u->keys.pos].u.Af = 1;
            Anima[u->keys.pos].v.f++;
            u->keys.f++;
            if (id == ((int)(s.size())) - 1){
                Anima[u->keys.pos].v.end++;
                u->keys.end++;
            }

            Animation.push_back(Anima);

            if (id == ((int)(s.size())) - 1) return ;

            Vertex2* k = nullptr;
            for (Vertex2* v : u->childs) if (v->keys.val == s[id + 1]) k = v;

            if (k == nullptr) {

                std::cout << s << "\n";
                Vertex2 *x = new Vertex2(s[id + 1]);
                x->keys.pos = find();
                Pos[x->keys.pos] = 1;
                u->childs.push_back(x);

                std::vector <Transforms2> Ani(Pos.size());
                SetPostion();
                GetUI(root,Ani);
                for (Transforms2 & v : Anima) v.u = v.v;
                for (int i = 0 ; i < Anima.size() ; i++) {
                    Ani[i].u = Anima[i].v;
                    Ani[i].v.color = Anima[i].v.color;
                    Ani[i].v.colorE = Anima[i].v.colorE;
                    Ani[i].v.Af = Anima[i].v.Af;
                    Ani[i].v.AE = Anima[i].v.AE;
                }
                
                int pos = x->keys.pos;
                Ani[pos].u.PostionE = Ani[pos].v.PostionPar;
                Ani[pos].u.PostionPar = Ani[pos].v.PostionPar;
             //   std::cout << u->keys.Postion.x << " " << u->keys.Postion.y << "\n";
                Ani[pos].u.colorE = Ani[pos].v.colorE = 1;
                Ani[pos].u.Postion = Ani[pos].v.Postion;
                Ani[pos].u.radius = Ani[pos].v.radius;
                Ani[pos].u.Af = 0, Ani[pos].v.color = 0;
                Animation.push_back(Ani);

                IN(x,id + 1,s,Animation);
            }
            else {
                Anima = Animation.back();
                for (Transforms2 & v : Anima) v.u = v.v;
                Anima[k->keys.pos].v.colorE = 1;
                Anima[k->keys.pos].u.colorE = 0;
                Animation.push_back(Anima);
                IN(k,id + 1,s,Animation);
            }

        }

        void SR(Vertex2 *u,int id,std::string &s,std::vector <std::vector<Transforms2> >  &Animation) {
            std::vector<Transforms2> Anima = Animation.back();
            for (Transforms2 & v : Anima) v.u = v.v;
            Anima[u->keys.pos].v.color = 1;
            Anima[u->keys.pos].u.Af = 1;
            if (id == ((int)(s.size())) - 1){
            //    std::cout << "co khong? :" << u->keys.end << "\n";
                if (u->keys.end) {
                    Anima[u->keys.pos].v.color = 2;
                }
            }

            Animation.push_back(Anima);

            if (id == ((int)(s.size())) - 1) return ;

            Vertex2* k = nullptr;
            for (Vertex2* v : u->childs) if (v->keys.val == s[id + 1]) k = v;

            if (k == nullptr) {
                return ;
            }
            else {
                Anima = Animation.back();
                for (Transforms2 & v : Anima) v.u = v.v;
                Anima[k->keys.pos].v.colorE = 1;
                Anima[k->keys.pos].u.colorE = 0;
                Animation.push_back(Anima);
                SR(k,id + 1,s,Animation);
            }

        }

        void insert(std::string x,std::vector <std::vector<Transforms2> >  &Animation) {
            std::vector<Transforms2> Anima = Animation.back();
            int d = 0;
            for (Transforms2 & v : Anima) {
                v.u = v.v;
                if (v.v.color != 0) {
                    v.v.color = 0;
                    d = 1;
                }
                if (v.v.colorE != 0) {
                    v.v.colorE = 0;
                    v.u.AE = 0;
                    d = 1;
                }
            }

            if (d == 1) Animation.push_back(Anima);
            IN(root,-1,x,Animation);
        }

        void search(std::string x,std::vector <std::vector<Transforms2> >  &Animation) {
            std::vector<Transforms2> Anima = Animation.back();
            int d = 0;
            for (Transforms2 & v : Anima) {
                v.u = v.v;
                if (v.v.color != 0) {
                    v.v.color = 0;
                    d = 1;
                }
                if (v.v.colorE != 0) {
                    v.v.colorE = 0;
                    v.u.AE = 0;
                    d = 1;
                }
            }

            std::cout << x << "\n";

            if (d == 1) Animation.push_back(Anima);
            SR(root,-1,x,Animation);
        }

        bool Del(Vertex2 *u,int id,std::string &s,std::vector <std::vector<Transforms2> >  &Animation) {
            std::vector<Transforms2> Anima = Animation.back();
            for (Transforms2 & v : Anima){
                v.u = v.v;
            }
            Anima[u->keys.pos].v.color = 1;
            Anima[u->keys.pos].u.Af = 1;
            if (id == ((int)(s.size())) - 1){
            //    std::cout << "co khong? :" << u->keys.end << "\n";
                if (u->keys.end) {
                    Anima[u->keys.pos].v.color = 2;
                }
            }

            Animation.push_back(Anima);

            if (id == ((int)(s.size())) - 1){

                if (u->keys.end > 0){
                    u->keys.end--;
                    if (u->keys.f-- == 1){
                        for (Transforms2 & v : Anima) v.u = v.v;   
                        int pos = u->keys.pos;
                        Anima[pos].v.end = 0;
                        Anima[pos].u.end = 0;
                        Anima[pos].v.Af = 0;
                        Anima[pos].v.PostionE = Anima[pos].v.PostionPar;
                        Animation.push_back(Anima);

                        Pos[pos] = 0;
                        u->keys.pos = -1;
                        Anima[pos].v.pos = -1;
                    } else {
                        for (Transforms2 & v : Anima) v.u = v.v;   
                        int pos = u->keys.pos;
                        Anima[pos].v.end--;
                        Anima[pos].u.end--;
                        Anima[pos].v.color = 0;
                        Anima[pos].u.Af = 0;
                        Anima[pos].v.colorE = 0;
                        Animation.push_back(Anima);    
                    }

                    return true;
                }
                else {
                    for (Transforms2 & v : Anima) v.u = v.v;   
                    int pos = u->keys.pos;
                    Anima[pos].v.color = 0;
                    Anima[pos].u.Af = 0;
                    Anima[pos].v.colorE = 0;
                    Animation.push_back(Anima);
                }
                return false;
            }

            Vertex2* k = nullptr;
            for (Vertex2* v : u->childs) if (v->keys.val == s[id + 1]) k = v;

            if (k == nullptr) {
                for (Transforms2 & v : Anima) v.u = v.v;   
                int pos = u->keys.pos;
                Anima[pos].v.color = 0;
                Anima[pos].u.Af = 0;
                Anima[pos].v.colorE = 0;
                Animation.push_back(Anima);
                return false;
            }
            else {
                Anima = Animation.back();
                for (Transforms2 & v : Anima) v.u = v.v;
                Anima[k->keys.pos].v.colorE = 1;
                Anima[k->keys.pos].u.colorE = 0;
                Animation.push_back(Anima);
                int g = Del(k,id + 1,s,Animation);
                Anima = Animation.back();
                if (g == 0) {
                    for (Transforms2 & v : Anima) v.u = v.v;   
                    int pos = u->keys.pos;
                    Anima[pos].v.color = 0;
                    Anima[pos].u.Af = 0;
                    Anima[pos].v.colorE = 0;
                    Animation.push_back(Anima);
                    return g;
                }

                if (Pos[k->keys.pos] == 0) {
                    auto p = u->childs.begin();
                    while ((*p) != k) p++; 
                    u->childs.erase(p);

                    std::vector<Transforms2> Ani(Anima.size());
                    SetPostion();
                    GetUI(root,Ani);
                    Anima = Animation.back();
                    for (Transforms2 & v : Anima) v.u = v.v;  
                    for (int i = 0 ; i < Ani.size() ; i++){
                        Anima[i].v.Postion = Ani[i].v.Postion;
                        Anima[i].v.PostionE = Ani[i].v.PostionE;
                        Anima[i].v.PostionPar = Ani[i].v.PostionPar;
                        Anima[i].v.radius = Ani[i].v.radius;
                    }
                    Animation.push_back(Anima);
                }

                if (u->keys.f-- == 1){
                    for (Transforms2 & v : Anima) v.u = v.v;   
                    int pos = u->keys.pos;
                    Anima[pos].v.Af = 0;
                    Anima[pos].v.PostionE = Anima[pos].v.PostionPar;
                    Animation.push_back(Anima);
                    Pos[pos] = 0;
                    u->keys.pos = -1;
                    Anima[pos].v.pos = -1;

                }
                else {
                    for (Transforms2 & v : Anima) v.u = v.v;   
                    int pos = u->keys.pos;
                    Anima[pos].v.color = 0;
                    Anima[pos].u.Af = 0;
                    Anima[pos].v.colorE = 0;
                    Animation.push_back(Anima);
                }

                return g;
            }

        }



        void Delete(std::string x,std::vector <std::vector<Transforms2> >  &Animation) {
            std::vector<Transforms2> Anima = Animation.back();
            int d = 0;
            for (Transforms2 & v : Anima) {
                v.u = v.v;
                if (v.v.color != 0) {
                    v.v.color = 0;
                    d = 1;
                }
                if (v.v.colorE != 0) {
                    v.v.colorE = 0;
                    v.u.AE = 0;
                    d = 1;
                }
            }

            std::cout << x << "\n";

            if (d == 1) Animation.push_back(Anima);
            Del(root,-1,x,Animation);
        }
    };




    std::vector <std::vector<Transforms2> > Animation;
    std::vector <std::vector <std::vector<Transforms2> > > Unre; 
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
    void DrawAnimation(std::vector<Transforms2> f,double g);
    void DrawAnimationEdge(std::vector<TransformsEdge> f,double g);
};

#endif 