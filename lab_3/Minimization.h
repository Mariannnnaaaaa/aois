#pragma once
#include <string>
#include <vector>
#include <set>
#include <stack>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

bool logicalAnd(bool a, bool b);

bool logicalOr(bool a, bool b);

bool logicalNot(bool a);

bool implication(bool a, bool b);

bool equivalention(bool a, bool b);

int precedence(char op);

string processOperator(stack<char>& st, string postfix, char c);

string processClosingParenthesis(stack<char>& st, string postfix);

string processRemainingOperators(stack<char>& st, string postfix);

string infixToPostfix(string s);


bool processUnaryOperator(char c, bool operand);

bool processBinaryOperator(char c, bool operand1, bool operand2);

vector<bool> evaluatePostfix(const string& postfixExpression, const vector<bool>& values);

void printHeader(const string& expression, const string& postfixExpression);

void printRow(const vector<bool>& values, const vector<bool>& results);

string updateSKNF(const vector<bool>& values, string sknf);

string updateSDNF(const vector<bool>& values, string sdnf);

void printSKNF(const string& sknf, const vector<int>& sknfIndices);

void printSDNF(const string& sdnf, const vector<int>& sdnfIndices);

vector<pair<int, int>> FindClauses(const string& sknf);

string ExtractClause(const string& sknf, int start, int end);

vector<string> Get_clauses(const string& sknf);

bool IsLiteralStart(char c);

string ExtractLiteral(const string& clause, size_t& pos);

vector<string> Get_lits(const string& clause);

string RemoveNegation(const string& lit);

vector<string> NormalizeLiterals(const vector<string>& lits);

bool EqualLetters(const vector<string>& lits1, const vector<string>& lits2);

bool IsDelimiter(char c);

void AddToResult(vector<string>& result, string& temp);

vector<string> splitting(const string& input);

bool Original_substring(const string& subConstituent, const string& originalConstituent);

void PrintMergedClausesTable(const vector<string>& clauses, const vector<string>& originalClauses);

string MinimizeSDNF_Table(const string& sdnf);


string MinimizeSKNF_Table(const string& sknf);

void printKarnaughMap(const vector<vector<bool>>& kmap);

vector<vector<bool>> createKarnaughMap(const vector<int>& sdnfIndices);


void menu(int n, const string& expression);
