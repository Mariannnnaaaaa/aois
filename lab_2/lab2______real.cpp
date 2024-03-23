#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stack>
using namespace std;

bool logicalAnd(bool a, bool b) {
    return a && b;
}

bool logicalOr(bool a, bool b) {
    return a || b;
}

bool logicalNot(bool a) {
    return !a;
}

bool implication(bool a, bool b) {
    if (a == true && b == false) return false;
    else return true;
}

bool equivalention(bool a, bool b) {
    if ((a == true && b == true) || (a == false && b == false)) return true;
    else return false;
}

int precedence(char op) {
    if (op == '!') return 3;
    if (op == '&' || op == '|') return 2;
    if (op == '>' || op == '~') return 1;
    return 0;
}

string processOperator(stack<char>& st, string postfix, char c) {
    while (!st.empty() && precedence(c) <= precedence(st.top())) {
        postfix += st.top();
        st.pop();
    }
    st.push(c);
    return postfix;
}

string processClosingParenthesis(stack<char>& st, string postfix) {
    while (!st.empty() && st.top() != '(') {
        postfix += st.top();
        st.pop();
    }
    st.pop();
    return postfix;
}

string processRemainingOperators(stack<char>& st, string postfix) {
    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }
    return postfix;
}

string infixToPostfix(string s) {
    stack<char> st;
    string postfix;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (isalpha(c)) postfix += c;
        else if (c == '&' || c == '|' || c == '!' || c == '>' || c == '~') {
            postfix = processOperator(st, postfix, c);
        }
        else if (c == '(') st.push(c);
        else if (c == ')') {
            postfix = processClosingParenthesis(st, postfix);
        }
    }
    postfix = processRemainingOperators(st, postfix);
    return postfix;
}


bool processUnaryOperator(char c, bool operand) {
    if (c == '!') return logicalNot(operand);
    return false;
}

bool processBinaryOperator(char c, bool operand1, bool operand2) {
    if (c == '&') return logicalAnd(operand1, operand2);
    else if (c == '|') return logicalOr(operand1, operand2);
    else if (c == '>') return implication(operand1, operand2);
    else if (c == '~') return equivalention(operand1, operand2);
    return false;
}

vector<bool> evaluatePostfix(const string& postfixExpression, const vector<bool>& values) {
    stack<bool> st;
    vector<bool> results;
    for (char c : postfixExpression) {
        if (isalpha(c)) st.push(values[c - 'a']);
        else {
            bool result;
            bool operand2 = st.top(); st.pop();

            if (c == '!') result = processUnaryOperator(c, operand2);
            else {
                bool operand1 = st.top(); st.pop();
                result = processBinaryOperator(c, operand1, operand2);
            }
            st.push(result);
            results.push_back(result);
        }
    }
    return results;
}

int binaryToDecimal(const std::vector<int>& decimalResult) {
    int decimal = 0;
    int base = 1;

    for (int i = decimalResult.size() - 1; i >= 0; --i) {
        if (decimalResult[i] == 1) decimal += base;
        base *= 2;
    }
    return decimal;
}

void printHeader(const string& expression, const string& postfixExpression) {
    for (char c : expression) {
        if (isalpha(c)) cout << c << "\t";
    }

    for (char c : postfixExpression) {
        if (c == '&' || c == '|' || c == '!' || c == '>' || c == '~') cout << c << "\t";
    }
    cout << endl;
}

void printRow(const vector<bool>& values, const vector<bool>& results) {
    for (int j = 0; j < values.size(); ++j) {
        cout << values[j] << "\t";
    }

    for (bool result : results) {
        cout << result << "\t";
    }
    cout << "\n";
}

string updateSKNF(const vector<bool>& values, string sknf) {
    sknf += "(";
    for (int j = 0; j < values.size(); ++j) {
        sknf += (values[j] ? "!" : "") + string(1, 'a' + j) + (j < values.size() - 1 ? " | " : "");
    }
    sknf += ") & ";
    return sknf;
}

string updateSDNF(const vector<bool>& values, string sdnf) {
    sdnf += "(";
    for (int j = 0; j < values.size(); ++j) {
        sdnf += (values[j] ? "" : "!") + string(1, 'a' + j) + (j < values.size() - 1 ? " & " : "");
    }
    sdnf += ") | ";
    return sdnf;
}

void printSKNF(const string& sknf, const vector<int>& sknfIndices) {
    cout << "SKNF: " << sknf << "\n";
    cout << "SKNF Indices: ";
    for (int index : sknfIndices) {
        cout << index << " ";
    }
    cout << "\n";
}

void printSDNF(const string& sdnf, const vector<int>& sdnfIndices) {
    cout << "SDNF: " << sdnf << "\n";
    cout << "SDNF Indices: ";
    for (int index : sdnfIndices) {
        cout << index << " ";
    }
    cout << "\n";
}

int printTruthTable(int n, const string& expression) {
    string postfixExpression = infixToPostfix(expression);
    int totalRows = 1 << n;

    printHeader(expression, postfixExpression);

    string sknf;
    string sdnf;
    vector<int> sknfIndices;
    vector<int> sdnfIndices;
    vector<int> decimalResult;
    int binary_result = 0;

    for (int i = 0; i < totalRows; ++i) {
        vector<bool> values(n);
        for (int j = 0; j < n; ++j) {
            values[n - j - 1] = (i & (1 << j)) != 0;
        }

        vector<bool> results = evaluatePostfix(postfixExpression, values);
        printRow(values, results);

        decimalResult.push_back(results.back());
        binary_result = binaryToDecimal(decimalResult);

        if (results.back() == 0) {
            sknf = updateSKNF(values, sknf);
            sknfIndices.push_back(i);
        }
        else {
            sdnf = updateSDNF(values, sdnf);
            sdnfIndices.push_back(i);
        }
    }

    if (!sknf.empty()) sknf.erase(sknf.size() - 3);
    if (!sdnf.empty()) sdnf.erase(sdnf.size() - 3);

    printSKNF(sknf, sknfIndices);
    printSDNF(sdnf, sdnfIndices);

    cout << "Decimal representation of the result: " << binary_result << "\n";
    return binary_result;
}