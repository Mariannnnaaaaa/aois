#include "Matrix.h"

Matrix::Matrix() : size(16) {
    int predefinedMatrix[16][16] = {
        {1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0},
        {1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1},
        {0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1},
        {0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
        {1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}
    };

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = predefinedMatrix[i][j];
        }
    }
}

void Matrix::printMatrix() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int Matrix::getSize() const {
    return size;
}

int Matrix::getElement(int row, int col) const {
    if (row >= 0 && row < size && col >= 0 && col < size) {
        return matrix[row][col];
    }
    else {
        throw out_of_range("Index out of range");
    }
}

void Matrix::setElement(int row, int col, int value) {
    if (row >= 0 && row < size && col >= 0 && col < size) {
        matrix[row][col] = value;
    }
    else {
        throw out_of_range("Index out of range");
    }
}

string Matrix::findWord(int columnIndex)
{
    string word;
    for (int i = 0; i < 16; i++)
    {
        int x = (columnIndex + i) % 16;
        word += to_string(matrix[x][columnIndex]);
    }
    return word;
}

string Matrix::findAddressColumn(int position) {
    string row;
    for (int i = 0; i < 16; i++)
    {
        int rowIndex = (position + i) % 16;
        row += to_string(matrix[rowIndex][i]);
    }
    return row;
}

bool Matrix::logicalAnd(bool a, bool b) {
    return a && b;
}

string Matrix::f1(const string& firstWord, const string& secondWord) {
    string result;
    for (int i = 0; i < firstWord.size(); i++) {
        bool a = (firstWord[i] == '1');
        bool b = (secondWord[i] == '1');
        result += logicalAnd(a, b) ? '1' : '0';
    }
    return result;
}

string Matrix::f3(const string& firstWord) {
    return firstWord;
}

bool Matrix::logicalNot(bool a) {
    return !a;
}

string Matrix::f12(const string& firstWord) {
    string result;
    for (int i = 0; i < firstWord.size(); i++) {
        bool a = (firstWord[i] == '1');
        bool negatedA = !a;
        result += (negatedA ? '1' : '0');
    }
    return result;
}

string Matrix::f14(const string& firstWord, const string& secondWord) {
    string result;
    for (int i = 0; i < firstWord.size(); i++) {
        bool a = (firstWord[i] == '1');
        bool negatedA = !a;
        bool b = (secondWord[i] == '1');
        bool negatedB = !b;
        result += logicalAnd(negatedA, negatedB) ? '1' : '0';
    }
    return result;
}

void Matrix::setWordInColumn(const string& word, int columnIndex) {
    for (int i = 0; i < size; i++) {
        int x = (columnIndex + i) % 16;
        matrix[x][columnIndex] = (word[i] == '1') ? 1 : 0;
    }
}

int Matrix::findWordPosition(const string& searchedWord, bool condition) {
    int searchedNum = stoi(searchedWord, nullptr, 2);

    int bestNum = condition ? INT_MAX : INT_MIN;
    int bestIndex = -1;

    for (int i = 0; i < 16; i++) {
        string word = findWord(i);
        int wordNum = stoi(word, nullptr, 2);

        if ((condition && wordNum > searchedNum && wordNum < bestNum) ||
            (!condition && wordNum < searchedNum && wordNum > bestNum)) {
            bestNum = wordNum;
            bestIndex = i;
        }
    }

    return bestIndex;
}

string Matrix::summa(const string& key) {
    string result;
    int index = -1;

    for (int i = 0; i < 16; ++i) {
        string word = findWord(i);
        if (word.substr(0, 3) == key) {
            result = word;
            index = i;
            break;
        }
    }

    if (index == -1) {
        throw invalid_argument("No word starts with the given key.");
    }

    string V = result.substr(0, 3);
    string A = result.substr(3, 4);
    string B = result.substr(7, 4);
    string S = result.substr(11, 5);

    int numA = stoi(A, nullptr, 2);
    int numB = stoi(B, nullptr, 2);

    int sum = numA + numB;
    bitset<5> binarySum(sum);
    S = binarySum.to_string();
    result = V + A + B + S;
    return result;
}