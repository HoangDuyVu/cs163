
#ifndef AVLTree_hpp
#define AVLTree_hpp
#include <raylib.h>
#include <variable.hpp>
#include <ViewInApp.hpp>
#include <activities.hpp>
#include <iostream>
#include <vector>

class AVLTree {

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
                    int n = rng() % (Limitnode + 1);
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
                    if (n > Limitnode) {
                    if (n == -1) n = 0;
                        n = Limitnode;
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
            char a[3];
            void init(Vector2 _postion){
                Postion = _postion;
                Item.resize(3);
                Rect = {184,Postion.y,200,40};
                Pointer_A.init({239,506},{3,16});
                a[0] = '0';
                a[1] = '\0';
                Item[0] = button_select({199,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/V.png"),WHITE);
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

        };

        struct SEARCH{
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
                Item[0] = button_select({199,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/V.png"),WHITE);
                Item[1] = button_select({285,Postion.y + 5},{30,30},1,LoadTexture("res/textures/select/Rand.png"),WHITE);
                Item[2] = button_select({331,Postion.y + 5},{42,29},1,LoadTexture("res/textures/select/OK.png"),WHITE);

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

                    int n = rng() % 100;
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

                    // if (n > LimitNode) {
                    //     n = std::max(0,LimitNode);
                    //     if (n < 9) {
                    //         a[0] = n + '0';
                    //         a[1] = '\0';
                    //     }
                    //     else {
                    //         a[0] = n/10 + '0';
                    //         a[1] = n % 10 + '0';
                    //         a[2] = '\0';
                    //     }
                    // }

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

        struct DELETE{
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
                Item[0] = button_select({199,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/K.png"),WHITE);
                Item[1] = button_select({285,Postion.y + 5},{30,30},1,LoadTexture("res/textures/select/Rand.png"),WHITE);
                Item[2] = button_select({331,Postion.y + 5},{42,29},1,LoadTexture("res/textures/select/OK.png"),WHITE);

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
                    int n = rng() % (LimitNode) + 1;
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

                    if (n > LimitNode) {
                        n = std::max(0,LimitNode);
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
            sel[3] = choose(Delete, Vector2 {27,656},Vector2 {150,40},"Select",ConstColor1,ConstColor2,0);
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

    struct Vertex2 {
        Vector2 Postion;
        float radius; 
        int Af;
        int color;
        int key;
        int left;
        int right;
        int parent;
        bool Notdeath;
        int height; 
        int f;
        int rank;
        int drawf;
        int drawbalance;
        int drawPostion;
        int drawrank;
        int balance;
        Vertex2() {
            Notdeath = 0;
        }

        Vertex2(Vector2 Postion,float radius, int color,int val,bool death,int height,int left,int right):
        Postion(Postion),
        radius(radius),
        color(color),
        key(val),
        Notdeath(death),
        height(height),
        left(left),
        right(right){}
    };

    struct Transforms2{
        Vertex2 u,v;
        Transforms2() {}
        Transforms2(Vertex2 u,Vertex2 v): u(u), v(v) {}
    };

    class BinaryTreeAVL{
    public:

        int capacity;
        int size;
        int root;
        std::vector<Vertex2> arr;

        BinaryTreeAVL(int cap = 0) {
            capacity = cap; 
            root = -1;
            size = 0;
            arr.resize(capacity);
        }

        int GetSize() {
            int d = 0;
            for (int i = 0 ; i < capacity ; i++) 
            if (arr[i].Notdeath) d++;
            return d;
        }

        int find(){
            for (int i = 0 ; i < capacity ; i++)
            if (!arr[i].Notdeath) return i;
            return -1;
        }

        int height(int id){
            if (id == -1) return 0;
            return arr[id].height;
        }

        int RightRotate(int id,int par,int pos,std::vector<std::vector<Transforms2> > &AnimationI,std::vector<std::vector <TransformsEdge> > &AnimationE) {

            std::vector<Transforms2> anima(capacity);
            std::vector<TransformsEdge> animaE(capacity);
            dfs(root,root,120,screenWidth - 120,100,60,anima,animaE);
            anima[id].u.color =  anima[id].v.color = 2;

            int x = arr[id].left;
            int T2 = arr[x].right;

            animaE[T2].v.PostionX = arr[id].Postion;
            AnimationI.push_back(anima);
            AnimationE.push_back(animaE);
            animaE[T2].u = animaE[T2].v;
            std::vector<Transforms2> Anima = anima;
            std::vector<TransformsEdge> AnimaE = animaE;

            arr[x].right = id;
            arr[id].left = T2;
            
            if (par == -1) {
                root = x;
            }
            else if (pos == 0) {
                arr[par].left = x;
            }
            else arr[par].right = x;

            dfs(root,root,120,screenWidth - 120,100,60,anima,animaE);

            for (int i = 0 ; i < capacity ; i++) {
                anima[i].u = Anima[i].v;
                animaE[i].u = AnimaE[i].v;
            }

            anima[id].u.color =  anima[id].v.color = 2;
            AnimationI.push_back(anima);
            AnimationE.push_back(animaE);

            for (int i = 0 ; i < capacity ; i++) {
                anima[i].u = anima[i].v;
                animaE[i].u = animaE[i].v;
            }

            anima[id].v.color = 2;
            anima[id].u.Af = 255;
            AnimationI.push_back(anima);
            AnimationE.push_back(animaE);

            arr[id].height = std::max(height(arr[id].left),height(arr[id].right)) + 1;
            arr[x].height =  std::max(height(arr[x].left),height(arr[x].right)) + 1;
            return x;
        }

        int LeftRotate(int id,int par,int pos,std::vector<std::vector<Transforms2> > &AnimationI,std::vector<std::vector <TransformsEdge> > &AnimationE) {
            
            std::vector<Transforms2> anima(capacity);
            std::vector<TransformsEdge> animaE(capacity);
            dfs(root,root,120,screenWidth - 120,100,60,anima,animaE);
            anima[id].u.color =  anima[id].v.color = 2;

            int x = arr[id].right;
            int T2 = arr[x].left;

            animaE[T2].v.PostionX = arr[id].Postion;
            AnimationI.push_back(anima);
            AnimationE.push_back(animaE);
            animaE[T2].u = animaE[T2].v;
            std::vector<Transforms2> Anima = anima;
            std::vector<TransformsEdge> AnimaE = animaE;

            arr[x].left = id;
            arr[id].right = T2;

            if (par == -1) {
                root = x;
            }
            else if (pos == 0) {
                arr[par].left = x;
            }
            else arr[par].right = x;

            dfs(root,root,120,screenWidth - 120,100,60,anima,animaE);

            for (int i = 0 ; i < capacity ; i++) {
                anima[i].u = Anima[i].v;
                animaE[i].u = AnimaE[i].v;
            }

            anima[id].u.color =  anima[id].v.color = 2;
            AnimationI.push_back(anima);
            AnimationE.push_back(animaE);

            for (int i = 0 ; i < capacity ; i++) {
                anima[i].u = anima[i].v;
                animaE[i].u = animaE[i].v;
            }

            anima[id].v.color = 2;
            anima[id].u.Af = 255;
            AnimationI.push_back(anima);
            AnimationE.push_back(animaE);


            arr[id].height = std::max(height(arr[id].left),height(arr[id].right)) + 1;
            arr[x].height =  std::max(height(arr[x].left),height(arr[x].right)) + 1;
            return x;
        }

        int GetBanlance(int id){
            return height(arr[id].left) - height(arr[id].right);
        }

        // x = 150  , y = 120 -> x += 80 , y += 80,

        int FindRight (int node,int par,int left,int high, int deltaHigh,int deltaLeft) {

            if (arr[node].left == -1) {
                arr[node].Postion = {(float)left,(float)high};
            }

            if (arr[node].left == -1 && arr[node].right == -1) return left;
            if (arr[node].left == -1) return FindRight(arr[node].right,node,left + deltaLeft,high + deltaHigh,deltaHigh,deltaLeft);

            int x = FindRight(arr[node].left,node,left,high + deltaHigh,deltaHigh,deltaLeft);
            arr[node].Postion = {(float) x + deltaLeft,(float) high};

            if (arr[node].right == -1) return x + deltaLeft;

            return FindRight(arr[node].right,node,x + 2*deltaLeft,high + deltaHigh,deltaHigh,deltaLeft);
        }

        void dfs(int id,int par,int l,int r,int h, int delta, std::vector<Transforms2> &g,std::vector <TransformsEdge> &f){


            //if (arr[id].Notdeath) std::cout << "id = " << id << "\n";
            arr[id].f = 1;
            if (id == -1){
                std::cout <<"coluontroi";
                return ;
            }


            Vertex2 &u = arr[id];
            u.Postion = {(float)((l + r) / 2.0),(float)h};
            u.balance = GetBanlance(id);

            if (u.left != -1) {
                arr[id].f += arr[u.left].f;
                dfs(u.left,id,l,(l + r)/2,h + delta,delta,g,f);
            }

            arr[id].rank = arr[id].f;
            if (u.right != - 1){
                arr[id].f += arr[u.right].f;
                dfs(u.right,id,(l + r)/2,r,h + delta,delta,g,f);
            }

            g[id].u = g[id].v = u;
            f[id].u = f[id].v = Edge(arr[par].Postion,u.Postion,u.Postion,0,id,255);
        }


        int Insert(int node,int par,int pos, int key,std::vector<std::vector<Transforms2> > &AnimationI,std::vector<std::vector <TransformsEdge> > &AnimationE) {

            std::vector<Transforms2> anima(capacity);
            std::vector<TransformsEdge> animaE(capacity);

            if (node == -1) {
                node = find();
                if (find() == -1) {
                    std::cout << "hetcuu\n";
                }

                arr[node] = Vertex2({0,0},15,0,key,1,1,-1,-1);
                arr[node].parent = par;
                arr[node].Af = 255;
                arr[node].drawf = 0;
                arr[node].drawPostion = 0;
                arr[node].drawrank = 0;
                arr[node].drawbalance = 0;

                if (par != -1 && par != node) {
                    if (pos == 0) arr[par].left = node;
                    else arr[par].right = node;
                }

                if (par == -1) root = node;

                dfs(root,root,120,screenWidth - 120,100,60,anima,animaE);
             //   std::cerr << root << " " << node << " " << arr[node].Postion.x  << " " << arr[node].Postion.y << "\n";
                anima[node].u.Af = 0;
                anima[node].v.color = 2;
                anima[node].u.color = 2;
                animaE[node].u.Af = 0;
                AnimationI.push_back(anima);
                AnimationE.push_back(animaE);


                for (int i = 0 ; i < capacity ; i++){
                    if (node != i){
                        if (arr[i].color == 1) anima[i].u.Af = 0;
                        anima[i].v.color = 0;
                    }

                    arr[i].color = 0;
                }

                animaE[node].u.Af = 255;
                anima[node].u = anima[node].v;

                AnimationI.push_back(anima);
                AnimationE.push_back(animaE);
                return node;
            }

            dfs(root,root,120,screenWidth - 120,100,60,anima,animaE);
            anima[node].u.Af = 0;
            anima[node].v.color = 1;
            arr[node].color = 1;
            for (int i = 0 ; i < capacity ; i++)
            if (arr[i].color != 0) {
                animaE[i].u.color = animaE[i].v.color = 1;
            }

            AnimationI.push_back(anima);
            AnimationE.push_back(animaE);

            anima[node].u = anima[node].v;

            if (key < arr[node].key) {

                animaE[arr[node].left].v.color = 1;
                AnimationI.push_back(anima);
                AnimationE.push_back(animaE);
                arr[node].left = Insert(arr[node].left,node,0,key,AnimationI,AnimationE);
            }
            else if (key > arr[node].key) {
                animaE[arr[node].right].v.color = 1;
                AnimationI.push_back(anima);
                AnimationE.push_back(animaE);
                arr[node].right = Insert(arr[node].right,node,1,key,AnimationI,AnimationE);
            }
            else{
                dfs(root,root,120,screenWidth - 120,100,60,anima,animaE);


                for (int i = 0 ; i < capacity ; i++){
                        if (arr[i].color == 1) anima[i].u.Af = 0;
                        anima[i].v.color = 0;
                    arr[i].color = 0;
                }

                animaE[node].u.Af = 255;
                anima[node].u = anima[node].v;

                AnimationI.push_back(anima);
                AnimationE.push_back(animaE);
                return node;
            }

            arr[node].height = std::max(height(arr[node].left),height(arr[node].right)) + 1;

            int Balance = GetBanlance(node);


            dfs(root,root,120,screenWidth - 120,100,60,anima,animaE);
            anima[node].v.color = 2;
            anima[node].u.Af = 0;
            anima[node].v.drawbalance = 1;
            AnimationI.push_back(anima);
            AnimationE.push_back(animaE);

            anima[node].u = anima[node].v;
            AnimationI.push_back(anima);
            AnimationE.push_back(animaE);

            if (Balance > 1 && key < arr[arr[node].left].key) {
                return RightRotate(node,par,pos,AnimationI,AnimationE);
            }

            if (Balance < -1 && key > arr[arr[node].right].key) {
                return LeftRotate(node,par,pos,AnimationI,AnimationE);
            }


            if (Balance > 1 && key > arr[arr[node].left].key) {
                arr[node].left = LeftRotate(arr[node].left,node,0,AnimationI,AnimationE);
                return  RightRotate(node,par,pos,AnimationI,AnimationE);
            }

            if (Balance < -1 && key < arr[arr[node].right].key) {
                arr[node].right = RightRotate(arr[node].right,node,1,AnimationI,AnimationE);
                return LeftRotate(node,par,pos,AnimationI,AnimationE);
            }

            return node;
        }

        void search(int node,int par,int pos, int key,std::vector<std::vector<Transforms2> > &AnimationI,std::vector<std::vector <TransformsEdge> > &AnimationE) {

            std::vector<Transforms2> anima(capacity);
            std::vector<TransformsEdge> animaE(capacity);

            if (node == -1) {

                dfs(root,root,120,screenWidth - 120,100,60,anima,animaE);


                for (int i = 0 ; i < capacity ; i++){
                        if (arr[i].color == 1) anima[i].u.Af = 0;
                        anima[i].v.color = 0;
                    arr[i].color = 0;
                }

                // animaE[node].u.Af = 255;
                // anima[node].u = anima[node].v;

                AnimationI.push_back(anima);
                AnimationE.push_back(animaE);
                return ;
            }

            dfs(root,root,120,screenWidth - 120,100,60,anima,animaE);
            arr[node].color = 1;
            for (int i = 0 ; i < capacity ; i++)
            if (arr[i].color != 0) {
                animaE[i].u.color = animaE[i].v.color = 1;
            }

            anima[node].v.color = 1;


            AnimationI.push_back(anima);
            AnimationE.push_back(animaE);

            for (int i = 0 ; i < capacity ; i++) 
            anima[i].u = anima[i].v;

            AnimationI.push_back(anima);
            AnimationE.push_back(animaE);

            if (key < arr[node].key) {
                animaE[arr[node].left].v.color = 1;
                AnimationI.push_back(anima);
                AnimationE.push_back(animaE);
                search(arr[node].left,node,0,key,AnimationI,AnimationE);
            }
            else if (key > arr[node].key) {
                animaE[arr[node].right].v.color = 1;
                AnimationI.push_back(anima);
                AnimationE.push_back(animaE);
                search(arr[node].right,node,1,key,AnimationI,AnimationE);
            }
            else {
                anima[node].u = anima[node].v;
                anima[node].u.Af = 0;
                anima[node].v.color = 2;
                AnimationI.push_back(anima);
                AnimationE.push_back(animaE);


                for (int i = 0 ; i < capacity ; i++){
                    arr[i].color = 0;
                }

                return ;
            }
        }


        void select(int node,int par,int pos, int k,std::vector<std::vector<Transforms2> > &AnimationI,std::vector<std::vector <TransformsEdge> > &AnimationE) {

            std::vector<Transforms2> anima(capacity);
            std::vector<TransformsEdge> animaE(capacity);

            dfs(root,root,120,screenWidth - 120,100,60,anima,animaE);
            arr[node].color = 1;

            for (int i = 0 ; i < capacity ; i++)
            if (arr[i].color != 0) {
                animaE[i].u.color = animaE[i].v.color = 1;
            }

            anima[node].u.Af = 0;
            anima[node].v.color = 1;
            anima[node].v.drawrank = 1;


            AnimationI.push_back(anima);
            AnimationE.push_back(animaE);

            for (int i = 0 ; i < capacity ; i++) 
            anima[i].u = anima[i].v;

            if (arr[node].left != -1) {
                anima[arr[node].left].v.drawf = 1;
                anima[arr[node].left].u.Af = 0;
                AnimationI.push_back(anima);
                AnimationE.push_back(animaE);
            }

            for (int i = 0 ; i < capacity ; i++) 
            anima[i].u = anima[i].v;

            AnimationI.push_back(anima);
            AnimationE.push_back(animaE);

            if (k == arr[node].rank)
            {
                anima[node].u = anima[node].v;
                anima[node].u.Af = 0;
                anima[node].v.color = 2;
                AnimationI.push_back(anima);
                AnimationE.push_back(animaE);


                for (int i = 0 ; i < capacity ; i++){
                    arr[i].color = 0;
                }

                return ;
            }
            else 
            if (k < arr[node].rank) {

                animaE[arr[node].left].v.color = 1;
                AnimationI.push_back(anima);
                AnimationE.push_back(animaE);

                select(arr[node].left,node,0,k,AnimationI,AnimationE);
            }
            else {
                animaE[arr[node].right].v.color = 1;
                AnimationI.push_back(anima);
                AnimationE.push_back(animaE);
                select(arr[node].right,node,0,k - arr[node].rank,AnimationI,AnimationE);
            }
        }
        
    };




    std::vector <std::vector<Transforms2> > Animation;
    std::vector <std::vector <std::vector<Transforms2> > > Unre; 
    std::vector <std::vector<TransformsEdge> > AnimationEdge;
    std::vector <std::vector <std::vector<TransformsEdge> > > UnreEdge; 
    std::vector<button_select> remote;
    std::vector <BinaryTreeAVL> UnreAVL;
    BinaryTreeAVL avl;
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
    void insert(int v);
    void search(int v);
    void Select(int k);
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