#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
private:
    string key;
    string value;
    Node* next;

public:
    Node(string key, string value) : key(key), value(value), next(nullptr) {}

    string getKey() const {
        return key;
    }

    string getValue() const {
        return value;
    }

    Node* getNext() const {
        return next;
    }

    void setNext(Node* nextNode) {
        next = nextNode;
    }
};