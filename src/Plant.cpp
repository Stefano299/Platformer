//
// Created by stefano on 7/18/24.
//

#include "../includes/Plant.h"
#include"../includes/frameTime.h"

//TODO fare che hero e plant hanno la stessa funzione sign
int sign2(float x){ //Metoddo sign2 per non avere conflitto di nome con quello di hero
    if(x > 0)
        return 1;
    else if(x<0)
        return -1;
    else if(x==0)
        return 0;
}

Plant::Plant(float x, float y, float speed, int hp, EnemyContainer* container) : Enemy(x, y, speed, hp, container) {
    weapon.setType(WeaponType::Plant);
    shootTexture.loadFromFile("../assets/plantattack.png");
    idleTexture.loadFromFile("../assets/plantidle.png");
    hitTexture.loadFromFile("../assets/planthit.png");
    sprite.setOrigin(22, 21);  //La pianta è 44x42
    sprite.setScale(3,3);
    this->x+=35;
    this->y+=30+5; //Voglio metterlo giust sulla piattaforma
    sprite.setPosition(this->x, this->y);
    rectangle = new Rectangle(x+2, y-4, 43*2, 34*3);
    hitIndex = 0;
    idleIndex = 0;
    shootIndex = 0;
    direction = 0; //Non voglio si muova
    animationType = PlantAnimationType::Idle;
    shootDirection = -1;
    shootTime = 0;
    collisionDmg = 3;
}

void Plant::hitAnimation() {
    sprite.setTexture(hitTexture);
    sprite.setTextureRect(sf::IntRect(44 * hitIndex, 0, 44, 42));
}

void Plant::idleAnimation() {
    sprite.setTexture(idleTexture);
    sprite.setTextureRect(sf::IntRect (44*idleIndex, 0, 44, 42));
}

void Plant::shootAnimation() {
    sprite.setTexture(shootTexture);
    sprite.setTextureRect(sf::IntRect (44*shootIndex, 0, 44, 42));
}

void Plant::timeFlow() {
    if(frameTime%5==0 && animationType == PlantAnimationType::Hit)
        hitIndex++;
    if(frameTime%4==0)
        idleIndex++;
    if(frameTime%6 ==0 && animationType == PlantAnimationType::Shoot){
        shootIndex++;
        if(shootIndex == 4)
            weapon.shoot(x+ sign2(shootDirection)*30, y-30, shootDirection); //spara proprio quando si trova al punto giusto dell'animazione
            //Correzioni fatte per far uscire il proiettile dalla bocca
    }
    if(hitIndex > 4) {
        hitIndex = 0;
        animationType = PlantAnimationType::Idle; //Dopo che finisce l'animazione che viene colpito voglio si passi di nuovo a quela che cammina
    }
    if(hitIndex >= 1 && hp <= 0){
        container->removeEnemy(this); //Prima di morrie voglio facia l'animazione
    }
    if(idleIndex > 10)
        idleIndex = 0;
    if(shootIndex > 7){
        shootIndex = 0;
        animationType = PlantAnimationType::Idle; //Dopo aver sparato torna idle
    }
    shootTime++;
}

void Plant::setAnimation() {
    if(animationType == PlantAnimationType::Hit)
        hitAnimation();
    else if(animationType == PlantAnimationType::Idle)
        idleAnimation();
    else if(animationType == PlantAnimationType::Shoot)
        shootAnimation();
}

void Plant::draw(sf::RenderWindow &window) {
    setAnimation();
    move(direction); //Tanto non si muove;
    //rectangle->draw(window);
    weapon.draw(window); //Per mostrare i proiettili
    window.draw(sprite);
    timeFlow();
}

void Plant::hit(int dmg) {
    hp-= dmg;
    animationType = PlantAnimationType::Hit;
}

void Plant::changeShootDir(float dir) {
    shootDirection = sign2(dir);
    sprite.setScale(-shootDirection*3, 3.f); //Voglio che si  giri lo sprite in base a dove sta guardando
}

void Plant::shoot() {         //Il proiettile è sparato nella direzione in cui è orientato plant in un certo istante
    //48 per fare coincidere, se spara più coli di seguito, lo sparo all'animazione
    if(shootTime >= 48){  //Per non permettergli di sparare troppi colpi
        animationType = PlantAnimationType::Shoot; //Il colpo viene sparato nel metodo shootANimation
        shootTime = 0;
    }
}

const Weapon &Plant::getWeapon() const {
    return weapon;
}



