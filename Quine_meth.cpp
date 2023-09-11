#include "pre_process.h"
#include "cmath"

bool derivCheckQuine(vector<string> expressions, map<string, bool> &variableValues) {
    bool isDeriv = true;

    //getting 2^n lol
    unsigned long long maxPow = 1;
    for (int i = 0; i < variableValues.size(); i++)
        maxPow <<= 1;

    for (unsigned long long binNum = 0; binNum < maxPow; binNum++) {
        unsigned long long curBit = 1;
        for (auto &variable : variableValues) {
            variable.second = binNum & curBit;
            curBit <<= 1;
        }
        queue<bool> exprRes;
        stack<bool> res;
        for (int i = 0; i < expressions.size(); ++i) {
            exprRes.push(solveExpr(expressions[i], variableValues));
        }

        while (!exprRes.empty()) {
            res.push(exprRes.front()); exprRes.pop();
            if (res.size() == 2) {
                bool cur = res.top(); res.pop();
                bool prev = res.top(); res.pop();
                res.push(implication(cur, prev));
            }
        }
        if (!res.top()) {
            return false;
        }
    }

    return isDeriv;
}