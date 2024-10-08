
#ifndef Hashtable_hpp
#define Hashtable_hpp
#include <raylib.h>
#include <variable.hpp>
#include <ViewInApp.hpp>
#include <activities.hpp>
#include <iostream>
#include <vector>

class Hashtable {

private:
    struct Select
    {
        struct CREATE{
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
                Pointer_A.init({239,506 - 4*40},{3,16});
                Pointer_B.init({239 + 131,506 - 4*40},{3,16});
                a[0] = '0';
                a[1] = '\0';
                b[0] = '0';
                b[1] = '\0';
                Item[0] = button_select({199,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/N.png"),WHITE);
                Item[1] = button_select({285,Postion.y + 5},{30,30},1,LoadTexture("res/textures/select/Rand.png"),WHITE);
                Item[2] = button_select({131 + 331,Postion.y + 5},{42,29},1,LoadTexture("res/textures/select/OK.png"),WHITE);
                Item[3] = button_select({131 + 199,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/K.png"),WHITE);
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
                    int n = rng() % (13) + 5;
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
                 //  // std::cout << "co\n";

                    int key = GetCharPressed();
                    while (key > 0) {
                        if ((key >= 48) && (key <= 57) && strlen(a) < 2) {
                            int len = strlen(a);
                            a[len] = (char) key;
                            a[len + 1] = '\0';
                        }

                        int n = 0;
                        for (int i = 0 ; i < strlen(a); i++) n = n*10 + a[i] - '0';

                    if (n > 17) {
                        n = 17;
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
                  //  // std::cout << "coooo\n";

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
                   // // std::cout << "co\n";
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
                 //  // std::cout << "co\n";

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
                  //  // std::cout << "coooo\n";

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
                   // // std::cout << "co\n";
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

    struct Vertex2 {
        Vector2 Postion;
        float radius; 
        int Af;
        int color;
        int key;
        int pos;
        bool root;
        Vertex2() {
            root = 0;
        }

        Vertex2(Vector2 Postion,float radius, int color,int val,int Af):
        Postion(Postion),
        radius(radius),
        color(color),
        key(val),
        Af(Af){}
    };

    struct Transforms2{
        Vertex2 u,v;
        Transforms2() {}
        Transforms2(Vertex2 u,Vertex2 v): u(u), v(v) {}
    };

    class HashTable {

    public:
        int SizeN;
        int SizeM;
        int size;
        std::vector <std::vector<Vertex2> > arr;

        HashTable(int n = 0,int m = 0) {
            SizeN = n;
            SizeM = m;
            size = n;
            arr.resize(n);
            for (int i = 0 ; i < n ; i++){
                arr[i].push_back(Vertex2({0,0},20,0,i,255));
                arr[i][0].root = 1;
            }
        }

        void dfs(int l,int r, std::vector <Transforms2> &Anima,std::vector <TransformsEdge> &AnimaE) {
            float delta = 80;
            int left = ((l + r) / 2.0) - 1.0*delta*(SizeN - 1)/2.0;
            int d = SizeN;

            for (int i = 0 ; i < SizeN ; i++) {
                float postionx = left + i*delta;
                float postiony = 130;

                Vector2 lastPostion = {left + i*delta,130};
                int ok = 0;
                for (Vertex2 &v : arr[i]) {
                    v.Postion = {postionx,postiony};
                    if (ok != 0) v.pos = d++;
                    else v.pos = i;
                    if (v.root) postiony += 80;
                    else postiony += 60;

                    Anima[v.pos].u = Anima[v.pos].v = v;
                    AnimaE[v.pos].u = AnimaE[v.pos].v = Edge(lastPostion,v.Postion,{0,0},0,0,255);
                    lastPostion = v.Postion;
                    ok = 1;
                }
            }
        }

        void insert(int k,std::vector<std::vector<Transforms2> > &AnimationI,std::vector<std::vector <TransformsEdge> > &AnimationE) {
            int val = k;
            k = k % SizeN;
            if (arr[k].size() == SizeM) return ;

            std::vector <Transforms2> Anima(size);
            std::vector <TransformsEdge> AnimaE(size);
            dfs(200,1240,Anima,AnimaE);

            Anima[k].v.color = 1;
            Anima[k].u.Af = 0;
            AnimationI.push_back(Anima);
            AnimationE.push_back(AnimaE);                        

            Anima[k].u = Anima[k].v;
            arr[k].push_back(Vertex2({0,0},17,0,val,255));

            Anima.resize(size + 1);
            AnimaE.resize(size + 1);
            dfs(200,1240,Anima,AnimaE);
            Anima[k].v.color = 1;
            int z = arr[k][arr[k].size() - 1].pos;
            Anima[z].u.Af = 0;
            Anima[z].v.color = 2;
            AnimaE[z].u.Af = 0;
            AnimaE[z].v.Af = 255;
            AnimationI.push_back(Anima);
            AnimationE.push_back(AnimaE);   
            size++;

            for (Transforms2 v : Anima) {
                // std::cout << v.v.color << " " << v.u.color << "\n";
                // std::cout << v.v.Af << " " << v.u.Af << "\n";
                // std::cout << v.v.radius << " " << v.u.radius << "\n";
            }
        }

        void search(int k,std::vector<std::vector<Transforms2> > &AnimationI,std::vector<std::vector <TransformsEdge> > &AnimationE) {
            int val = k;
            k = k % SizeN;

            std::vector <Transforms2> Anima(size);
            std::vector <TransformsEdge> AnimaE(size);
            dfs(200,1240,Anima,AnimaE);

            Anima[k].v.color = 1;
            Anima[k].u.Af = 0;
            AnimationI.push_back(Anima);
            AnimationE.push_back(AnimaE);                        

            Anima[k].u = Anima[k].v; 

            int d = 0;
            for (Vertex2 &v : arr[k]) {
                d++;
                if (d == 1) continue;

                AnimaE[v.pos].v.Af = 0;
                AnimaE[v.pos].v.color = 1;
                AnimationI.push_back(Anima);
                AnimationE.push_back(AnimaE); 

                AnimaE[v.pos].u = AnimaE[v.pos].v;
                Anima[v.pos].v.color = 1;
                Anima[v.pos].u.Af = 0;
                AnimationI.push_back(Anima);
                AnimationE.push_back(AnimaE);  
                if (v.key == val) {
                    Anima[v.pos].u.color = 1;
                    Anima[v.pos].v.color = 2;
                    AnimationI.push_back(Anima);
                    AnimationE.push_back(AnimaE);  
                    return ;
                }

                Anima[v.pos].u = Anima[v.pos].v;

            }

            d = 0;
            for (Vertex2 &v : arr[k]) {
                d++;
                if (d == 1) continue;
                Anima[v.pos].v.color = 0;
                Anima[v.pos].u.Af = 1;
    
                AnimaE[v.pos].v.color = 0;
                AnimaE[v.pos].u.Af = 1;
            }

            AnimationI.push_back(Anima);
            AnimationE.push_back(AnimaE);  

            for (Transforms2 v : Anima) {
                // std::cout << v.v.color << " " << v.u.color << "\n";
                // std::cout << v.v.Af << " " << v.u.Af << "\n";
                // std::cout << v.v.radius << " " << v.u.radius << "\n";
            }
        }

        void Delete(int k,std::vector<std::vector<Transforms2> > &AnimationI,std::vector<std::vector <TransformsEdge> > &AnimationE) {
            int val = k;
            k = k % SizeN;

            std::vector <Transforms2> Anima(size);
            std::vector <TransformsEdge> AnimaE(size);
            dfs(200,1240,Anima,AnimaE);

            Anima[k].v.color = 1;
            Anima[k].u.Af = 0;
            AnimationI.push_back(Anima);
            AnimationE.push_back(AnimaE);                        

            Anima[k].u = Anima[k].v; 

            int d = 0;
            for (Vertex2 &v : arr[k]) {
                d++;
                if (d == 1) continue;

                AnimaE[v.pos].v.Af = 0;
                AnimaE[v.pos].v.color = 1;
                AnimationI.push_back(Anima);
                AnimationE.push_back(AnimaE); 

                AnimaE[v.pos].u = AnimaE[v.pos].v;
                Anima[v.pos].v.color = 1;
                Anima[v.pos].u.Af = 0;
                AnimationI.push_back(Anima);
                AnimationE.push_back(AnimaE);  
                if (v.key == val) {

                    Anima[v.pos].u.color = 1;
                    Anima[v.pos].v.color = 2;
                    AnimationI.push_back(Anima);
                    AnimationE.push_back(AnimaE); 

                    Anima[v.pos].u.color = 2;
                    Anima[v.pos].u.Af = 255;
                    Anima[v.pos].v.Af = 0;

                    int lastPos = v.pos;

                    for (int x = d; x < arr[k].size() ; x++) {
                        Vertex2 &A = arr[k][x];
                        Vertex2 &B = arr[k][x - 1];
                        lastPos = A.pos;
                        Anima[A.pos].v.Postion = B.Postion;

                        B = A;
                    }

                    AnimaE[lastPos].v.Af = 0;
                    AnimaE[lastPos].u.color = 0;
                    AnimaE[lastPos].v.color = 0;
                    AnimationI.push_back(Anima);
                    AnimationE.push_back(AnimaE);  

                    arr[k].pop_back();
                    size--;

                    return ;
                }

                Anima[v.pos].u = Anima[v.pos].v;

            }

            d = 0;
            for (Vertex2 &v : arr[k]) {
                d++;
                if (d == 1) continue;
                Anima[v.pos].v.color = 0;
                Anima[v.pos].u.Af = 1;
    
                AnimaE[v.pos].v.color = 0;
                AnimaE[v.pos].u.Af = 1;
            }

            AnimationI.push_back(Anima);
            AnimationE.push_back(AnimaE);  

            for (Transforms2 v : Anima) {
                // std::cout << v.v.color << " " << v.u.color << "\n";
                // std::cout << v.v.Af << " " << v.u.Af << "\n";
                // std::cout << v.v.radius << " " << v.u.radius << "\n";
            }
        }


    };




    std::vector <std::vector<Transforms2> > Animation;
    std::vector <std::vector <std::vector<Transforms2> > > Unre; 
    std::vector <std::vector<TransformsEdge> > AnimationEdge;
    std::vector <std::vector <std::vector<TransformsEdge> > > UnreEdge; 
    std::vector<button_select> remote;
    std::vector <HashTable> UnreHash;
    HashTable hashtable;
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
    void create(int n,int k);
    void insert(int v);
    void search(int v);
    void DElete(int k);
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