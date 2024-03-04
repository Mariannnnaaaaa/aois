#pragma once
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class BinaryConverter {
private:
    int decimal_number;
    vector<int> binary;
public:
    void toBinary();

    vector<int> getOnesComplement() const;

    vector<int> getTwosComplement() const;

    BinaryConverter(int num) : decimal_number(num) { }

    void print() const;

    int toDecimal() const;

    vector<int> addBinary(const vector<int>& a, const vector<int>& b, int carry) const;

    BinaryConverter operator+(const BinaryConverter& other) const;

    BinaryConverter operator-(const BinaryConverter& other) const;

    vector<int> multiplyBinary(const vector<int>& num1, const vector<int>& num2) const;

    vector<int> normalizeBinary(vector<int>& result) const;

    BinaryConverter operator*(const BinaryConverter& other) const;

    void checkDivideByZero(const BinaryConverter& other) const;

    BinaryConverter operator/(const BinaryConverter& other) const;
};