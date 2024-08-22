
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
            color = 1;
            colorE = 1;
            par = -1;
            Af = 255;
            AE = 255;
        }
    };

    struct Vertex2 {
        Vector2 Postion;
        float radius; 
        bool NotDeath;
        int leaf;
        Vertex2 *par;
        
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

        void insertNonFull(int k,key g) {
            int i = numKeys - 1;

            // Nếu là nút lá
            if (leaf) {
                // Dịch chuyển các phần tử lớn hơn để tìm vị trí chèn
                while (i >= 0 && keys[i].val > k) {
                    keys[i + 1] = keys[i];
                    childs[i + 1] = childs[i];
                    i--;
                }

                // Chèn phần tử vào vị trí tìm được
                keys[i + 1] = g;

                childs[i + 1] = nullptr;
                numKeys++;
            } else { // Nếu không phải nút lá
                // Tìm con phù hợp để di chuyển xuống
                while (i >= 0 && keys[i].val > k) {
                    i--;
                }

                // Kiểm tra xem con đã đầy hay chưa
                if (childs[i + 1]->numKeys == 3) {
                    // Tách con nếu nó đầy
                    splitChild(i + 1, childs[i + 1]);

                    // Sau khi tách, phần tử ở giữa di chuyển lên, cần kiểm tra lại
                    if (keys[i + 1].val < k) {
                        i++;
                    }
                }
                childs[i + 1]->insertNonFull(k,g);
            }
        }

    void splitChild(int i, Vertex2* y) {
            // Tạo một nút mới để chứa các phần tử lớn hơn của y
            Vertex2* z = new Vertex2(y->leaf);
            z->numKeys = 1;

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
            for (int j = numKeys; j >= i + 1; j--) {
                childs[j + 1] = childs[j];
            }

            // Liên kết z với nút hiện tại
            childs[i + 1] = z;

            // Dịch chuyển các phần tử của nút hiện tại để tạo chỗ cho phần tử giữa của y
            for (int j = numKeys - 1; j >= i; j--) {
                keys[j + 1] = keys[j];
            }

            // Đưa phần tử giữa của y lên nút hiện tại
            keys[i] = y->keys[1];
            numKeys++;
        }
    };

    struct Transforms2{
        key u,v;
        Transforms2() {}
        Transforms2(key u,key v): u(u), v(v) {}
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
            for (Vertex2 *v : u->childs) 
                d += CountKey(v);
            return d;
        }

        void Formard(Vertex2 *u) {
            // if (u == nullptr) return;
            // int d = u->keys.size();
            // std::sort(u->keys.begin(),u->keys.end(),[](key a, key b){
            //     return a.val < b.val;
            // });

            // for (key &v : u->keys) v.par = -1;

            // std::sort(u->childs.begin(),u->childs.end(),[](Vertex2 *a, Vertex2 *b){
            //     return a->keys[0].val < b->keys[0].val;
            // });

            // if (!u->childs.empty()) u->leaf = 0;

            // auto p = u->keys.begin();
            // int dd = 0;
            // for (Vertex2 *&v : u->childs)  {  
            //     Formard(v);
            //     if (p != u->keys.end() && p->val < v->keys[0].val){
            //         p++;
            //         dd++;
            //     }

            //     v->keys.front().par = dd;
            //     v-> par = u;
            // }
            // return;
        }

        float FindPostion(Vertex2* u,float t,float f,float h,float delh,float r) {
            if (u == nullptr) return 0;

           // std::cout << u->keys[0].val << '\n';
          //  if (u-> par != nullptr) std::cout << u->keys[0].val << " " << u->par->keys[0].val << "\n";
            float g = t;
            std::vector <float> k;
            for (Vertex2 *v : u->childs) {
                if (k.empty() && v->keys.front().par == u->childs.size()) g += r + f;
                g = FindPostion(v,g,f,h + delh,delh,r);
                k.push_back(g);
            }

           float mid = (std::max(g  - f - 2*r,t) + t) / 2.0;

            if (!u->childs.empty() && u->childs.front()->keys.front().par == 0) {
                mid = std::max(mid,k[0] - r - f );
            }

            std::cout << u->keys[0].val << "----- " << mid << " " << g << " " << t << ": "; 
            
            float m = u->keys.size() / 2.0;

            float left = mid - 1.0*(r*2 + 4)*((int)u->keys.size() - 1)/2.0;
            if (left < t) left = t;
            for (int i  = 0 ; i < u->keys.size() ; i++) {
                u->keys[i].Postion = {left,h};
                u->keys[i].radius = r;
                std::cout << u->keys[i].Postion.x << " ";
                left += (r*2 + 4);
            } 

            std::cout << left << "\n";

            return std::max(g,left + f - 4);
        }

        // void PostionEdge(Vertex2 * u) {
        //     if (u == nullptr) return ;

        //     for (Vertex2 * &v : u->childs) {
        //         float mid = (u->keys[0].Postion.x + u->keys.back().Postion.x) / 2.0;
        //         float mid2 = (v->keys[0].Postion.x + v->keys.back().Postion.x) / 2.0;
        //         key &x = v->keys.front();

        //         std::cout << x.val << " " << mid << " " << mid2 << "\n";
        //         if (x.par == 0) {
        //             x.PostionE = {mid2,x.Postion.y};
        //             x.PostionPar = {u->keys.front().Postion};
        //         }
        //         else if (x.par == u->keys.size()) {
        //             x.PostionE = {mid2,x.Postion.y};
        //             x.PostionPar = {u->keys.back().Postion};
        //         }
        //         else {
        //             x.PostionE = {mid2,x.Postion.y};
        //             x.PostionPar = {mid,u->keys.back().Postion.y};
        //         }

        //         PostionEdge(v);
        //     }
        // }

        void SetPostion() {
            Formard(root);
            float k = screenWidth - (FindPostion(root,0,40,100,70,21.4) - 40 - 2*21.4);
            FindPostion(root,k/2.0,40,100,70,21.4);
            PostionEdge(root);
        }

        void GetUI(Vertex2* u,std::vector<Transforms2> &Anima){
            if (u == nullptr) return ;
            for (key v : u->keys)
                Anima[v.pos].u = Anima[v.pos].v = v;
            for (Vertex2 *v : u->childs) {
                GetUI(v,Anima);
            }
        }


        void insert(int x) {

            key g;
            g.val = x;
            g.pos = find();
            Pos[g.pos] = 1;
            if (root->numKeys == 3) {
                Vertex2* s = new Vertex2(false);

                // Đưa root hiện tại thành con của nút mới
                s->childs[0] = root;

                // Tách root và di chuyển phần tử giữa lên nút mới
                s->splitChild(0, root);

                // Chọn con phù hợp để chèn phần tử mới
                int i = 0;
                if (s->keys[0].val < x) {
                    i++;
                }
                s->childs[i]->insertNonFull(x,g);

                // Thay đổi root
                root = s;
            } else {
                root->insertNonFull(x,g);
            }
        }
        
    };




    std::vector <std::vector<Transforms2> > Animation;
    std::vector <std::vector <std::vector<Transforms2> > > Unre; 
    std::vector <std::vector<TransformsEdge> > AnimationEdge;
    std::vector <std::vector <std::vector<TransformsEdge> > > UnreEdge; 
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