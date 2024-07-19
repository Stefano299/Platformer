//
// Created by stefano on 7/19/24.
//

#ifndef PLATFORMER_CAMERA_H
#define PLATFORMER_CAMERA_H

#include<SFML/Graphics.hpp>

class Camera {
private:
    sf::View view;
    sf::Texture backgroundTxt; //Se si muove la camera is muove anche l background
    sf::Sprite backgroundSpr;
    float width;
    float heigth;
    float x;
    float y;
    float speed;
public:
    Camera(float width,float heigth, float speed);
    void setView(sf::RenderWindow& window) const;
    void arrowsMove(sf::RenderWindow& window); //Muovere la camera con le arrow keys
    void drawBackground(sf::RenderWindow& window);
    float getX() const;
    float getY() const;
};


#endif //PLATFORMER_CAMERA_H
