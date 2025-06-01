#include "C:\Users\Shah Faisal\source\repos\Data Structures Project\Data Structures Project\Zombie.h"

// Constructor
Zombie::Zombie(int posX, int posY) {
    x = posX;
    y = posY;
    health = 100;
    damageValue = 20; // Standard damage value
}

// Get position X
int Zombie::getX() const {
    return x;
}

// Get position Y
int Zombie::getY() const {
    return y;
}

// Set position
void Zombie::setPosition(int posX, int posY) {
    x = posX;
    y = posY;
}

// Get health
int Zombie::getHealth() const {
    return health;
}

// Set health
void Zombie::setHealth(int newHealth) {
    health = newHealth;
    if (health < 0) {
        health = 0;
    }
}

// Get damage value
int Zombie::getDamageValue() const {
    return damageValue;
}