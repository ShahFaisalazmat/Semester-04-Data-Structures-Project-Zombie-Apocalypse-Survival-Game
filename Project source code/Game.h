#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <ctime>
#include <cstdlib>
#include "C:\Users\Shah Faisal\source\repos\Data Structures Project\Data Structures Project\Graph.h"
#include "C:\Users\Shah Faisal\source\repos\Data Structures Project\Data Structures Project\LinkedList.h"
#include "C:\Users\Shah Faisal\source\repos\Data Structures Project\Data Structures Project\Zombie.h "

class Game {
private:
    // Game map represented as a graph
    Graph* cityMap;

    // Player position
    int playerX, playerY;

    // Safe zone position
    int safeZoneX, safeZoneY;

    // Map dimensions
    int mapWidth, mapHeight;

    // Player stats
    int health;
    int score;

    // Queue for zombie management
    std::queue<Zombie> zombieQueue;

    // Linked list for collected items
    LinkedList* inventory;

    // Game status flags
    bool gameOver;
    bool playerWon;

    // Internal methods
    void drawMap();
    void movePlayer(char direction);
    void moveZombies();
    void spawnZombie();
    void checkCollisions();
    void collectItem();
    bool isValidMove(int x, int y);
    std::vector<std::pair<int, int>> findShortestPath(int startX, int startY, int endX, int endY);
    void updateScore();

public:
    // Constructor
    Game(int width, int height);

    // Destructor
    ~Game();

    // Game initialization
    void initialize();

    // Game modes
    bool playManualMode();
    bool playAutomatedMode();

    // Getters
    int getScore() const;
    int getHealth() const;
    bool isGameOver() const;
    bool hasPlayerWon() const;
};

#endif // GAME_H#pragma once
#pragma once
