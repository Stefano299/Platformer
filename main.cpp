#include <iostream>
#include<string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include"constants.h"
#include"frameTime.h"
#include"GameCharacter.h"

using namespace std;

long int frameTime = 0;

void initWindow(sf::RenderWindow& window);
void initBackground(sf::Sprite& sprite);
void update(sf::RenderWindow& window, const sf::Sprite& background, GameCharacter& hero);
void handleEvents(sf::RenderWindow &window);

void handleHeroMovement(GameCharacter &hero);

int main() {
    sf::RenderWindow window;
    initWindow(window);
    sf::Sprite background;
    GameCharacter hero(200, SCREEN_HEIGTH - 400, 8.0f);
    initBackground(background);
    while(window.isOpen()){
        handleEvents(window);
        handleHeroMovement(hero);
        update(window, background, hero);
    }
    return 0;
}

void handleHeroMovement(GameCharacter &hero) {
    int dx = 0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        dx=-1;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        dx = 1;
    hero.move(dx);
}

void handleEvents(sf::RenderWindow &window) {
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }
    }
}

void initBackground(sf::Sprite& sprite){
    static sf::Texture texture;  //Sennò viene eliminata
    texture.loadFromFile("../assets/background.jpg");
    sprite.setTexture(texture);
    sprite.scale((float)SCREEN_WIDTH/1920, (float)SCREEN_HEIGTH / 1200);
    sprite.setPosition(0,0);
}

void initWindow(sf::RenderWindow& window){
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGTH), "Platformer");
    window.setFramerateLimit(60);
}

void update(sf::RenderWindow& window, const sf::Sprite& background, GameCharacter& hero){
    frameTime++;
    window.clear();
    window.draw(background);
    hero.draw(window);
    window.display();
}