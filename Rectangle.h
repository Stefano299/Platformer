//
// Created by stefano on 7/15/24.
//

#ifndef PLATFORMER_RECTANGLE_H
#define PLATFORMER_RECTANGLE_H


struct Rectangle {
public:
    float x;
    float y;
    float width;
    float height;
public:
    Rectangle(float x, float y, float w, float h):x(x), y(y), width(w), height(h){}
};


#endif //PLATFORMER_RECTANGLE_H
