//
// Created by stefano on 7/19/24.
//

#ifndef PLATFORMER_CAMERA_H
#define PLATFORMER_CAMERA_H

#include<SFML/Graphics.hpp>

class HealthBar;
class Camera {
private:
    sf::View view;
    sf::Texture backgroundTxt; //Se si muove la camera is muove anche l background
    sf::Sprite backgroundSpr;
    HealthBar* healthBar;
    sf::Texture gameoverTxt; //Sprite mostrato quando si perde
    sf::Sprite gameoverSpr;
    int gameOverIndex; //Per l'animazione del gameover
    float width;
    float heigth;
    float x;
    float y;
    float speed;
public:
    Camera(float width,float heigth, float speed);
    void arrowsMove(); //Muovere la camera con le arrow keys
    void update(sf::RenderWindow& window);
    void move(int dx, int dy);
    void setCoordinates(float x, float y);
    float getX() const;
    float getY() const;
    void updateHealthBar(int hp, int maxHealth);
    void drawHealthBar(sf::RenderWindow& window)const;
    HealthBar* getHealthBar() const;
    void drawGameOver(sf::RenderWindow& window); // per mostrare la schermata di gameover sopra tutto
    void gameOver(); //Mostrare la schermata di gameover
    ~Camera();
};


#endif //PLATFORMER_CAMERA_H
