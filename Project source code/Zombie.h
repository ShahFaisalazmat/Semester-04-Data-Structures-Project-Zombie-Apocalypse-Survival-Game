#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H

// Zombie class to represent each zombie in the game
class Zombie {
private:
    int x, y;        // Position coordinates
    int health;      // Zombie health
    int damageValue; // Damage inflicted on player

public:
    // Constructor
    Zombie(int posX, int posY);

    // Get position
    int getX() const;
    int getY() const;

    // Set position
    void setPosition(int posX, int posY);

    // Get health
    int getHealth() const;

    // Set health
    void setHealth(int newHealth);

    // Get damage value
    int getDamageValue() const;
};

#endif // ZOMBIE_H