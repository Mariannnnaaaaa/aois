#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <bitset>

using namespace std;

class Matrix {
private:
    int matrix[16][16];
    int size;

public:
    Matrix();

    void printMatrix() const;

    int getSize() const;

    int getElement(int row, int col) const;

    void setElement(int row, int col, int value);

    string findWord(int columnIndex);

    string findAddressColumn(int position);

    bool logicalAnd(bool a, bool b);

    string f1(const string& firstWord, const string& secondWord);

    string f3(const string& firstWord);

    bool logicalNot(bool a);

    string f12(const string& firstWord);

    string f14(const string& firstWord, const string& secondWord);

    void setWordInColumn(const string& word, int columnIndex);

    int findWordPosition(const string& searchedWord, bool condition);

    string summa(const string& key);
};
