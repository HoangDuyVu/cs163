//
//  node.hpp
//  hahaaa
//
//  Created by Aquafjna on 22/7/24.
//

#ifndef node_hpp
#define node_hpp

#include <iostream>
#include <stdio.h>
#include <raylib.h>

class node {

private:
    Vector2 postion;
    float radius;
    Vector2 size;
    Color color;
    char *text;
    Font font;
    Texture2D texture;
    bool mouse;
    enum Shape{
        RECT,
        CIRCLE
    };
    
    Shape shape;
    
public:
    void build(Shape _shape,Vector2 _postion,Vector2 _size,Color _color,bool _mouse);
    void build(Shape _shape,Vector2 _postion,Vector2 _size,Color _color,Texture2D &_texture,bool _mouse);
    void build(Shape _shape,Vector2 _postion,float radius,Color _color,bool _mouse);
    void buildText(char *_text,Font _font);
};

#endif /* node_hpp */
