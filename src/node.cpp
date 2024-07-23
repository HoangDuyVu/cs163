//
//  node.cpp
//  hahaaa
//
//  Created by Aquafjna on 22/7/24.
//

#include "node.hpp"

void node::build(Shape _shape, Vector2 _postion, Vector2 _size, Color _color,bool _mouse) {
    shape =_shape;
    postion = _postion;
    size = _size;
    color = _color;
    mouse = _mouse;
}

void node::build(Shape _shape, Vector2 _postion, Vector2 _size, Color _color,Texture2D &_texture,bool _mouse) {
    shape =_shape;
    postion = _postion;
    size = _size;
    color = _color;
    texture = _texture;
    mouse = _mouse;
}

void node::build(Shape _shape, Vector2 _postion, float _radius, Color _color,bool _mouse) {
    shape =_shape;
    postion = _postion;
    radius = _radius;
    color = _color;
    mouse = _mouse;
}

void node::buildText(char *_text, Font _font) {
    text = _text;
    font = _font;
}

