#ifndef SEQDERIVCHECK_PRE_PROCESS_H
#define SEQDERIVCHECK_PRE_PROCESS_H

#include "iostream"
#include "vector"
#include "stack"
#include "queue"
#include "map"

using std::string, std::vector, std::stack, std::map, std::queue;

//haha useless
struct variable {
    string name;
    bool value;
};

string readInput();
string stringSlice(const string &curString, int indStart, int indEnd);

string parseInput1(const string &input, stack<string> &unpExprs);

string getVariables(const string &input, map<string, bool> &dict);

bool implication(bool oper1, bool oper2);

string polishizeExpr(const string &expr);
string parseExpressions(stack<string> &unpExprs, vector<string> &rpnExprs);
bool solveExpr(const string &expr, map<string, bool> varVal);


#endif //SEQDERIVCHECK_PRE_PROCESS_H