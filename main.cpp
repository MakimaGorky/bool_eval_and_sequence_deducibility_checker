#include <iostream>
#include "pre_process.h"
#include "Quine_meth.h"

vector<string> taskPool {
                         // from homeWork
                         "(a | (c > b)) / (a & c > b) ", // 0
                         "a ~ b, a ~ c / a ~ (b > c) ", // 0
                         "c > (b > a) / (b & !a) > (a & !c) ", // 0
                         "b > c / (c > a) > (b > (a & !c)) ", // 0
                         "(a > b) & (b > c) > (c > a) ", // 0
                         "(b | c) / ((!b&c)|(b>c)) ", // 0
                         "(a|!c>a&b)/(a>!a)|c&!b ", // 0
                         "((a>b)>a)/a ", // 1
                         "((c&b)|a)/((c|b)&(c|a) ", // 0
                         "ч>х/(х>ф)>(ч>(ф|!х)) ", // 1
                         "f|x,k|!x/f|k ", // 1
                         "!f>(k&x)/(k&x)>f ", // 0
                         // additional for test
                         // space after expression is the most important part
                         "a > b / (a > !b) > !a ", // 1
                         "(a > (c > b)) / ((a & c) > b) ", // 1
                         ""
                        };

///
int main() {

//    for (int i = 0; i< taskPool.size(); ++i)
    {
//        std::cout << i << " ";
//        string inp = taskPool[i];
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
            std::cout << "1: this expression is deducible! 😎" << std::endl;
        }
        else {
            std::cout << "0: this expression isn't deducible 😥" << std::endl;
        }

    }
    return 0;
}
