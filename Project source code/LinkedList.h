#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <iostream>

// Node class for the linked list
class Node {
private:
    std::string itemName;  // Name of the item
    int value;          // Value of the item
    Node* next;         // Pointer to the next node

public:
    // Constructor
    Node(const std::string& name, int val);

    // Getters
    std::string getName() const;
    int getValue() const;
    Node* getNext() const;

    // Setters
    void setNext(Node* nextNode);

    // Friend class
    friend class LinkedList;
};

// LinkedList class to manage inventory
class LinkedList {
private:
    Node* head;  // Head of the linked list
    int size;    // Number of items in the list

public:
    // Constructor
    LinkedList();

    // Destructor
    ~LinkedList();

    // Insert a new item at the beginning
    void insert(const std::string& name, int value);

    // Remove an item by name
    bool remove(const std::string& name);

    // Search for an item by name
    Node* search(const std::string& name) const;

    // Display all items in the inventory
    void display() const;

    // Check if the list is empty
    bool isEmpty() const;

    // Get the size of the list
    int getSize() const;

    // Get the head of the list
    Node* getHead() const;
};

#endif // LINKEDLIST_H#pragma once
