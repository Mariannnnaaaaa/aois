#include "Minimization.h"

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
        sknf += (values[j] ? "!" : "") + string(1, 'a' + j) + (j < values.size() - 1 ? "|" : "");
    }
    sknf += ")&";
    return sknf;
}

string updateSDNF(const vector<bool>& values, string sdnf) {
    sdnf += "(";
    for (int j = 0; j < values.size(); ++j) {
        sdnf += (values[j] ? "" : "!") + string(1, 'a' + j) + (j < values.size() - 1 ? "&" : "");
    }
    sdnf += ")|";
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

vector<pair<int, int>> FindClauses(const string& sknf) {
    vector<pair<int, int>> positions;
    int openBracket = 0;
    int shift = 0;

    for (size_t i = 0; i < sknf.length(); ++i) {
        if (sknf[i] == '(') {
            if (shift == 0) {
                openBracket = i;
            }
            shift++;
        }
        else if (sknf[i] == ')') {
            shift--;
            if (shift == 0) {
                positions.push_back(make_pair(openBracket, i));
            }
        }
    }

    return positions;
}

string ExtractClause(const string& sknf, int start, int end) {
    return sknf.substr(start, end - start + 1);
}

vector<string> Get_clauses(const string& sknf) {
    vector<string> clauses;
    vector<pair<int, int>> positions = FindClauses(sknf);

    for (const auto& pos : positions) {
        clauses.push_back(ExtractClause(sknf, pos.first, pos.second));
    }

    return clauses;
}

bool IsLiteralStart(char c) {
    return isalpha(c) || c == '!';
}

string ExtractLiteral(const string& clause, size_t& pos) {
    if (clause[pos] == '!') {
        if (pos + 1 < clause.length() && isalpha(clause[pos + 1])) {
            return string(1, '!') + clause[++pos];
        }
    }
    else if (isalpha(clause[pos])) {
        return string(1, clause[pos]);
    }
    return "";
}

vector<string> Get_lits(const string& clause) {
    vector<string> lits;
    for (size_t i = 0; i < clause.length(); ++i) {
        if (IsLiteralStart(clause[i])) {
            string lit = ExtractLiteral(clause, i);
            if (!lit.empty()) {
                lits.push_back(lit);
            }
        }
    }
    return lits;
}

string RemoveNegation(const string& lit) {
    return lit.substr(lit.find_first_not_of('!'));
}

vector<string> NormalizeLiterals(const vector<string>& lits) {
    vector<string> normalized;
    for (const string& lit : lits) {
        normalized.push_back(RemoveNegation(lit));
    }
    sort(normalized.begin(), normalized.end());
    return normalized;
}

bool EqualLetters(const vector<string>& lits1, const vector<string>& lits2) {
    vector<string> normalizedLits1 = NormalizeLiterals(lits1);
    vector<string> normalizedLits2 = NormalizeLiterals(lits2);
    return normalizedLits1 == normalizedLits2;
}

bool IsDelimiter(char c) {
    return c == '|' || c == '(' || c == ')' || c == ' ' || c == '&';
}

void AddToResult(vector<string>& result, string& temp) {
    if (!temp.empty()) {
        result.push_back(temp);
        temp.clear();
    }
}

vector<string> splitting(const string& input) {
    vector<string> result;
    string temp = "";
    for (char c : input) {
        if (c == '!') {
            temp += c;
            continue;
        }
        if (IsDelimiter(c)) {
            AddToResult(result, temp);
            continue;
        }
        temp += c;
    }
    AddToResult(result, temp);
    return result;
}

bool Original_substring(const string& subConstituent, const string& originalConstituent) {
    vector<string> sublits = splitting(subConstituent);
    vector<string> originallits = splitting(originalConstituent);

    for (const string& lit : sublits) {
        if (find(originallits.begin(), originallits.end(), lit) == originallits.end()) {
            return false;
        }
    }
    return true;
}

void PrintMergedClausesTable(const vector<string>& clauses, const vector<string>& originalClauses) {
    cout << "Table of Merged Clauses:\n";
    cout << setw(15) << " ";
    for (const auto& clause : originalClauses) {
        cout << setw(15) << clause;
    }
    cout << endl;

    for (size_t i = 0; i < clauses.size(); ++i) {
        cout << setw(15) << clauses[i];
        for (size_t j = 0; j < originalClauses.size(); ++j) {
            if (originalClauses[j].find(clauses[i])) {
                bool containsSubstring = Original_substring(clauses[i], originalClauses[j]);
                if (containsSubstring) {
                    cout << setw(15) << "X";
                }
                else {
                    cout << setw(15) << " ";
                }
            }
            else {
                cout << setw(15) << " ";
            }
        }
        cout << endl;
    }
}

string MinimizeSDNF_Table(const string& sdnf) {
    vector<string> clauses = Get_clauses(sdnf);
    if (clauses.empty() || clauses.size() == 1) {
        return clauses.empty() ? "" : clauses[0];
    }

    string result;
    bool changed = true;
    int stage = 1;
    while (changed) {
        bool merged = false;
        vector<string> newClauses;
        changed = false;

        cout << "Stage " << stage << ":\n";

        for (size_t i = 0; i < clauses.size(); ++i) {
            merged = false;
            for (size_t j = 0; j < clauses.size(); ++j) {
                if (i != j) {
                    vector<string> lits1 = Get_lits(clauses[i]);
                    vector<string> lits2 = Get_lits(clauses[j]);

                    vector<string> matchinglits;
                }
            }
        }

        for (size_t i = 0; i < clauses.size(); ++i) {
            merged = false;
            for (size_t j = 0; j < clauses.size(); ++j) {
                if (i != j) {
                    vector<string> lits1 = Get_lits(clauses[i]);
                    vector<string> lits2 = Get_lits(clauses[j]);

                    vector<string> matchinglits;
                    if (EqualLetters(lits1, lits2)) {
                        for (const string& lit : lits1) {
                            if (find(lits2.begin(), lits2.end(), lit) != lits2.end()) {
                                matchinglits.push_back(lit);
                            }
                        }

                        if (matchinglits.size() >= lits1.size() - 1) {
                            string mergedClause = accumulate(matchinglits.begin() + 1, matchinglits.end(), matchinglits[0],
                                [](const string& a, const string& b) { return a + "&" + b; });
                            if (find(newClauses.begin(), newClauses.end(), mergedClause) == newClauses.end()) {
                                newClauses.push_back(mergedClause);
                                changed = true;
                                cout << "Merged: " << clauses[i] << " with " << clauses[j] << " -> " << mergedClause << endl;
                            }
                            merged = true;
                        }
                    }
                }
            }
            if (!merged) {
                newClauses.push_back(clauses[i]);
            }
        }
        clauses = newClauses;
        ++stage;
    }

    for (size_t i = 0; i < clauses.size(); ++i) {
        result += "(" + clauses[i] + ")";
        if (i < clauses.size() - 1) {
            result += " | ";
        }
    }

    PrintMergedClausesTable(clauses, Get_clauses(sdnf));
    return result;
}


string MinimizeSKNF_Table(const string& sknf) {
    vector<string> clauses = Get_clauses(sknf);
    if (clauses.empty() || clauses.size() == 1) {
        return clauses.empty() ? "" : clauses[0];
    }

    string result;
    bool changed = true;
    int stage = 1;
    while (changed) {
        bool merged = false;
        vector<string> newClauses;
        changed = false;

        cout << "Stage " << stage << ":\n";

        for (size_t i = 0; i < clauses.size(); ++i) {
            merged = false;
            for (size_t j = 0; j < clauses.size(); ++j) {
                if (i != j) {
                    vector<string> lits1 = Get_lits(clauses[i]);
                    vector<string> lits2 = Get_lits(clauses[j]);

                    vector<string> matchinglits;
                }
            }
        }

        for (size_t i = 0; i < clauses.size(); ++i) {
            merged = false;
            for (size_t j = 0; j < clauses.size(); ++j) {
                if (i != j) {
                    vector<string> lits1 = Get_lits(clauses[i]);
                    vector<string> lits2 = Get_lits(clauses[j]);

                    vector<string> matchinglits;
                    if (EqualLetters(lits1, lits2)) {
                        for (const string& lit : lits1) {
                            if (find(lits2.begin(), lits2.end(), lit) != lits2.end()) {
                                matchinglits.push_back(lit);
                            }
                        }

                        if (matchinglits.size() >= lits1.size() - 1) {
                            string mergedClause = accumulate(matchinglits.begin() + 1, matchinglits.end(), matchinglits[0],
                                [](const string& a, const string& b) { return a + "|" + b; });
                            if (find(newClauses.begin(), newClauses.end(), mergedClause) == newClauses.end()) {
                                newClauses.push_back(mergedClause);
                                changed = true;
                                cout << "Merged: " << clauses[i] << " with " << clauses[j] << " -> " << mergedClause << endl;
                            }
                            merged = true;
                        }
                    }
                }
            }
            if (!merged) {
                newClauses.push_back(clauses[i]);
            }
        }
        clauses = newClauses;
        ++stage;
    }

    for (size_t i = 0; i < clauses.size(); ++i) {
        result += "(" + clauses[i] + ")";
        if (i < clauses.size() - 1) {
            result += " & ";
        }
    }

    PrintMergedClausesTable(clauses, Get_clauses(sknf));
    return result;
}

void printKarnaughMap(const vector<vector<bool>>& kmap) {
    cout << "\nKarnaugh Map:\n";
    cout << "     00  01  11  10\n";
    cout << "   +---------------\n";
    for (int i = 0; i < 2; ++i) {
        cout << " " << i << " |";
        for (int j = 0; j < 4; ++j) {
            cout << "  " << kmap[i][j];
        }
        cout << "\n";
    }
}

vector<vector<bool>> createKarnaughMap(const vector<int>& sdnfIndices) {
    vector<vector<bool>> kmap(2, vector<bool>(4, false));
    for (int index : sdnfIndices) {
        int row = (index >> 2) & 1;
        int col = ((index >> 1) & 1) << 1 | (index & 1);
        kmap[row][col] = true;
    }
    return kmap;
}
