#include <iostream>
#include<string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include"constants.h"
#include"frameTime.h"
#include"Hero.h"
#include"PhysicsWorld.h"
#include"Block.h"
#include"BlockGrid.h"
#include"Bullet.h"

using namespace std;

long int frameTime = 0;

void initWindow(sf::RenderWindow& window);
void initBackground(sf::Sprite& sprite);
void update(sf::RenderWindow& window, const sf::Sprite& background, Hero& hero, PhysicsWorld& world, const BlockGrid& grid);
void handleEvents(sf::RenderWindow &window, BlockGrid& grid, Hero& hero);
void handleHeroMovement(Hero &hero);
void addBlock(const sf::Vector2i& mousePos, BlockGrid& grid);

int main() {
    sf::RenderWindow window;
    initWindow(window);
    PhysicsWorld world;
    Block::loadTextures();
    BlockGrid grid(GRID_WIDTH, GRID_HEIGHT);
    sf::Sprite background;
    Hero hero(500, 200, 8.0f);
    addBlock(sf::Vector2i (500, SCREEN_HEIGTH-100), grid);
    world.addHero(&hero);
    world.addGrid(&grid);
    hero.setPhysicsWorld(&world);
    initBackground(background);
    while(window.isOpen()){
        handleEvents(window, grid, hero);
        handleHeroMovement(hero);
        update(window, background, hero, world, grid);
    }
    return 0;
}

void handleHeroMovement(Hero &hero) {
    int dx = 0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        dx=-1;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        dx = 1;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        hero.jump();
    hero.move(dx);
}
void addBlock(const sf::Vector2i& mousePos, BlockGrid& grid){
    grid.addBlock(Block((mousePos.x/(int)BLOCK_WIDTH)*BLOCK_WIDTH, (mousePos.y/(int)BLOCK_HEIGTH)*BLOCK_HEIGTH, Type::green));
}

void handleEvents(sf::RenderWindow &window, BlockGrid& grid, Hero& hero) {
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }
        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
            hero.shoot();
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){  //TODO renderlo un evento o spostarlo
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            std::cout << mousePos.x << " PRESSED" << endl;
            addBlock(mousePos, grid);
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
    window.setKeyRepeatEnabled(false);
}

void update(sf::RenderWindow& window, const sf::Sprite& background, Hero& hero, PhysicsWorld& world, const BlockGrid& grid){
    frameTime++;
    window.clear();
    window.draw(background);
    hero.draw(window);
    world.update();
    grid.draw(window);
    window.display();
}