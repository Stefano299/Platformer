#include <iostream>
#include<string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include"../includes/constants.h"
#include"../includes/Hero.h"
#include"../includes/PhysicsWorld.h"
#include"../includes/Block.h"
#include"../includes/BlockGrid.h"
#include"../includes/HeroBullet.h"
#include"../includes/Slime.h"
#include"../includes/EnemyContainer.h"
#include"../includes/Plant.h"
#include"../includes/Pig.h"
#include"../includes/Camera.h"
#include"../includes/HealthBar.h"

using namespace std;

long int frameTime = 0;

int toGrid(float y){ //Per gestire quando i blocchi vengono messi in y negative (il blocco verrebbe messo nella casella più in basso)
    if(y <= 0)
        y -=BLOCK_HEIGTH;
    return ((int)y/(int)BLOCK_HEIGTH)*BLOCK_HEIGTH;
}

void initWindow(sf::RenderWindow& window);
void update(sf::RenderWindow& window, Hero& hero, PhysicsWorld& world, const BlockGrid& grid, EnemyContainer& enemyContainer);
void handleEvents(sf::RenderWindow &window, BlockGrid& grid, Hero& hero, EnemyContainer& enemyContainer, PhysicsWorld& world);
void handleHeroMovement(Hero &hero);
void addBlock(const sf::Vector2f& mousePos, BlockGrid& grid);
void addSlime(const sf::Vector2f& mousePos, EnemyContainer& enemyContainer);
void addPlant(const sf::Vector2f& mousePos, EnemyContainer& enemyContainer);
void addPig(const sf::Vector2f& mousePos, EnemyContainer& enemyContainer);

int main() {
    sf::RenderWindow window;
    initWindow(window);
    PhysicsWorld world;
    Block::loadTextures();
    BlockGrid grid(GRID_WIDTH, GRID_HEIGHT);
    Hero hero(500, SCREEN_HEIGTH-400, 8.0f, 40);
    EnemyContainer enemyContainer;
    addBlock(sf::Vector2f (500, SCREEN_HEIGTH-100), grid);
    world.addHero(&hero);
    world.addGrid(&grid);
    world.addEnemyContainer(&enemyContainer);
    hero.setPhysicsWorld(&world);
    while(window.isOpen()){
        handleEvents(window, grid, hero, enemyContainer, world);
        handleHeroMovement(hero);
        hero.getCamera()->arrowsMove(); //Per muovere la camera con le frecce, incaso serva
        update(window, hero, world, grid, enemyContainer);
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
void addBlock(const sf::Vector2f& mousePos, BlockGrid& grid){
    float gridX = ((int)mousePos.x/(int)BLOCK_WIDTH)*BLOCK_WIDTH;
    float gridY = toGrid(mousePos.y);
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
            //VOGLIO LE COORDINATE RELATIVE ALLA TELECAMERA!
            sf::Vector2f  worldPos = window.mapPixelToCoords(mousePos);
            addBlock(worldPos, grid);
        }
        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f  worldPos = window.mapPixelToCoords(mousePos);
            addSlime(worldPos, enemyContainer);
        }
        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f  worldPos = window.mapPixelToCoords(mousePos);
            addPlant(worldPos, enemyContainer);
        }
        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f  worldPos = window.mapPixelToCoords(mousePos);
            addPig(worldPos, enemyContainer);
        }
    }
}

void initWindow(sf::RenderWindow& window){
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGTH), "Platformer");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
}

void addSlime(const sf::Vector2f& mousePos, EnemyContainer& enemyContainer){
    enemyContainer.addEnemy(new Slime(((int)mousePos.x/(int)BLOCK_WIDTH)*BLOCK_WIDTH, toGrid(mousePos.y), 5.f,30, &enemyContainer));
}

void addPlant(const sf::Vector2f& mousePos, EnemyContainer& enemyContainer){
    enemyContainer.addEnemy(new Plant(((int)mousePos.x/(int)BLOCK_WIDTH)*BLOCK_WIDTH, toGrid(mousePos.y), 0.f,30, &enemyContainer));
}

void addPig(const sf::Vector2f& mousePos, EnemyContainer& enemyContainer){
    enemyContainer.addEnemy(new Pig(((int)mousePos.x/(int)BLOCK_WIDTH)*BLOCK_WIDTH, toGrid(mousePos.y), 3.f,30, &enemyContainer));
}

void update(sf::RenderWindow& window, Hero& hero, PhysicsWorld& world, const BlockGrid& grid, EnemyContainer& enemyContainer){
    frameTime++;
    window.clear();
    hero.draw(window);
    world.update();
    grid.draw(window);
    enemyContainer.drawAll(window);
    hero.drawHealthBar(window); //Lo devo fare cosicchè non venga coperta da altri sprite
    hero.getCamera()->drawGameOver(window);
    window.display();
}