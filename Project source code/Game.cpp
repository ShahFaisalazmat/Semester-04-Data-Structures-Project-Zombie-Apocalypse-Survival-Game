#include "C:\Users\Shah Faisal\source\repos\Data Structures Project\Data Structures Project\Game.h"
#include <conio.h>
#include <windows.h>
#include <queue>
#include <algorithm>

// Constructor
Game::Game(int width, int height) {
    // Initialize map dimensions
    mapWidth = width;
    mapHeight = height;

    // Create city map graph
    cityMap = new Graph(width * height);

    // Initialize player stats
    health = 100;
    score = 0;

    // Initialize game status
    gameOver = false;
    playerWon = false;

    // Initialize inventory
    inventory = new LinkedList();

    // Seed random number generator
    srand(static_cast<unsigned int>(time(nullptr)));
}

// Destructor
Game::~Game() {
    delete cityMap;
    delete inventory;
}

// Initialize the game
void Game::initialize() {
    // Create graph connections (edges) for the map
    // Each cell connects to adjacent cells (up, down, left, right)
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int nodeId = y * mapWidth + x;

            // Connect to adjacent cells if they exist
            // Up
            if (y > 0) {
                cityMap->addEdge(nodeId, (y - 1) * mapWidth + x);
            }
            // Down
            if (y < mapHeight - 1) {
                cityMap->addEdge(nodeId, (y + 1) * mapWidth + x);
            }
            // Left
            if (x > 0) {
                cityMap->addEdge(nodeId, y * mapWidth + (x - 1));
            }
            // Right
            if (x < mapWidth - 1) {
                cityMap->addEdge(nodeId, y * mapWidth + (x + 1));
            }
        }
    }

    // Set up walls (randomly block some edges)
    for (int i = 0; i < mapWidth * mapHeight / 5; i++) {
        int x = rand() % mapWidth;
        int y = rand() % mapHeight;

        // Ensure we don't place a wall at player or safezone positions
        if ((x != 1 || y != 1) && (x != mapWidth - 2 || y != mapHeight - 2)) {
            int nodeId = y * mapWidth + x;
            cityMap->setNodeType(nodeId, 'W'); // W for Wall
        }
    }

    // Place items (randomly)
    for (int i = 0; i < mapWidth * mapHeight / 10; i++) {
        int x = rand() % mapWidth;
        int y = rand() % mapHeight;

        // Ensure we don't place items on walls, player or safezone
        int nodeId = y * mapWidth + x;
        if (cityMap->getNodeType(nodeId) != 'W' &&
            (x != 1 || y != 1) &&
            (x != mapWidth - 2 || y != mapHeight - 2)) {
            cityMap->setNodeType(nodeId, 'I'); // I for Item
        }
    }

    // Place player at top-left corner
    playerX = 1;
    playerY = 1;
    cityMap->setNodeType(playerY * mapWidth + playerX, 'P');

    // Place safe zone at bottom-right corner
    safeZoneX = mapWidth - 2;
    safeZoneY = mapHeight - 2;
    cityMap->setNodeType(safeZoneY * mapWidth + safeZoneX, 'S');

    // Initial zombie spawn
    for (int i = 0; i < 3; i++) {
        spawnZombie();
    }
}

// Draw the game map
void Game::drawMap() {
    system("cls"); // Clear screen

    // Display game title
    std::cout << "==============================================================" << std::endl;
    std::cout << "                ZOMBIE APOCALYPSE SURVIVAL GAME                " << std::endl;
    std::cout << "==============================================================" << std::endl;

    // Display player stats
    std::cout << "Health: " << health << " | Score: " << score << std::endl;
    std::cout << "Inventory: ";
    if (inventory->isEmpty()) {
        std::cout << "Empty";
    }
    else {
        inventory->display();
    }
    std::cout << std::endl;

    // Display map border
    std::cout << "+";
    for (int x = 0; x < mapWidth; x++) {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;

    // Display map
    for (int y = 0; y < mapHeight; y++) {
        std::cout << "|";
        for (int x = 0; x < mapWidth; x++) {
            int nodeId = y * mapWidth + x;
            char nodeType = cityMap->getNodeType(nodeId);

            // Display appropriate character for each cell
            if (x == playerX && y == playerY) {
                std::cout << "P"; // Player
            }
            else if (x == safeZoneX && y == safeZoneY) {
                std::cout << "S"; // Safe zone
            }
            else if (nodeType == 'W') {
                std::cout << "#"; // Wall
            }
            else if (nodeType == 'Z') {
                std::cout << "Z"; // Zombie
            }
            else if (nodeType == 'I') {
                std::cout << "*"; // Item
            }
            else {
                std::cout << " "; // Empty space
            }
        }
        std::cout << "|" << std::endl;
    }

    // Display bottom border
    std::cout << "+";
    for (int x = 0; x < mapWidth; x++) {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;

    // Display controls
    std::cout << "Controls: W (Up), S (Down), A (Left), D (Right), Q (Quit)" << std::endl;
}

// Check if a move is valid
bool Game::isValidMove(int x, int y) {
    // Check if the position is within bounds
    if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
        return false;
    }

    // Check if the position is not a wall
    int nodeId = y * mapWidth + x;
    return cityMap->getNodeType(nodeId) != 'W';
}

// Move the player
void Game::movePlayer(char direction) {
    int newX = playerX;
    int newY = playerY;

    // Determine new position based on direction
    switch (direction) {
    case 'W': // Up
    case 'w':
        newY--;
        break;
    case 'S': // Down
    case 's':
        newY++;
        break;
    case 'A': // Left
    case 'a':
        newX--;
        break;
    case 'D': // Right
    case 'd':
        newX++;
        break;
    default:
        return; // Invalid direction
    }

    // Check if the move is valid
    if (isValidMove(newX, newY)) {
        // Update old position
        cityMap->setNodeType(playerY * mapWidth + playerX, ' ');

        // Update player position
        playerX = newX;
        playerY = newY;

        // Update new position
        int newNodeId = playerY * mapWidth + playerX;
        char nodeType = cityMap->getNodeType(newNodeId);

        // Check if player reached the safe zone
        if (playerX == safeZoneX && playerY == safeZoneY) {
            gameOver = true;
            playerWon = true;
            return;
        }

        // Check for item collection
        if (nodeType == 'I') {
            collectItem();
        }

        // Mark player's new position
        cityMap->setNodeType(newNodeId, 'P');
    }
}

// Spawn a new zombie
void Game::spawnZombie() {
    int x, y;
    int nodeId;

    // Find a valid position for the zombie (not on a wall, player, or safe zone)
    do {
        x = rand() % mapWidth;
        y = rand() % mapHeight;
        nodeId = y * mapWidth + x;
    } while ((x == playerX && y == playerY) ||
        (x == safeZoneX && y == safeZoneY) ||
        cityMap->getNodeType(nodeId) == 'W' ||
        cityMap->getNodeType(nodeId) == 'Z' ||
        cityMap->getNodeType(nodeId) == 'I');

    // Create zombie and add to queue
    Zombie zombie(x, y);
    zombieQueue.push(zombie);

    // Mark zombie position on map
    cityMap->setNodeType(nodeId, 'Z');
}

// Move all zombies in the queue
void Game::moveZombies() {
    int zombieCount = zombieQueue.size();

    // Process each zombie in the queue
    for (int i = 0; i < zombieCount; i++) {
        Zombie zombie = zombieQueue.front();
        zombieQueue.pop();

        // Clear old position
        cityMap->setNodeType(zombie.getY() * mapWidth + zombie.getX(), ' ');

        // Calculate potential moves (prefer moving toward player)
        int bestX = zombie.getX();
        int bestY = zombie.getY();
        int bestDistance = abs(playerX - zombie.getX()) + abs(playerY - zombie.getY());

        // Check each possible direction
        const int dx[4] = { 0, 1, 0, -1 }; // Right, Down, Left, Up
        const int dy[4] = { -1, 0, 1, 0 }; // Right, Down, Left, Up

        for (int j = 0; j < 4; j++) {
            int newX = zombie.getX() + dx[j];
            int newY = zombie.getY() + dy[j];

            if (isValidMove(newX, newY)) {
                int nodeId = newY * mapWidth + newX;
                char nodeType = cityMap->getNodeType(nodeId);

                // Don't move onto another zombie or the safe zone
                if (nodeType != 'Z' && nodeType != 'S') {
                    int distance = abs(playerX - newX) + abs(playerY - newY);

                    // Prefer moves that get closer to the player
                    if (distance < bestDistance) {
                        bestDistance = distance;
                        bestX = newX;
                        bestY = newY;
                    }
                }
            }
        }

        // Update zombie position
        zombie.setPosition(bestX, bestY);

        // Check if zombie reached the player
        if (bestX == playerX && bestY == playerY) {
            health -= 20; // Zombie attack damages player
            if (health <= 0) {
                gameOver = true;
                playerWon = false;
            }
        }
        else {
            // Mark new position
            cityMap->setNodeType(bestY * mapWidth + bestX, 'Z');

            // Add back to the queue
            zombieQueue.push(zombie);
        }
    }

    // Spawn new zombie with a 20% chance each turn
    if (rand() % 5 == 0) {
        spawnZombie();
    }
}

// Collect item at player's position
void Game::collectItem() {
    // Define possible items
    const char* itemNames[] = { "Medkit", "Food", "Ammo", "Weapon" };
    const int itemValues[] = { 25, 15, 10, 30 };

    // Randomly select an item
    int itemIndex = rand() % 4;
    std::string itemName = itemNames[itemIndex];
    int itemValue = itemValues[itemIndex];

    // Add item to inventory
    inventory->insert(itemName, itemValue);

    // Apply item effect
    if (itemName == "Medkit") {
        health += itemValue;
        if (health > 100) health = 100; // Cap health at 100
    }

    // Update score
    score += itemValue * 10;
}

// Find shortest path using BFS
std::vector<std::pair<int, int>> Game::findShortestPath(int startX, int startY, int endX, int endY) {
    // Result path
    std::vector<std::pair<int, int>> path;

    // Convert coordinates to node IDs
    int startNodeId = startY * mapWidth + startX;
    int endNodeId = endY * mapWidth + endX;

    // BFS data structures
    std::queue<int> nodeQueue;
    std::vector<bool> visited(mapWidth * mapHeight, false);
    std::vector<int> parent(mapWidth * mapHeight, -1);

    // Start BFS
    nodeQueue.push(startNodeId);
    visited[startNodeId] = true;

    while (!nodeQueue.empty()) {
        int currentNodeId = nodeQueue.front();
        nodeQueue.pop();

        // Check if we reached the end
        if (currentNodeId == endNodeId) {
            break;
        }

        // Get coordinates from node ID
        int x = currentNodeId % mapWidth;
        int y = currentNodeId / mapWidth;

        // Check all four directions
        const int dx[4] = { 0, 1, 0, -1 }; // Right, Down, Left, Up
        const int dy[4] = { -1, 0, 1, 0 }; // Right, Down, Left, Up

        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            // Skip if out of bounds
            if (newX < 0 || newX >= mapWidth || newY < 0 || newY >= mapHeight) {
                continue;
            }

            int newNodeId = newY * mapWidth + newX;

            // Skip if wall or already visited
            char nodeType = cityMap->getNodeType(newNodeId);
            if (nodeType == 'W' || visited[newNodeId]) {
                continue;
            }

            // Add to queue
            nodeQueue.push(newNodeId);
            visited[newNodeId] = true;
            parent[newNodeId] = currentNodeId;
        }
    }

    // Reconstruct path if end was reached
    if (parent[endNodeId] != -1) {
        int current = endNodeId;
        while (current != startNodeId) {
            int x = current % mapWidth;
            int y = current / mapWidth;
            path.push_back({ x, y });
            current = parent[current];
        }

        // Reverse path to get start->end order
        std::reverse(path.begin(), path.end());
    }

    return path;
}

// Update score based on game progress
void Game::updateScore() {
    // Formula: (Items Collected Value * 10) - (Zombies Encountered * 5) + (Distance Traveled * 2)
    int itemsValue = 0;
    Node* current = inventory->getHead();
    while (current != nullptr) {
        itemsValue += current->getValue();
        current = current->getNext();
    }

    int zombiesEncountered = 100 - health; // Estimate based on health loss
    int distanceTraveled = abs(playerX - 1) + abs(playerY - 1); // Manhattan distance from start

    score = (itemsValue * 10) - (zombiesEncountered / 10 * 5) + (distanceTraveled * 2);

    // Ensure score doesn't go negative
    if (score < 0) score = 0;
}

// Play in manual mode (player controls character)
bool Game::playManualMode() {
    char input;

    while (!gameOver) {
        // Draw the current state
        drawMap();

        // Get player input
        input = _getch();

        // Process input
        if (input == 'q' || input == 'Q') {
            gameOver = true;
            playerWon = false;
        }
        else if (input == 'w' || input == 'W' || input == 's' || input == 'S' ||
            input == 'a' || input == 'A' || input == 'd' || input == 'D') {
            movePlayer(input);
            moveZombies();
            updateScore();
        }

        // Add a small delay for better user experience
        Sleep(100);
    }

    // Final map display
    drawMap();

    return playerWon;
}

// Play in automated mode (computer finds path)
bool Game::playAutomatedMode() {
    // Find path from player to safe zone
    std::vector<std::pair<int, int>> path = findShortestPath(playerX, playerY, safeZoneX, safeZoneY);

    // Check if a path exists
    if (path.empty()) {
        std::cout << "No valid path to the safe zone!" << std::endl;
        return false;
    }

    // Follow the path
    for (const auto& position : path) {
        // Draw current state
        drawMap();

        // Move player to next position
        int nextX = position.first;
        int nextY = position.second;

        // Clear old position
        cityMap->setNodeType(playerY * mapWidth + playerX, ' ');

        // Update player position
        playerX = nextX;
        playerY = nextY;

        // Check new position
        int newNodeId = playerY * mapWidth + playerX;
        char nodeType = cityMap->getNodeType(newNodeId);

        // Check if player reached the safe zone
        if (playerX == safeZoneX && playerY == safeZoneY) {
            gameOver = true;
            playerWon = true;
            break;
        }

        // Check for item collection
        if (nodeType == 'I') {
            collectItem();
        }

        // Mark player's new position
        cityMap->setNodeType(newNodeId, 'P');

        // Move zombies
        moveZombies();

        // Update score
        updateScore();

        // Check if game is over
        if (gameOver) {
            break;
        }

        // Delay for animation
        Sleep(500);
    }

    // Final map display
    drawMap();

    return playerWon;
}

// Getters
int Game::getScore() const {
    return score;
}

int Game::getHealth() const {
    return health;
}

bool Game::isGameOver() const {
    return gameOver;
}

bool Game::hasPlayerWon() const {
    return playerWon;
}