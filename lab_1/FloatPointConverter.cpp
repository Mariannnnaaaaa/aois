#include "FloatPointConverter.h"
using namespace std;

FloatingPointConverter::FloatingPointConverter() {}

void FloatingPointConverter::convertIntegerPart(int intValue) {
    while (intValue) {
        exponent.insert(exponent.begin(), intValue % 2);
        intValue /= 2;
    }
}

void FloatingPointConverter::convertFractionalPart(float fracValue) {
    int bit;
    while (mantissa.size() < 23) {
        fracValue *= 2;
        bit = fracValue >= 1.0 ? 1 : 0;
        mantissa.push_back(bit);
        if (bit == 1) fracValue -= 1.0;
    }
    while (mantissa.size() < 23) mantissa.push_back(0);
}

void FloatingPointConverter::convertSign(float value) {
    sign = (value >= 0) ? 0 : 1;
}

void FloatingPointConverter::convertValues(float value) {
    int intValue = (int)value;
    float fracValue = value - intValue;
    convertIntegerPart(intValue);
    convertFractionalPart(fracValue);
}

void FloatingPointConverter::adjustMantissa() {
    for (int i = exponent.size() - 1; i >= 1; --i) {
        mantissa.insert(mantissa.begin(), exponent[i]);
    }
    while (mantissa.size() > 23) {
        mantissa.pop_back();
    }
}

void FloatingPointConverter::convertExponent() {
    int bias = 127;
    int expValue = exponent.size() - 1 + bias;
    exponent.clear();
    convertIntegerPart(expValue);
}

FloatingPointConverter::FloatingPointConverter(float value) {
    convertSign(value);
    convertValues(value);
    adjustMantissa();
    convertExponent();
}

void FloatingPointConverter::print() {
    cout << "Sign: " << sign << endl;
    cout << "Exponent: ";
    for (int i = 0; i < exponent.size(); ++i) {
        cout << exponent[i];
    }
    cout << endl;
    cout << "Mantissa: ";
    for (int i = 0; i < mantissa.size(); ++i) {
        cout << mantissa[i];
    }
    cout << endl;
}

float FloatingPointConverter::convertToDecimal() {
    int expValue = 0;
    for (int i = 0; i < exponent.size(); ++i) {
        expValue = expValue * 2 + exponent[i];
    }
    int bias = 127;
    expValue -= bias;
    float mantValue = 1.0;
    for (int i = 0; i < mantissa.size(); ++i) {
        mantValue += mantissa[i] * pow(2, -i - 1);
    }
    float value = pow(2, expValue) * mantValue;
    if (sign == 1) value = -value;
    return value;
}


bool FloatingPointConverter::isZero(FloatingPointConverter& fp) {
    return (fp.mantissa == vector<int>(23, 0) && fp.exponent == vector<int>(8, 0));
}

void FloatingPointConverter::calculateExponentValue(FloatingPointConverter& fp, int& exponentValue) {
    for (int i = 0; i < fp.exponent.size(); ++i) exponentValue = exponentValue * 2 + fp.exponent[i];
}

void FloatingPointConverter::adjustMantissaForExponentDifference(FloatingPointConverter& fp, int exponentDifference) {
    fp.mantissa.insert(fp.mantissa.begin(), 1);
    for (int i = 0; i < exponentDifference - 1; ++i) fp.mantissa.insert(fp.mantissa.begin(), 0);
}

void FloatingPointConverter::adjustMantissaSize(vector<int>& mantissa) {
    while (mantissa.size() > 23) mantissa.pop_back();
}

void FloatingPointConverter::printMantissa(vector<int>& mantissa) {
    for (int i = 0; i < mantissa.size(); ++i) {
        cout << mantissa[i];
    }
    cout << "\n";
}

void FloatingPointConverter::calculateMantissa(bool carry, FloatingPointConverter& result, vector<int>& mantissa1, vector<int>& mantissa2) {
    bool carry = 0;
    for (int i = mantissa1.size() - 1; i >= 0; --i) {
        int sum = mantissa1[i] + mantissa2[i] + carry;
        result.mantissa.insert(result.mantissa.begin(), sum % 2);
        carry = sum / 2;
    }
}

void FloatingPointConverter::adjustExponentForCarry(FloatingPointConverter& result) {
    if (result.exponent.back() == 2) {
        int carry = 0;
        for (int i = result.exponent.size() - 1; i >= 0; --i) {
            int sum = result.exponent[i] + carry;
            result.exponent[i] = sum % 2;
            carry = sum / 2;
        }
    }
}

FloatingPointConverter FloatingPointConverter::operator+(FloatingPointConverter& other) {
    if (isZero(*this)) return other;
    if (isZero(other)) return *this;

    FloatingPointConverter result;
    bool thisExponentGreater = false;
    int exponentValue = 0;
    int otherExponentValue = 0;

    calculateExponentValue(*this, exponentValue);
    calculateExponentValue(other, otherExponentValue);

    int exponentDifference = exponentValue - otherExponentValue;

    if (exponentDifference > 0) {
        thisExponentGreater = true;
        adjustMantissaForExponentDifference(other, exponentDifference);
    }
    else if (exponentDifference < 0) {
        thisExponentGreater = false;
        exponentDifference = abs(exponentDifference);
        adjustMantissaForExponentDifference(*this, exponentDifference);
    }

    if (thisExponentGreater) result.exponent = exponent;
    else result.exponent = other.exponent;

    adjustMantissaSize(mantissa);
    adjustMantissaSize(other.mantissa);

    cout << "Mantissa1: ";
    printMantissa(mantissa);
    cout << "Mantissa2: ";
    printMantissa(other.mantissa);

    bool carry = 0;
    calculateMantissa(carry, result, mantissa, other.mantissa);

    if (carry) {
        result.mantissa.insert(result.mantissa.begin(), 0);
        ++result.exponent.back();
    }

    adjustExponentForCarry(result);

    adjustMantissaSize(result.mantissa);
    return result;
}