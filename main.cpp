#include <iostream>
#include<string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include"constants.h"
#include"Hero.h"
#include"PhysicsWorld.h"
#include"Block.h"
#include"BlockGrid.h"
#include"HeroBullet.h"
#include"Slime.h"
#include"EnemyContainer.h"
#include"Plant.h"
#include"Pig.h"

using namespace std;

long int frameTime = 0;

void initWindow(sf::RenderWindow& window);
void initBackground(sf::Sprite& sprite);
void update(sf::RenderWindow& window, const sf::Sprite& background, Hero& hero, PhysicsWorld& world, const BlockGrid& grid, EnemyContainer& enemyContainer);
void handleEvents(sf::RenderWindow &window, BlockGrid& grid, Hero& hero, EnemyContainer& enemyContainer, PhysicsWorld& world);
void handleHeroMovement(Hero &hero);
void addBlock(const sf::Vector2i& mousePos, BlockGrid& grid);
void addSlime(const sf::Vector2i& mousePos, EnemyContainer& enemyContainer);
void addPlant(const sf::Vector2i& mousePos, EnemyContainer& enemyContainer);
void addPig(const sf::Vector2i& mousePos, EnemyContainer& enemyContainer);

int main() {
    sf::RenderWindow window;
    initWindow(window);
    PhysicsWorld world;
    Block::loadTextures();
    BlockGrid grid(GRID_WIDTH, GRID_HEIGHT);
    sf::Sprite background;
    Hero hero(500, 200, 8.0f);
    EnemyContainer enemyContainer;
    addBlock(sf::Vector2i (500, SCREEN_HEIGTH-100), grid);
    world.addHero(&hero);
    world.addGrid(&grid);
    world.addEnemyContainer(&enemyContainer);
    hero.setPhysicsWorld(&world);
    initBackground(background);
    while(window.isOpen()){
        handleEvents(window, grid, hero, enemyContainer, world);
        handleHeroMovement(hero);
        update(window, background, hero, world, grid, enemyContainer);
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
    float gridX = (mousePos.x/(int)BLOCK_WIDTH)*BLOCK_WIDTH;
    float gridY = (mousePos.y/(int)BLOCK_HEIGTH)*BLOCK_HEIGTH;
    if(!grid.isBlockPresent(gridX, gridY)){  //Sennò tenendo premuto si mettono un sacco di blocchi
        grid.addBlock(Block(gridX, gridY,Type::green));
        cout << "block added" << endl;
    }
}

void handleEvents(sf::RenderWindow &window, BlockGrid& grid, Hero& hero, EnemyContainer& enemyContainer, PhysicsWorld& world) {
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
            addSlime(mousePos, enemyContainer);
        }
        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            addPlant(mousePos, enemyContainer);
        }
        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            addPig(mousePos, enemyContainer);
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

void addSlime(const sf::Vector2i& mousePos, EnemyContainer& enemyContainer){
    enemyContainer.addEnemy(new Slime((mousePos.x/(int)BLOCK_WIDTH)*BLOCK_WIDTH, (mousePos.y/(int)BLOCK_HEIGTH)*BLOCK_HEIGTH, 0.f,30));
}

void addPlant(const sf::Vector2i& mousePos, EnemyContainer& enemyContainer){
    enemyContainer.addEnemy(new Plant((mousePos.x/(int)BLOCK_WIDTH)*BLOCK_WIDTH, (mousePos.y/(int)BLOCK_HEIGTH)*BLOCK_HEIGTH, 5.f,30));
}

void addPig(const sf::Vector2i& mousePos, EnemyContainer& enemyContainer){
    enemyContainer.addEnemy(new Pig((mousePos.x/(int)BLOCK_WIDTH)*BLOCK_WIDTH, (mousePos.y/(int)BLOCK_HEIGTH)*BLOCK_HEIGTH, 3.f,30));
}

void update(sf::RenderWindow& window, const sf::Sprite& background, Hero& hero, PhysicsWorld& world, const BlockGrid& grid, EnemyContainer& enemyContainer){
    frameTime++;
    window.clear();
    window.draw(background);
    hero.draw(window);
    world.update();
    grid.draw(window);
    enemyContainer.drawAll(window);
    window.display();
}