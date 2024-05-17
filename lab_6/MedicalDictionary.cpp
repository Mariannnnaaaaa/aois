#include <iostream>
#include <string>
#include <vector>
#include "Node.cpp"

using namespace std;

class MedicalDictionary {
private:
    int capacity;
    vector<Node*> table;

    int _hashFunction(const string& key) {
        if (key.length() < 2) {
            return 0;
        }
        int first = toupper(key[0]) - 'A';
        int second = toupper(key[1]) - 'A';
        return (first * 26 + second) % capacity;
    }

public:
    MedicalDictionary(int capacity = 20) : capacity(capacity), table(vector<Node*>(capacity, nullptr)) {}

    int getCapacity() const { return capacity; }

    void setCapacity(int newCapacity) {
        capacity = newCapacity;
        table.resize(newCapacity, nullptr);
    }

    void addTerm(const string& term, const string& definition) {
        int index = _hashFunction(term);
        if (table[index] == nullptr) {
            table[index] = new Node(term, definition);
        }
        else {
            Node* current = table[index];
            while (current->getNext() != nullptr) {
                current = current->getNext();
            }
            current->setNext(new Node(term, definition));
        }
    }

    string searchTerm(const string& term) {
        int index = _hashFunction(term);
        Node* current = table[index];
        vector<string> definitions;

        while (current != nullptr) {
            if (current->getKey() == term) {
                definitions.push_back(current->getValue());
            }
            current = current->getNext();
        }

        if (definitions.empty()) {
            return "The term is not found in the dictionary.";
        }

        string result = "Definitions for '" + term + "':\n";
        for (const string& definition : definitions) {
            result += " - " + definition + "\n";
        }

        return result;
    }

    string deleteTerm(const string& term) {
        int index = _hashFunction(term);
        Node* current = table[index];
        Node* prev = nullptr;
        vector<Node*> nodesToDelete;
        while (current != nullptr) {
            if (current->getKey() == term) {
                nodesToDelete.push_back(current);
            }
            prev = current;
            current = current->getNext();
        }

        if (nodesToDelete.empty()) {
            return "The term is not found in the dictionary.";
        }
        else if (nodesToDelete.size() == 1) {
            Node* nodeToDelete = nodesToDelete[0];
            current = table[index];
            prev = nullptr;
            while (current != nullptr) {
                if (current == nodeToDelete) {
                    if (prev != nullptr) {
                        prev->setNext(current->getNext());
                    }
                    else {
                        table[index] = current->getNext();
                    }
                    delete current;
                    return "The term has been successfully deleted.";
                }
                prev = current;
                current = current->getNext();
            }
        }
        else {
            cout << "Several entries with the term '" << term << "' were found. Choose which one to delete:" << endl;
            for (int i = 0; i < nodesToDelete.size(); ++i) {
                cout << i + 1 << ". " << nodesToDelete[i]->getValue() << endl;
            }
            int choice;
            cin >> choice;
            while (choice < 1 || choice > nodesToDelete.size()) {
                cout << "Incorrect choice. Try again: ";
                cin >> choice;
            }

            Node* nodeToDelete = nodesToDelete[choice - 1];
            current = table[index];
            prev = nullptr;
            while (current != nullptr) {
                if (current == nodeToDelete) {
                    if (prev != nullptr) {
                        prev->setNext(current->getNext());
                    }
                    else {
                        table[index] = current->getNext();
                    }
                    delete current;
                    return "The term has been successfully deleted.";
                }
                prev = current;
                current = current->getNext();
            }
        }
        return "An error occurred when deleting a term.";
    }

    void displayAllTerms() {
        cout << "A list of all terms and their definitions:" << endl;
        for (int i = 0; i < capacity; ++i) {
            Node* current = table[i];
            cout << "Cell " << i << ":" << endl;
            while (current != nullptr) {
                cout << "  " << current->getKey() << ": " << current->getValue() << endl;
                current = current->getNext();
            }
        }
    }

    ~MedicalDictionary() {
        for (int i = 0; i < capacity; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* next = current->getNext();
                delete current;
                current = next;
            }
        }
    }
};