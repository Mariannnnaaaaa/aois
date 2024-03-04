#pragma once
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class FloatingPointConverter {
    private:
    int sign;
    vector<int> exponent;
    vector<int> mantissa;

public:
    FloatingPointConverter() {}

    void convertIntegerPart(int intValue);

    void convertFractionalPart(float fracValue);

    void convertSign(float value);

    void convertValues(float value);

    void adjustMantissa();

    void convertExponent();

    FloatingPointConverter(float value);

    void print();

    float convertToDecimal();


    bool isZero(FloatingPointConverter& fp);

    void calculateExponentValue(FloatingPointConverter& fp, int& exponentValue);

    void adjustMantissaForExponentDifference(FloatingPointConverter& fp, int exponentDifference);

    void adjustMantissaSize(vector<int>& mantissa);

    void printMantissa(vector<int>& mantissa);

    void calculateMantissa(bool carry, FloatingPointConverter& result, vector<int>& mantissa1, vector<int>& mantissa2);

    void adjustExponentForCarry(FloatingPointConverter& result);

    FloatingPointConverter operator+(FloatingPointConverter& other);
};