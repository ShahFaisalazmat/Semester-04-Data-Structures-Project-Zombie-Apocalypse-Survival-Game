#include "C:\Users\Shah Faisal\source\repos\Data Structures Project\Data Structures Project\LinkedList.h"

// Node Constructor
Node::Node(const std::string& name, int val) {
    itemName = name;
    value = val;
    next = nullptr;
}

// Node Getters
std::string Node::getName() const {
    return itemName;
}

int Node::getValue() const {
    return value;
}

Node* Node::getNext() const {
    return next;
}

// Node Setters
void Node::setNext(Node* nextNode) {
    next = nextNode;
}

// LinkedList Constructor
LinkedList::LinkedList() {
    head = nullptr;
    size = 0;
}

// LinkedList Destructor
LinkedList::~LinkedList() {
    // Delete all nodes to prevent memory leaks
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    size = 0;
}

// Insert a new item at the beginning of the list
void LinkedList::insert(const std::string& name, int value) {
    // Create a new node
    Node* newNode = new Node(name, value);

    // Insert at the beginning (faster than appending)
    newNode->next = head;
    head = newNode;

    // Increment size
    size++;
}

// Remove an item by name
bool LinkedList::remove(const std::string& name) {
    // Check if list is empty
    if (head == nullptr) {
        return false;
    }

    // Check if head is the item to remove
    if (head->itemName == name) {
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
        return true;
    }

    // Search for the item in the rest of the list
    Node* current = head;
    while (current->next != nullptr && current->next->itemName != name) {
        current = current->next;
    }

    // If found, remove it
    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
        size--;
        return true;
    }

    // Item not found
    return false;
}

// Search for an item by name
Node* LinkedList::search(const std::string& name) const {
    Node* current = head;

    // Traverse the list
    while (current != nullptr) {
        if (current->itemName == name) {
            return current; // Item found
        }
        current = current->next;
    }

    // Item not found
    return nullptr;
}

// Display all items in the inventory
void LinkedList::display() const {
    Node* current = head;
    bool first = true;

    // Traverse the list
    while (current != nullptr) {
        if (!first) {
            std::cout << ", ";
        }
        else {
            first = false;
        }
        std::cout << current->itemName << "(" << current->value << ")";
        current = current->next;
    }
}

// Check if the list is empty
bool LinkedList::isEmpty() const {
    return head == nullptr;
}

// Get the size of the list
int LinkedList::getSize() const {
    return size;
}

// Get the head of the list
Node* LinkedList::getHead() const {
    return head;
}