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
    std::cout << parseInput1(inp, uExprs) << std::endl;

    vector<string> exprs;

    std::cout << parseExpressions(uExprs, exprs) << std::endl;

    for (int i = 0; i < exprs.size(); ++i) {
        std::cout << exprs[i] << " - ";
    }
    std::cout << std::endl;

    map<string, bool> vars;
    getVariables(inp, vars);

    std::cout << derivCheckQuine(exprs, vars);

    return 0;
}
