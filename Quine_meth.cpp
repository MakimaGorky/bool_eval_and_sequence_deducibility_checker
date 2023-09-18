#include "pre_process.h"
#include "cmath"

bool microSolve(string expression, map<string, bool> assignedVars, map<string, bool> allVars) {
    map<string, bool> localVars;
    for (auto var : allVars){
        if (assignedVars.find(var.first) == assignedVars.end()) {
            localVars[var.first] = false;
        }
    }

    unsigned long long maxPow = 1;
    for (int i = 0; i < localVars.size(); i++)
        maxPow <<= 1;

    unsigned long long binNum = 0;

    bool isAbsoluteTrue = true;

    for (unsigned long long binNum = 0; binNum < maxPow; binNum++) {
        unsigned long long curBit = 1;
        for (auto &variable : localVars) {
            variable.second = binNum & curBit;
            curBit <<= 1;
        }
        map<string, bool> curVals;

        for (auto v : localVars)
            curVals[v.first] = v.second;
        for (auto v : assignedVars)
            curVals[v.first] = v.second;

        isAbsoluteTrue = isAbsoluteTrue && solveExpr(expression, curVals);

    }

    return isAbsoluteTrue;
}

void expressionPrint(string baseExpression, map<string, bool> variableValues) {
//    std::cout << "ahahahahah" << std::endl;
    string baseExprRPN = polishizeExpr(baseExpression);

    unsigned long long maxPow = 1;
    for (int i = 0; i < variableValues.size(); i++)
        maxPow <<= 1;

    unsigned long long binNum = 0;

    while (binNum < maxPow) {
        unsigned long long curBit = 1;
        for (auto &variable : variableValues) {
            variable.second = binNum & curBit;
            curBit <<= 1;
        }
        map<string, bool> curVars;
        int ind = variableValues.size() - 1;
        for (auto &var : variableValues) {
            int binPow = (int) pow(2, ind);
            var.second = binNum & binPow;
            curVars[var.first] = var.second;

            string cuteSpaces {};

            for (int i = (binPow == 1) ? 0 : binPow; i < maxPow / 2; ++i)
                cuteSpaces.append(" ");

            std::cout << cuteSpaces << "for " << var.first << " = " << var.second << ": \n" << cuteSpaces;

            string res {};

            for (int i = 0; i < baseExpression.size(); ++i) {
                const string cur {baseExpression[i]};

                if (curVars.find(cur) != curVars.end()) {
                    auto val = variableValues[cur];
                    res.append(std::to_string(val));
                }
                else {
                    res.append(cur);
                }
            }
            bool needCont = !microSolve(baseExprRPN, curVars, variableValues);
            if (!needCont) {
                std::cout << res << " = 1\n";
                //todo binNum += ?
                binNum += (int) pow(2, ind) - 1;
                break;
            }
            else {
                if (ind != 0) {
                    std::cout << res << " = ?\n";
                }
                else {
                    std::cout << res << " = 0\n";
                    return;
                }
            }


            --ind;
        }

        ++binNum;
    }

}

bool derivCheckQuine(string &baseExpression, vector<string> expressions, map<string, bool> &variableValues) {
//    std::cout << "ahahaha";

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
            auto res = solveExpr(expressions[i], variableValues);
            exprRes.push(res);
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
            isDeriv = false;
        }
    }

    return isDeriv;
}