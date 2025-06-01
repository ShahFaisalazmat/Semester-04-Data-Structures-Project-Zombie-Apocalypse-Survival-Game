// Zombie Apocalypse Survival Game
// Data Structures Semester Project - Spring 2025
// 
// This is the main file that initializes the game and handles the main menu

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>  // For _getch() functionality
#include <windows.h> // For system("cls") and Sleep()
#include "C:\Users\Shah Faisal\source\repos\Data Structures Project\Data Structures Project\Game.h"

using namespace std;

// Function prototypes
void displayTitle();
void displayMenu();
void displayHighScores();
void saveHighScore(const string& playerName, int score);

int main() {
    bool exitGame = false;
    Game* game = nullptr;
    string playerName;

    while (!exitGame) {
        system("cls"); // Clear screen
        displayTitle();
        displayMenu();

        char choice = _getch();

        switch (choice) {
        case '1': { // Manual Mode
            system("cls");
            cout << "Enter your name: ";
            cin >> playerName;

            game = new Game(20, 20); // Create a 20x20 map
            game->initialize();

            bool gameResult = game->playManualMode();

            if (gameResult) {
                cout << "\nCongratulations! You survived the zombie apocalypse!" << endl;
                saveHighScore(playerName, game->getScore());
            }
            else {
                cout << "\nGame Over! You were caught by zombies!" << endl;
            }

            delete game;
            game = nullptr;

            cout << "\nPress any key to return to the main menu...";
            _getch();
            break;
        }
        case '2': { // Automated Mode
            system("cls");
            cout << "Enter your name: ";
            cin >> playerName;

            game = new Game(20, 20); // Create a 20x20 map
            game->initialize();

            bool gameResult = game->playAutomatedMode();

            if (gameResult) {
                cout << "\nCongratulations! You survived the zombie apocalypse!" << endl;
                saveHighScore(playerName, game->getScore());
            }
            else {
                cout << "\nGame Over! You couldn't reach the safe zone!" << endl;
            }

            delete game;
            game = nullptr;

            cout << "\nPress any key to return to the main menu...";
            _getch();
            break;
        }
        case '3': // Display High Scores
            system("cls");
            displayHighScores();
            cout << "\nPress any key to return to the main menu...";
            _getch();
            break;
        case '4': // Exit
            exitGame = true;
            break;
        default:
            cout << "\nInvalid choice. Press any key to try again...";
            _getch();
            break;
        }
    }

    cout << "\nThank you for playing Zombie Apocalypse Survival Game!" << endl;
    return 0;
}

// Display game title with ASCII art
void displayTitle() {
    cout << "=====================================================================" << endl;
    cout << "   _____                _     _                                       " << endl;
    cout << "  |__  /___  _ __ ___ | |__ (_) ___                                  " << endl;
    cout << "    / // _ \\| '_ ` _ \\| '_ \\| |/ _ \\                                 " << endl;
    cout << "   / /| (_) | | | | | | |_) | |  __/                                 " << endl;
    cout << "  /____\\___/|_| |_| |_|_.__/|_|\\___|                                 " << endl;
    cout << "    / \\   _ __   ___   ___ __ _| |_   _ _ __  ___  ___               " << endl;
    cout << "   / _ \\ | '_ \\ / _ \\ / __/ _` | | | | | '_ \\/ __|/ _ \\              " << endl;
    cout << "  / ___ \\| |_) | (_) | (_| (_| | | |_| | |_) \\__ \\  __/              " << endl;
    cout << " /_/   \\_\\ .__/ \\___/ \\___\\__,_|_|\\__, | .__/|___/\\___|              " << endl;
    cout << "         |_|                      |___/|_|                            " << endl;
    cout << "=====================================================================" << endl;
    cout << "                       SURVIVAL GAME                                  " << endl;
    cout << "=====================================================================" << endl;
    cout << endl;
}

// Display the main menu
void displayMenu() {
    cout << "MAIN MENU:" << endl;
    cout << "1. Start Manual Mode" << endl;
    cout << "2. Start Automated Mode" << endl;
    cout << "3. View High Scores" << endl;
    cout << "4. Exit" << endl;
    cout << "\nSelect an option (1-4): ";
}

// Display high scores from file
void displayHighScores() {
    ifstream highScoreFile("C:\\Users\\Shah Faisal\\source\\repos\\Data Structures Project\\Data Structures Project\\highscores.txt");

    cout << "=====================================================================" << endl;
    cout << "                           HIGH SCORES                               " << endl;
    cout << "=====================================================================" << endl;

    if (!highScoreFile.is_open()) {
        cout << "No high scores available yet." << endl;
        return;
    }

    string name;
    int score;
    int rank = 1;

    cout << "Rank\tName\t\tScore" << endl;
    cout << "------------------------------------" << endl;

    while (highScoreFile >> name >> score) {
        cout << rank << "\t" << name << "\t\t" << score << endl;
        rank++;
    }

    highScoreFile.close();
}

// Save high score to file
void saveHighScore(const string& playerName, int score) {
    // Simple implementation - append to file
    ofstream highScoreFile("C:\\Users\\Shah Faisal\\source\\repos\\Data Structures Project\\Data Structures Project\\highscores.txt", ios::app);

    if (highScoreFile.is_open()) {
        highScoreFile << playerName << " " << score << endl;
        highScoreFile.close();
        cout << "Your score has been saved!" << endl;
    }
    else {
        cout << "Unable to save high score." << endl;
    }
}