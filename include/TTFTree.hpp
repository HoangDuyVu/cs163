
#ifndef TTFTree_hpp
#define TTFTree_hpp
#include <raylib.h>
#include <variable.hpp>
#include <ViewInApp.hpp>
#include <activities.hpp>
#include <iostream>
#include <vector>
#include <map>

class TTFTree {

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
                    int n = rng() % (Limitnode + 30 + 1);
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
                    if (n > Limitnode + 30) {
                    if (n == -1) n = 0;
                        n = Limitnode + 30;
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

    struct key {
        Vector2 Postion;
        Vector2 PostionPar;
        Vector2 PostionE;
        int Af , AE;
        int color, colorE;
        int pos;
        int val;
        int par;
        int radius;
        int posVal;
        key(int _val = 0) {
            val = _val;
            color = 0;
            colorE = 0;
            par = -1;
            Af = 255;
            AE = 255;
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
        bool NotDeath;
        int leaf;
        int poss = 0;
        float midx;
        
        key keys[3];
        Vertex2* childs[4]; 
        int numKeys;   

        Vertex2(int _leaf = 0) {
            leaf = _leaf;
            NotDeath = 1;
            numKeys = 0;
            for (int i = 0 ; i < 4 ; i++) childs[i] = nullptr;
        }

        Vertex2(Vector2 Postion,float radius,bool NotDeath):
        Postion(Postion),
        radius(radius),
        NotDeath(NotDeath)
        {}
    };

    class TwoTFTree{
    public:

        int capacity;
        int size;
        Vertex2 *root;
        std::map<int,int> Pos;

        TwoTFTree(int cap = 0) {
            root = new Vertex2(1);
            Pos.clear();
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
            for (int i = 0 ; i < 3; i++) p->keys[i] = u->keys[i];
            for (int i = 0 ; i < 4; i++) p->childs[i] = u->childs[i];
            for (int i = 0 ; i < 4 ; i++) p->childs[i] = Save(p->childs[i]);
            return p;
        }

        float FindPostion(Vertex2* u,float t,float f,float h,float delh,float r) {
            if (u == nullptr) return 0;

            float g = t;
            float mid = -1;
            int dd = 0;
            for (int i = 0 ; i < u->numKeys ; i++) {
                Vertex2 *v = u->childs[i];
                if (v != nullptr) dd++;
                g = FindPostion(v,g,f,h+ delh,delh,r);
            }

            if (g == t) {
                mid = g;
                g += f + r;
            }

            Vertex2 *v = u->childs[u->numKeys];
            if (v != nullptr) dd++;
            g = FindPostion(v,g,f,h + delh,delh,r);

            if (dd == 1 && u->childs[0] != nullptr) {
                g += f + r;
                mid = g;
            }

            if (mid == -1)  mid = (std::max(g  - f - 2*r,t) + t) / 2.0;

            float m = u->numKeys / 2.0;
            float left = mid - 1.0*(r*2 + 4)*((int)u->numKeys - 1)/2.0;

            if (left < t) left = t;
            for (int i  = 0 ; i < u->numKeys ; i++) {
                u->keys[i].Postion = {left,h};
                u->keys[i].radius = r;
               // std::cout << u->keys[i].val << " " << u->keys->Postion.x << " " << u->keys->Postion.y << " " << u->keys->pos << "\n";
                left += (r*2 + 4);
            }

            return std::max(g,left + f - 4);
        }

        void PostionEdge(Vertex2 * u) {
            if (u == nullptr) return ;

            int k = u->numKeys;
            int poss = -1;
            for (int i = 0; i < k ; i++) if (u->keys[i].par != -1) poss = i;

            if (poss == -1) poss = 0;
            u->poss = poss;
            for (int i = 0 ; i <= k ; i++) PostionEdge(u->childs[i]);
            int d = 0;
            u->midx = (u->keys[0].Postion.x + u->keys[u->numKeys - 1].Postion.x) / 2.0;

            for (int d = 0 ; d <= k ; d++){
                if (u->childs[d] != nullptr && d != 0 && d != k){
                    int Pl = u->childs[d]->poss;
                    key &x = u->childs[d]->keys[Pl];
                    x.par = 0;
                    x.PostionE = {u->childs[d]->midx,x.Postion.y};
                    x.PostionPar = {u->midx,u->keys[0].Postion.y};
                }
                else if (u->childs[d] != nullptr && d == 0){
                    int Pl = u->childs[d]->poss;
                    key &x = u->childs[d]->keys[Pl];
                    x.par = 0;
                    x.PostionE = {u->childs[d]->midx,x.Postion.y};
                    x.PostionPar = u->keys[d].Postion;
                }
                else if (u->childs[d] != nullptr && d == k){
                    int Pl = u->childs[d]->poss;
                    key &x = u->childs[d]->keys[Pl];
                    x.par = 0;
                    x.PostionE = {u->childs[d]->midx,x.Postion.y};
                    x.PostionPar =  u->keys[d - 1].Postion;
                }
            }
            
        }

        void SetPostion() {
            float r = 21.4;
            float dis = 40;
            float k = 0;
            for (int i = r ; i >= 5 ; i--) {
                dis -= 3;
                r-= 0.6;
                k = screenWidth - (FindPostion(root,0,dis,150,100,r) - dis - 2*r);
                if (k > 30) break;
            }
            FindPostion(root,k/2.0,dis,150,100,r);
            PostionEdge(root);
        }

        void GetUI(Vertex2* u,std::vector<Transforms2> &Anima){
            if (u == nullptr) return ;
            int d = u->numKeys;
            for (int i = 0 ; i < d ; i++) {
                key v = u->keys[i];
                Anima[v.pos].u = Anima[v.pos].v = v;
            }
            for (int i = 0 ; i <= d ; i++) {
                GetUI(u->childs[i],Anima);
            }
        }

        void splitChild(int i,Vertex2* &u, Vertex2* y,std::vector <std::vector<Transforms2> > &Animation) {

                std::vector <Transforms2> Anima = Animation.back();
                for (Transforms2 &v : Anima) v.u = v.v;

                Anima[y->keys[1].pos].v.color = 2;
                Anima[y->keys[1].pos].u.Af = 0;
                Animation.push_back(Anima);
                // Tạo một nút mới để chứa các phần tử lớn hơn của y
                Vertex2* z = new Vertex2(y->leaf);
                z->numKeys = 1;

                for (Transforms2 &v : Anima) v.u = v.v;

                Anima[y->keys[0].pos].v.par = 1;
                Anima[y->keys[0].pos].v.colorE = 0;
                Anima[y->keys[0].pos].u.colorE = 0;
                Anima[y->keys[0].pos].v.PostionE =  Anima[y->keys[0].pos].v.Postion;
                Anima[y->keys[0].pos].u.PostionE = Anima[y->keys[0].pos].v.PostionE;
                Anima[y->keys[0].pos].v.PostionPar =  Anima[y->keys[1].pos].v.Postion;
                Anima[y->keys[0].pos].u.PostionPar = Anima[y->keys[0].pos].v.PostionPar;

                Anima[y->keys[2].pos].v.par = 1;
                Anima[y->keys[2].pos].v.colorE = 0;
                Anima[y->keys[2].pos].u.colorE = 0;
                Anima[y->keys[2].pos].v.PostionE =  Anima[y->keys[2].pos].v.Postion;
                Anima[y->keys[2].pos].u.PostionE = Anima[y->keys[2].pos].v.PostionE;
                Anima[y->keys[2].pos].v.PostionPar =  Anima[y->keys[1].pos].v.Postion;
                Anima[y->keys[2].pos].u.PostionPar = Anima[y->keys[2].pos].v.PostionPar;

                // Chuyển phần tử cuối cùng của y sang z
                z->keys[0] = y->keys[2];

                // Nếu y không phải là nút lá, chuyển các con của y sang z
                if (!y->leaf) {
                    for (int j = 0; j < 2; j++) {
                        z->childs[j] = y->childs[j + 2];
                        y->childs[j + 2] = nullptr;
                    }
                }

                y->numKeys = 1; // Giảm số lượng phần tử của y

                // Dịch chuyển các con của nút hiện tại để tạo chỗ cho z
                for (int j = u->numKeys; j >= i + 1; j--) {
                    u->childs[j + 1] = u->childs[j];
                }

                // Liên kết z với nút hiện tại
                u->childs[i + 1] = z;

                // Dịch chuyển các phần tử của nút hiện tại để tạo chỗ cho phần tử giữa của y
                for (int j = u->numKeys - 1; j >= i; j--) {
                    u->keys[j + 1] = u->keys[j];
                }

                // Đưa phần tử giữa của y lên nút hiện tại
                u->keys[i] = y->keys[1];
                u->keys[i].par = -1;
                u->numKeys++;

                if (root == y) root = u;
                SetPostion();


                std::vector<Transforms2> Ani(Anima.size());

                if (y == root)
                GetUI(u,Ani); else GetUI(root,Ani);

                for (int i = 0 ; i < Ani.size() ; i++){
                    Anima[i].v = Ani[i].v;
                    if (Anima[i].u.color == 2) Anima[i].v.color = 2;
                    if (Anima[i].u.color == 1) Anima[i].v.color = 1;
                    if (Anima[i].u.colorE == 1) Anima[i].v.colorE = 1;
                }
                
                Animation.push_back(Anima);
            }

        void insertNonFull(Vertex2 *u,int k,key g,std::vector <std::vector<Transforms2> > &Animation) {

            std::vector <Transforms2> Anima = Animation.back();
            for (Transforms2 &v : Anima){
                v.u = v.v;
                if (v.v.color == 2) v.v.color = 1;
            }

            for (int i = 0 ; i < u->numKeys ; i++) {
                int x = u->keys[i].pos;
                Anima[x].u.Af = 0;
                Anima[x].u.color = 0;
                Anima[x].v.color = 1;
            }

            Animation.push_back(Anima);

            int i = u->numKeys - 1;

            // Nếu là nút lá
            if (u->leaf) {
                // Dịch chuyển các phần tử lớn hơn để tìm vị trí chèn
                while (i >= 0 && u->keys[i].val > k) {
                    u->keys[i + 1] = u->keys[i];
                    u->childs[i + 1] = u->childs[i];
                    i--;
                }

                // Chèn phần tử vào vị trí tìm được
                u->keys[i + 1] = g;

                u->childs[i + 1] = nullptr;
                u->numKeys++;
            } else { // Nếu không phải nút lá
                // Tìm con phù hợp để di chuyển xuống
                while (i >= 0 && u->keys[i].val > k) {
                    i--;
                }

                Anima = Animation.back();
                for (Transforms2 &v : Anima) v.u = v.v;

                if (u->childs[i + 1] != nullptr) {
                    for (int p = 0 ; p < u->childs[i + 1]->numKeys ; p++)
                    if (u->childs[i + 1]->keys[p].par != -1) {
                        Anima[u->childs[i + 1]->keys[p].pos].v.colorE = 1;
                        break;
                    }
                    Animation.push_back(Anima);
                }

                // Kiểm tra xem con đã đầy hay chưa
                if (u->childs[i + 1]->numKeys == 3) {
                    // Tách con nếu nó đầy
                    splitChild(i + 1,u, u->childs[i + 1],Animation);

                    Anima = Animation.back();


                    for (Transforms2 &v : Anima){
                        v.u = v.v;
                        if (v.u.color == 2) {
                            v.v.color = 1;
                            v.u.Af = 0;
                        }
                    }

                    Animation.push_back(Anima);


                    // Sau khi tách, phần tử ở giữa di chuyển lên, cần kiểm tra lại
                    if (u->keys[i + 1].val < k) {
                        i++;
                    }

                    Anima = Animation.back();
                    for (Transforms2 &v : Anima) v.u = v.v;

                    if (u->childs[i + 1] != nullptr) {
                        for (int p = 0 ; p < u->childs[i + 1]->numKeys ; p++)
                        if (u->childs[i + 1]->keys[p].par != -1) {
                            Anima[u->childs[i + 1]->keys[p].pos].v.colorE = 1;
                            break;
                        }
                        Animation.push_back(Anima);
                    }
                }

                insertNonFull(u->childs[i + 1],k,g,Animation);
            }
        }


        void insert(int x,std::vector <std::vector<Transforms2> >  &Animation) {

            std::vector <Transforms2> Anima = Animation.back();
            for (Transforms2 &v : Anima) {
                v.u = v.v;
                v.v.color = 0;
                v.v.colorE = 0;
                v.u.AE = 0;

                if (v.v.color != v.u.color) v.u.Af = 0;
            }

            if (Animation.size() == 1) Animation.pop_back();
            Animation.push_back(Anima);

            key g;
            g.val = x;
            g.pos = find();
            Pos[g.pos] = 1;
            if (root->numKeys == 3) {

                for (int i = 0 ; i < 3 ; i++) {
                    int x = root->keys[i].pos;
                    Anima[x].u.Af = 0;
                    Anima[x].v.color = 1;
                    Anima[x].v.Af = 255;
                }

                Animation.push_back(Anima);

                Vertex2* s = new Vertex2(false);

                // Đưa root hiện tại thành con của nút mới
                s->childs[0] = root;

                // Tách root và di chuyển phần tử giữa lên nút mới
                splitChild(0,s, root,Animation);

                Anima = Animation.back();

                for (Transforms2 &v : Anima){
                    v.u = v.v;
                    if (v.u.color == 2) {
                        v.v.color = 1;
                        v.u.Af = 0;
                    }
                }

                Animation.push_back(Anima);

                

                // Chọn con phù hợp để chèn phần tử mới
                int i = 0;
                if (s->keys[0].val < x) {
                    i++;
                }

                Anima = Animation.back();
                for (Transforms2 &v : Anima) v.u = v.v;

                if (root->childs[i] != nullptr) {
                    for (int p = 0 ; p < root->childs[i]->numKeys ; p++)
                    if (root->childs[i]->keys[p].par != -1) {
                        Anima[root->childs[i]->keys[p].pos].v.colorE = 1;
                        break;
                    }
                    Animation.push_back(Anima);
                }
                insertNonFull(s->childs[i],x,g,Animation);

            } else {
                insertNonFull(root,x,g,Animation);
            }

            Anima = Animation.back();
            std::vector <Transforms2> Ani(Pos.size());
            SetPostion();
            GetUI(root,Ani);

            for (int i = 0 ; i < Anima.size(); i++) {
                Ani[i].u = Anima[i].v;
                Ani[i].v.colorE = Ani[i].u.colorE;
                Ani[i].v.color = Ani[i].u.color;
            }
            Ani[g.pos].u.color = 2;
            Ani[g.pos].u.Af = 0;
            Ani[g.pos].u.radius = 4;
            Ani[g.pos].v.color = 2; 
            Animation.push_back(Ani);

            for (Transforms2 &v : Ani){
                v.u = v.v;
                // if (v.u.color == 1) {
                //     v.u.Af = 0;
                //     v.v.color = 0;
                // }
            }

            Animation.push_back(Ani);
        }

        void search(int x,Vertex2* u,std::vector <std::vector<Transforms2> >  &Animation) {
            std::vector <Transforms2> Anima = Animation.back();
            for (Transforms2 &v : Anima){
                v.u = v.v;
                if (v.v.color == 2) v.v.color = 1;
            }

            for (int i = 0 ; i < u->numKeys ; i++) {
                int x = u->keys[i].pos;
                Anima[x].u.Af = 0;
                Anima[x].u.color = 0;
                Anima[x].v.color = 1;
            }

            Animation.push_back(Anima);

            int i = u->numKeys - 1;

            for (int j = 0 ; j <= i ; j++) 
            if (u->keys[j].val == x) {
                for (Transforms2 &v : Anima) v.u = v.v;
                Anima[u->keys[j].pos].v.color = 2;
                Anima[u->keys[j].pos].u.Af = 0;
                Animation.push_back(Anima);
                return ;
            }

            // Nếu là nút lá
            if (u->leaf) {
                Anima = Animation.back();
                for (Transforms2 &v : Anima){
                    v.u = v.v;
                    if (v.v.color != 0) {
                        v.v.color = 0;
                        v.u.Af = 0;
                    } 

                    if (v.v.colorE != 0) {
                        v.v.colorE = 0;
                        v.u.AE = 0;
                    }
                }

                Animation.push_back(Anima);
                return ;
            } else { // Nếu không phải nút lá
                // Tìm con phù hợp để di chuyển xuống
                while (i >= 0 && u->keys[i].val > x) {
                    i--;
                }

                Anima = Animation.back();
                for (Transforms2 &v : Anima) v.u = v.v;

                if (u->childs[i + 1] != nullptr) {
                    for (int p = 0 ; p < u->childs[i + 1]->numKeys ; p++)
                    if (u->childs[i + 1]->keys[p].par != -1) {
                        Anima[u->childs[i + 1]->keys[p].pos].v.colorE = 1;
                        break;
                    }
                    Animation.push_back(Anima);
                }


                search(x,u->childs[i + 1],Animation);
            }  
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