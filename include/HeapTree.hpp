
#ifndef HeapTree_hpp
#define HeapTree_hpp
#include <raylib.h>
#include <variable.hpp>
#include <ViewInApp.hpp>
#include <activities.hpp>
#include <iostream>
#include <vector>


class HeapTree {

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
                    a[0] = rng() % 3 + '0';
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
                    if (n > 30) {
                        a[0] = '3'; 
                        a[1] = '0';
                        a[2] = '\0';
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

        struct EXTRACT{
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
                Item[0] = button_select({199,Postion.y + 5},{80,29},0,LoadTexture("res/textures/select/I.png"),WHITE);
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
                    std::cout << "co\n";
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
        EXTRACT _extract;
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

            _create.init({184,496});
            _insert.init({184,536});
            _extract.init({184,576});
            _delete.init({184,616});
            _update.init({184,656});
            _file.init({184,456});
            KIND = 1;
            Postion = {0,457};
            Close = LoadTexture("res/textures/select/Open.png");
            Open  = LoadTexture("res/textures/select/close.png");
            Close.height /=4;
            Close.width /=4;
            Open.height /=4;
            Open.width /=4;
            Textr = Close;
            Size = {(float)Close.width,(float)Close.height};
            sel.resize(6);
            sel[0] = choose(Create, Vector2 {27,496},Vector2 {150,40},"Create",ConstColor1,ConstColor2,0);
            sel[1] = choose(Insert, Vector2 {27,536},Vector2 {150,40},"Insert",ConstColor1,ConstColor2,0);
            sel[2] = choose(Extract, Vector2 {27,576},Vector2 {150,40},"Extract",ConstColor1,ConstColor2,0);
            sel[3] = choose(Delete, Vector2 {27,616},Vector2 {150,40},"Delete",ConstColor1,ConstColor2,0);
            sel[4] = choose(Update, Vector2 {27,656},Vector2 {150,40},"Update",ConstColor1,ConstColor2,0);
            sel[5] = choose(file, Vector2 {27,456},Vector2 {150,40},"File",ConstColor1,ConstColor2,0);
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
                        if (kind == Extract) _extract.Draw();
                        if (kind == Delete) _delete.Draw();
                        if (kind == Update) _update.Draw();
                        if (kind == file)   _file.Draw();
                    }
                }
            }
        }

        int checkPressOn(bool Press);
    };


    std::vector <std::vector<Transforms> > Animation;
    std::vector <std::vector <std::vector<Transforms> > > Unre; 
    std::vector <std::vector<TransformsEdge> > AnimationEdge;
    std::vector <std::vector <std::vector<TransformsEdge> > > UnreEdge; 
    class BinaryHeap { 
    public:
        int capacity;
        int size;
        std::vector<Vertex> arr;



        BinaryHeap(int cap = 0) {
            capacity = cap; 
            size = 0;
            arr.resize(capacity);
        }

        int parent(int i) {
            return (i - 1) / 2;
        }

        int left(int i) {
            return 2 * i + 1;
        }

        int right(int i) {
            return 2 * i + 2;
        }

        void dfs(int id,int par,int l,int r,int h, int delta, std::vector<Transforms> &g,std::vector <TransformsEdge> &f){
            Vertex &u = arr[id];
            u.Postion = {(float)((l + r) / 2.0),(float)h};
            g[id].u = g[id].v = u;
            f[id].u = f[id].v = Edge(arr[par].Postion,u.Postion,u.Postion,0,id,255);

            if (left(id) < size) dfs(left(id),id,l,(l + r)/2,h + delta,delta,g,f);
            if (right(id) < size) dfs(right(id),id,(l + r)/2,r,h + delta,delta,g,f);
        }

        void Insert(int x,bool Ani,std::vector <std::vector<Transforms> > &AnimationI,std::vector <std::vector<TransformsEdge> > &AnimationEdgeI) {
            if (size == capacity) {
            std::cout << "Binary Heap Overflwon" << std::endl;
            return;
            }

          //  std::cout << "ggg\n";

            std::vector <Transforms> Anima; 
            std::vector <TransformsEdge> AnimaE;
            Anima.resize(size + 1);
            AnimaE.resize(size + 1);
            arr[size].val = x;
            arr[size].color = 0;
            arr[size].radius = 17;
            arr[size].Af = 255; 
            arr[size].Ani = 0;
            int k = size;
            size++;
          //  cout << Anima.size()
         //   return ;
            dfs(0,0,60,1380,140,80,Anima,AnimaE);

            Anima[k].u = Anima[k].v;
            Anima[k].u.Af = 0;
            AnimaE[k].u.Af = 0;
            Anima[k].u.color = 2;
            Anima[k].v.color = 2;
            AnimationI.push_back(Anima);
            AnimationEdgeI.push_back(AnimaE);

            AnimaE[k].u = AnimaE[k].v;
            Anima[k].u = Anima[k].v;
            AnimationI.push_back(Anima);
            AnimationEdgeI.push_back(AnimaE);

            while (k != 0 && arr[parent(k)].val > arr[k].val) {
                Anima[parent(k)].v.color = 1;
                Anima[parent(k)].u.Af = 0;
                Anima[k].u.color = 2;
                Anima[k].u.Af = 255;
                AnimaE[k].u.Af = 255;
                AnimationI.push_back(Anima);
                AnimationEdgeI.push_back(AnimaE);


                swap( & arr[parent(k)].val, & arr[k].val);

                std::swap(Anima[k].v.Postion,Anima[parent(k)].v.Postion);
                Anima[parent(k)].u.Af = 255;
                AnimationI.push_back(Anima);
                AnimationEdgeI.push_back(AnimaE);
                int OldK = k;
                k = parent(k);
                
                dfs(0,0,60,1380,140,80,Anima,AnimaE);
                Anima[k].v.color = 2;
                Anima[OldK].u.color = 1;
                Anima[OldK].u.Af = 0;
                Anima[OldK].v.Af = 255;
                AnimationI.push_back(Anima);
                AnimationEdgeI.push_back(AnimaE);

                AnimaE[k].u = AnimaE[k].v;
                Anima[k].u = Anima[k].v;
                AnimaE[OldK].u = AnimaE[OldK].v;
                Anima[OldK].u = Anima[OldK].v;
                AnimationI.push_back(Anima);
                AnimationEdgeI.push_back(AnimaE);
            }

            dfs(0,0,60,1380,140,80,Anima,AnimaE);
            Anima[k].u.Af = 0;
            Anima[k].u.color = 2;
            AnimationI.push_back(Anima);
            AnimationEdgeI.push_back(AnimaE);
        }

        void Heapify(int ind,std::vector <std::vector<Transforms> > &AnimationI,std::vector <std::vector<TransformsEdge> > &AnimationEdgeI) {

            std::vector <Transforms> Anima; 
            std::vector <TransformsEdge> AnimaE;
            Anima.resize(size);
            AnimaE.resize(size);
            dfs(0,0,60,1380,140,80,Anima,AnimaE);
            Anima[ind].v.color = 2;
            AnimationI.push_back(Anima);
            AnimationEdgeI.push_back(AnimaE);


            AnimaE[ind].u = AnimaE[ind].v;
            Anima[ind].u = Anima[ind].v;
            AnimationI.push_back(Anima);
            AnimationEdgeI.push_back(AnimaE);

            while (true) {
                int ri = right(ind); 
                int li = left(ind);
                int smallest = ind;
                if (li < size && arr[li].val < arr[smallest].val)
                smallest = li;
                if (ri < size && arr[ri].val < arr[smallest].val)
                smallest = ri;
                if (smallest != ind) {  
                    Anima[ind].u.color = 2;
                    Anima[smallest].u.Af = 0;
                    Anima[smallest].v.color = 1;

                    AnimationI.push_back(Anima);
                    AnimationEdgeI.push_back(AnimaE);

                    Anima[smallest].u.color = 1;
                    std::swap(Anima[ind].v.Postion,Anima[smallest].v.Postion);
                    Anima[smallest].u.Af = 255;
                    AnimationI.push_back(Anima);
                    AnimationEdgeI.push_back(AnimaE);

                    swap( & arr[ind].val, & arr[smallest].val);

                    int OldK = ind;
                    ind = smallest;
                    dfs(0,0,60,1380,140,80,Anima,AnimaE);
                    Anima[ind].u.color = 1;
                    Anima[ind].v.color = 2;

                    Anima[OldK].u.color = 1;
                    Anima[OldK].u.Af = 0;
                    Anima[OldK].v.Af = 255;

                    AnimationI.push_back(Anima);
                    AnimationEdgeI.push_back(AnimaE);

                    AnimaE[ind].u = AnimaE[ind].v;
                    Anima[ind].u = Anima[ind].v;
                    Anima[OldK].u = Anima[OldK].v;
                    AnimationI.push_back(Anima);
                    AnimationEdgeI.push_back(AnimaE);

                }
                else break;
            }

            dfs(0,0,60,1380,140,80,Anima,AnimaE);
            Anima[ind].u.Af = 0;
            Anima[ind].u.color = 2;
            AnimationI.push_back(Anima);
            AnimationEdgeI.push_back(AnimaE);
        }

        int getMin(std::vector <std::vector<Transforms> > &AnimationI,std::vector <std::vector<TransformsEdge> > &AnimationEdgeI) {
            return arr[0].val;
        }

        void ExtractMin(std::vector <std::vector<Transforms> > &AnimationI,std::vector <std::vector<TransformsEdge> > &AnimationEdgeI) {
            if (size == 0) return; 

            std::vector <Transforms> Anima; 
            std::vector <TransformsEdge> AnimaE;
            Anima.resize(size);
            AnimaE.resize(size);

            dfs(0,0,60,1380,140,80,Anima,AnimaE);


            Anima[0].v.color = 2;
            AnimationI.push_back(Anima);
            AnimationEdgeI.push_back(AnimaE);

            if (size == 1) {

                Anima[0].u = Anima[0].v;    
                Anima[0].v.Af = 0;
                AnimaE[0].v.Af = 0;
                AnimationI.push_back(Anima);
                AnimationEdgeI.push_back(AnimaE);
                size--; 
                return ;
            }

            Anima[0].u = Anima[0].v;      
            Anima[0].v.Af = 0;
            Anima[size - 1].v.color = 1;
            
            AnimationI.push_back(Anima);
            AnimationEdgeI.push_back(AnimaE);



            Anima[0].u.Af = 0;
            Anima[size - 1].u.color = 1;
            AnimaE[0].u = AnimaE[0].v;  
            AnimaE[size - 1].v.Af = 0;
            Anima[size - 1].v.Postion = Anima[0].u.Postion;
            AnimationI.push_back(Anima);
            AnimationEdgeI.push_back(AnimaE);


            arr[0] = arr[size - 1]; 
            size--;

            Anima.pop_back();
            AnimaE.pop_back();

            if (size == 0) {
            return;
            }
            Heapify(0,AnimationI,AnimationEdgeI); 
        }
        
        void Decreasekey(int i, int val) {
            arr[i].val = val; /*Updating the new_val*/
            while (i != 0 && arr[parent(i)].val > arr[i].val) /*Fixing the Min heap*/ {
            swap( & arr[parent(i)].val, & arr[i].val);
            i = parent(i);
            }
        }

        void Delete(int i,std::vector <std::vector<Transforms> > &AnimationI,std::vector <std::vector<TransformsEdge> > &AnimationEdgeI) {
            if (size == 0) return; 

            std::vector <Transforms> Anima; 
            std::vector <TransformsEdge> AnimaE;
            Anima.resize(size);
            AnimaE.resize(size);

            dfs(0,0,60,1380,140,80,Anima,AnimaE);
            Anima[i].v.color = 2;
            Anima[i].u.Af = 0;
            Anima[i].v.val = -1;

            AnimationI.push_back(Anima);
            AnimationEdgeI.push_back(AnimaE);

            arr[i].val = -1;

            int k = i;

            while (k != 0 && arr[parent(k)].val > arr[k].val) {
                Anima[parent(k)].v.color = 1;
                Anima[parent(k)].u.Af = 0;
                Anima[k].u.color = 2;
                Anima[k].u.Af = 255;
                AnimaE[k].u.Af = 255;
                AnimationI.push_back(Anima);
                AnimationEdgeI.push_back(AnimaE);
                swap( & arr[parent(k)].val, & arr[k].val);

                std::swap(Anima[k].v.Postion,Anima[parent(k)].v.Postion);
                Anima[parent(k)].u.Af = 255;
                AnimationI.push_back(Anima);
                AnimationEdgeI.push_back(AnimaE);
                k = parent(k);
                
                dfs(0,0,60,1380,140,80,Anima,AnimaE);
                Anima[k].v.color = 2;
                AnimationI.push_back(Anima);
                AnimationEdgeI.push_back(AnimaE);
            }
        }

        void Update(int i,int val,std::vector <std::vector<Transforms> > &AnimationI,std::vector <std::vector<TransformsEdge> > &AnimationEdgeI){
            if (size == 0) return; 

            std::vector <Transforms> Anima; 
            std::vector <TransformsEdge> AnimaE;
            Anima.resize(size);
            AnimaE.resize(size);

            dfs(0,0,60,1380,140,80,Anima,AnimaE);
            Anima[i].v.color = 2;
            Anima[i].u.Af = 0;
            Anima[i].v.val = val;

            AnimationI.push_back(Anima);
            AnimationEdgeI.push_back(AnimaE);

            arr[i].val = val;

            if (i != 0 && arr[parent(i)].val > val) {
                int k = i;

                while (k != 0 && arr[parent(k)].val > arr[k].val) {
                    Anima[parent(k)].v.color = 1;
                    Anima[parent(k)].u.Af = 0;
                    Anima[k].u.color = 2;
                    Anima[k].u.Af = 255;
                    AnimaE[k].u.Af = 255;
                    AnimationI.push_back(Anima);
                    AnimationEdgeI.push_back(AnimaE);
                    swap( & arr[parent(k)].val, & arr[k].val);

                    std::swap(Anima[k].v.Postion,Anima[parent(k)].v.Postion);
                    Anima[parent(k)].u.Af = 255;
                    AnimationI.push_back(Anima);
                    AnimationEdgeI.push_back(AnimaE);
                    k = parent(k);
                    
                    dfs(0,0,60,1380,140,80,Anima,AnimaE);
                    Anima[k].v.color = 2;
                    AnimationI.push_back(Anima);
                    AnimationEdgeI.push_back(AnimaE);
                }
            }
            else Heapify(i,AnimationI,AnimationEdgeI); 
        }
        // void Delete(int i) {
        //     Decreasekey(i, INT_MIN);
        //     ExtractMin();
        // }
        void swap(int * x, int * y) {
            int temp = * x;
            * x = * y;
            * y = temp;
        }
        void print() {
            for (int i = 0; i < size; i++)
            std::cout << arr[i].val << " ";
            std::cout << std::endl;
        }

        void DFS(int id,Vertex &u, int l, int r,int h ,int delta) {
            u.Postion = {(float)((l + r) / 2.0),(float)h};
            u.color = 0;
            u.kind_mouse = 0;
            u.radius = 17;
            u.Af = 255;

            if (left(id) < size) DFS(left(id),arr[left(id)],l,(l + r)/2,h + delta,delta);
            if (right(id) < size) DFS(right(id),arr[right(id)],(l + r)/2,r,h + delta,delta);
        }
    };

    std::vector<button_select> remote;
    std::vector <BinaryHeap> UnreHeap;
    BinaryHeap heap;
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
    void insert(int val);
    void ExtractMin(int k);
    void deletee(int i);
    void update(int i,int v);
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
    void DrawAnimation(std::vector<Transforms> f,double g);
    void DrawAnimationEdge(std::vector<TransformsEdge> f,double g);
};

#endif 