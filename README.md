# 🧟 Zombie Apocalypse Survival Game

A **console-based C++ survival game** developed as a **Data Structures semester project** for CS2001. The game challenges the player to navigate through a zombie-infested city, collect valuable items, avoid zombies, and reach the safe zone.

The project demonstrates the practical use of fundamental **data structures and algorithms** in an interactive game environment.

## 🎮 Game Overview

The player starts in a randomly generated city map and must survive long enough to reach the safe zone.

The game includes:

* 🕹️ **Manual Mode** — Control the player manually through the map.
* 🤖 **Automated Mode** — Uses pathfinding to automatically navigate toward the safe zone.
* 🗺️ **Randomly Generated Maps** — Maps contain walls, items, zombies, and open paths.
* ❤️ **Health System** — The player's health decreases during encounters with zombies.
* 🎒 **Inventory System** — Collected items are stored and displayed.
* 🏆 **Scoring System** — Score depends on collected items, zombies encountered, and distance traveled.
* 💾 **High Score System** — High scores are stored in `highscores.txt`.

## 🧩 Data Structures & Algorithms

The main purpose of the project is to demonstrate how data structures can be applied to game development.

### 1. Graph — City Map

The city map is represented using a **graph**.

* Each map cell represents a node.
* Edges connect adjacent cells.
* Movement is possible in four directions:

  * Up
  * Down
  * Left
  * Right
* Node information stores the content of each cell.
* The graph is used for pathfinding in automated mode.

### 2. Breadth-First Search (BFS)

**BFS** is used by the automated mode to find a shortest path from the player's current position toward the destination.

This allows the automated player to navigate through the map while considering walls and available paths.

### 3. Queue — Zombie Management

A custom **Queue** is used to manage zombie spawning and movement.

Queue operations include:

* `push`
* `pop`
* `peek`

Zombies are processed during each game turn.

### 4. Singly Linked List — Inventory

A custom **singly linked list** is used to maintain the player's inventory.

The inventory supports:

* Inserting items
* Removing items
* Displaying collected items

Each item stores information such as its name, value, and color.

## 🕹️ Gameplay

### Main Menu

The game provides the following options:

```text
1. Start Manual Mode
2. Start Automated Mode
3. View High Scores
4. Exit Game
```

### Map Symbols

| Symbol | Meaning   |
| ------ | --------- |
| `P`    | Player    |
| `S`    | Safe Zone |
| `Z`    | Zombie    |
| `*`    | Item      |
| `#`    | Wall      |

### Objective

Reach the **Safe Zone (`S`)** while:

1. Navigating around walls.
2. Avoiding zombies.
3. Collecting useful items.
4. Maintaining your health.
5. Maximizing your score.

## 🏁 Game End Conditions

The game can end in three ways:

### 🟢 Victory

The player reaches the safe zone.

### 🔴 Defeat — Zombie Encounter

A zombie catches the player.

### 🔴 Defeat — Health Depleted

The player's health reaches `0`.

## 🏆 Scoring System

The project uses the following scoring formula:

```text
Score = (ItemsCollectedValue × 10)
        − (ZombiesEncountered × 5)
        + (DistanceTraveled × 2)
```

High scores are saved in:

```text
highscores.txt
```

along with player names.

## 🖥️ User Interface

The game uses an **ASCII-based Text User Interface (TUI)**.

The gameplay screen displays:

* Current map
* Player position
* Zombies
* Items
* Walls
* Player health
* Current score
* Inventory

The menu and game interface also use color coding to improve readability.

## 🧪 Testing

The project was tested using several approaches:

* Manual testing of movement directions
* Pathfinding verification
* Boundary-condition testing
* Map-edge testing
* Wall-collision testing
* Inventory management testing
* Zombie movement testing

## ⚙️ Challenges

Several implementation challenges were addressed during development:

* Efficient pathfinding
* Synchronizing zombie movement
* Managing console colors across different platforms
* Balancing game difficulty

## 🚀 Future Enhancements

Possible future improvements include:

* 👹 Multiple zombie types with different behaviors
* 🗺️ More complex maps and special zones
* 💾 Save/load game functionality
* 👥 Multiplayer support

## 📚 Academic Context

**Course:** CS2001 — Data Structures
**Project Type:** Semester Project
**Language:** C++
**Application Type:** Console-Based Game

The project demonstrates how **graphs, queues, linked lists, and BFS** can be integrated into a practical software application.

## 📸 Game Screens

The project includes screenshots showing:

* Main menu
* Gameplay in progress
* Winning screen
* Losing screen
* High-score display

## 👨‍💻 Authors

**Shah Faisal**
BS Software Engineering
FAST-NUCES Islamabad

---

⭐ **Academic Project — Data Structures & Algorithms in C++**
