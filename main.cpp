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
#include"Slime.h"
using namespace std;

long int frameTime = 0;

void initWindow(sf::RenderWindow& window);
void initBackground(sf::Sprite& sprite);
void update(sf::RenderWindow& window, const sf::Sprite& background, Hero& hero, PhysicsWorld& world, const BlockGrid& grid, Slime* slime);
void handleEvents(sf::RenderWindow &window, BlockGrid& grid, Hero& hero, Slime*& slime, PhysicsWorld& world);
void handleHeroMovement(Hero &hero);
void addBlock(const sf::Vector2i& mousePos, BlockGrid& grid);
void addSlime(const sf::Vector2i& mousePos, Slime*& slime);

int main() {
    Slime* slime = nullptr;
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
        handleEvents(window, grid, hero, slime, world);
        handleHeroMovement(hero);
        update(window, background, hero, world, grid, slime);
    }
    delete slime;
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
    float gridX = (mousePos.x/(int)BLOCK_WIDTH)*BLOCK_WIDTH;
    float gridY = (mousePos.y/(int)BLOCK_HEIGTH)*BLOCK_HEIGTH;
    if(!grid.isBlockPresent(gridX, gridY)){  //Sennò tenendo premuto si mettono un sacco di blocchi
        grid.addBlock(Block(gridX, gridY,Type::green));
        cout << "block added" << endl;
    }
}

void handleEvents(sf::RenderWindow &window, BlockGrid& grid, Hero& hero, Slime*& slime, PhysicsWorld& world) {
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }
        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
            hero.shoot();
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){  //TODO renderlo un evento o spostarlo
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            addBlock(mousePos, grid);
        }
        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            addSlime(mousePos, slime);
            world.addSlime(slime);
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

void addSlime(const sf::Vector2i& mousePos, Slime*& slime){
    slime = new Slime((mousePos.x/(int)BLOCK_WIDTH)*BLOCK_WIDTH, (mousePos.y/(int)BLOCK_HEIGTH)*BLOCK_HEIGTH, 5.f,30);
}


void update(sf::RenderWindow& window, const sf::Sprite& background, Hero& hero, PhysicsWorld& world, const BlockGrid& grid, Slime* slime){
    frameTime++;
    window.clear();
    window.draw(background);
    hero.draw(window);
    world.update();
    grid.draw(window);
    if(slime!= nullptr) {
        slime->draw(window);
    }
    window.display();
}