#include "BinaryConverter.h"
using namespace std;

void BinaryConverter::toBinary() {
    int num = abs(decimal_number);
    while (num > 0) {
        binary.insert(binary.begin(), num % 2);
        num /= 2;
    }
    while (binary.size() < 8) binary.insert(binary.begin(), 0);
    if (decimal_number < 0) binary[0] = 1;
    else binary[0] = 0;
}

vector<int> BinaryConverter::getOnesComplement() const {
    vector<int> ones_complement = binary;
    if (binary[0] == 1) {
        for (int i = 1; i < ones_complement.size(); ++i) ones_complement[i] = 1 - ones_complement[i];
    }
    return ones_complement;
}

vector<int> BinaryConverter::getTwosComplement() const {
    vector<int> twos_complement = getOnesComplement();
    if (binary[0] == 1) {
        int carry = 1;
        for (int i = twos_complement.size() - 1; i >= 0; --i) {
            int sum = twos_complement[i] + carry;
            twos_complement[i] = sum % 2;
            carry = sum / 2;
        }
    }
    return twos_complement;
}

BinaryConverter::BinaryConverter(int num) : decimal_number(num) {
    toBinary();
}

void BinaryConverter::print() const {
    cout << "Binary representation: ";
    for (int bit : binary) cout << bit;
    cout << endl;

    cout << "Ones complement: ";
    for (int bit : getOnesComplement())  cout << bit;
    cout << endl;

    cout << "Twos complement: ";
    for (int bit : getTwosComplement())  cout << bit;
    cout << endl;
}

int BinaryConverter::toDecimal() const {
    int decimal = 0;
    int power = 0;
    int start = (binary[0] == 1) ? 1 : 0;
    for (int i = binary.size() - 1; i >= start; --i) {
        decimal += binary[i] * pow(2, power);
        ++power;
    }
    if (binary[0] == 1)  decimal = -decimal;
    return decimal;
}

vector<int> BinaryConverter::addBinary(const vector<int>& a, const vector<int>& b, int carry) const {
    vector<int> result(a.size(), 0);
    for (int i = a.size() - 1; i >= 0; --i) {
        int sum = a[i] + b[i] + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }
    return result;
}

BinaryConverter BinaryConverter::operator+(const BinaryConverter& other) const {
    if (binary[0] == 0 && other.binary[0] == 0) {
        int sum = decimal_number + other.decimal_number;
        return BinaryConverter(sum);
    }
    else if (binary[0] == 1 && other.binary[0] == 1) {
        vector<int> b1_twos_complement = getTwosComplement();
        vector<int> b2_twos_complement = other.getTwosComplement();
        int carry = 0;
        vector<int> result_binary = addBinary(b1_twos_complement, b2_twos_complement, carry);
        if (carry) result_binary[0] = result_binary[0] == 0 ? 1 : 0;
        BinaryConverter result(0);
        result.binary = result_binary;
        return result;
    }
    else {
        int sum = decimal_number + other.decimal_number;
        return BinaryConverter(sum);
    }
}

BinaryConverter BinaryConverter::operator-(const BinaryConverter& other) const {
    BinaryConverter neg_other = other;
    neg_other.decimal_number = -neg_other.decimal_number;
    neg_other.toBinary();
    return *this + neg_other;
}

vector<int> BinaryConverter::multiplyBinary(const vector<int>& num1, const vector<int>& num2) const {
    vector<int> result(16, 0);
    for (int i = 7; i >= 1; --i) {
        for (int j = 7; j >= 1; --j) result[i + j + 1] += num1[i] * num2[j];
    }
    return result;
}

vector<int> BinaryConverter::normalizeBinary(vector<int>& result) const {
    for (int i = 15; i > 0; --i) {
        if (result[i] > 1) {
            result[i - 1] += result[i] / 2;
            result[i] %= 2;
        }
    }
    return result;
}

BinaryConverter BinaryConverter::operator*(const BinaryConverter& other) const {
    vector<int> num1 = binary;
    vector<int> num2 = other.binary;
    vector<int> result = multiplyBinary(num1, num2);
    result = normalizeBinary(result);

    BinaryConverter product(0);
    product.binary = vector<int>(result.begin() + 9, result.end());
    if (binary[0] != other.binary[0]) product.binary.insert(product.binary.begin(), 1);
    else product.binary.insert(product.binary.begin(), 0);
    return product;
}

void BinaryConverter::checkDivideByZero(const BinaryConverter& other) const {
    if (other.toDecimal() == 0) throw runtime_error("Division by zero is not allowed.");
}

BinaryConverter BinaryConverter::operator/(const BinaryConverter& other) const {
    checkDivideByZero(other);
    int sign_a = binary[0] == 1 ? -1 : 1;
    int sign_b = other.binary[0] == 1 ? -1 : 1;
    BinaryConverter dividend(abs(decimal_number));
    BinaryConverter divisor(abs(other.decimal_number));
    BinaryConverter quotient(0);
    BinaryConverter remainder(0);
    while (dividend.toDecimal() >= divisor.toDecimal()) {
        remainder = dividend - divisor;
        dividend = remainder;
        quotient = quotient + BinaryConverter(1);
    }
    if (binary[0] != other.binary[0]) quotient.binary.insert(quotient.binary.begin(), 1);
    else quotient.binary.insert(quotient.binary.begin(), 0);
    return quotient;
}