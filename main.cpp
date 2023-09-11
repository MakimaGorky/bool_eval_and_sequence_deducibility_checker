#include <iostream>
#include "pre_process.h"
#include "Quine_meth.h"

vector<string> taskPool {
                         // from homeWork
                         "(a | (c > b)) / (a & c > b) ",
                         "a ~ b, a ~ c / a ~ (b > c)",
                         "c > (b > a) / (b & !a) > (a & !c)",
                         "b > c / (c > a) > (b > (a & !c))",
                         "(a > b) & (b > c) > (c > a)",
                         "(b | c) / ((!b&c)|(b>c))",
                         "",
                         "",
                         "",
                         "",
                         "",
                         "",
                         // additional for test
                         "a > b / (a > !b) > !a",
                         "(a > (c > b)) / ((a & c) > b)",
                         ""
                        };

int main() {
    string inp = taskPool[13];

    stack<string> uExprs;
    parseInput1(inp, uExprs);

    vector<string> exprs;

    parseExpressions(uExprs, exprs);

//    //it's easier
//    for (int i = 0; i < exprs.size(); ++i) {
//        std::cout << exprs[i] << " - ";
//    }
//    std::cout << std::endl;

    map<string, bool> vars;
    getVariables(inp, vars);

    if (derivCheckQuine(exprs, vars)) {
        std::cout << "this equasion is deducible 😎" << std::endl;
    }
    else {
        std::cout << "this equasion isn't deducible 😥" << std::endl;
    }

    return 0;
}
