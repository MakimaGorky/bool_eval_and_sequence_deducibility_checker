#include <iostream>
#include "pre_process.h"
#include "Quine_meth.h"

vector<string> taskPool {
                         // from homeWork
                         "(a | (c > b)) / (a & c > b) ",
                         "a ~ b, a ~ c / a ~ (b > c) ",
                         "c > (b > a) / (b & !a) > (a & !c) ",
                         "b > c / (c > a) > (b > (a & !c)) ",
                         "(a > b) & (b > c) > (c > a) ",
                         "(b | c) / ((!b&c)|(b>c)) ",
                         "",
                         "",
                         "",
                         "",
                         "",
                         "",
                         // additional for test
                         // space after expression is the most important part
                         "a > b / (a > !b) > !a ",
                         "(a > (c > b)) / ((a & c) > b) ",
                         ""
                        };

///
int main() {
//    string inp = taskPool[13];
    string inp = readInput();

    stack<string> uExprs;
    parseInput1(inp, uExprs);

    vector<string> exprs;

    parseExpressions(uExprs, exprs);

//    //it's easier to debug like this
//    for (int i = 0; i < exprs.size(); ++i) {
//        std::cout << exprs[i] << " - ";
//    }
//    std::cout << std::endl;

    map<string, bool> vars;
    getVariables(inp, vars);

    //there is no truth table printing here, but I can live with it
    if (derivCheckQuine(exprs, vars)) {
        std::cout << "this equasion is deducible! 😎" << std::endl;
    }
    else {
        std::cout << "this equasion isn't deducible 😥" << std::endl;
    }

    return 0;
}
