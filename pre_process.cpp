#include "pre_process.h"
#include "String"
#include "iostream"
#include "stack"
#include "queue"
#include "vector"
#include <array>
#include "algorithm"
#include "map"

using std::string, std::cin, std::cout, std::endl, std::vector, std::stack, std::map;

char help_button = 'H';
//TODO make format string‼
string starting_text = "Hello and Welcome to the sequence derivation checker!\nPress 'H' for help. Pls dont type excessive symbols!!\nLets check your sequence!";
string help_text = "for help ask my developer";

void handleHelpButton(const string &input){
    if ((input[0] == std::tolower(help_button)
        || input[0] == std::toupper(help_button))
        && (input.size() == 1) ) {

        cout << help_text;
    }
}

std::string readInput() {
    cout << starting_text << endl;

    string input;
    std::getline(cin, input); // cin.getline(input, 1024);

    handleHelpButton(input);

    return input + " ";
}

/// '/' is for |- ; '>' is for -> ; '+' is for xor ;
std::array<string, 9> special_symbols {"(", ")", "/", ">", "&", "!", "|", "~", "+"};

string stringSlice(const string &curString, int indStart, int indEnd) {
//    vector<char> res(indEnd - indStart + 1);
    string res = "";

    for (int ind = indStart; ind < indEnd; ind++){
        res.push_back(curString[ind]);
    }

    return res;
}

string getVariables(const string &input, vector<variable> variables) {
    int varStart = -1;
    int varEnd = -1;

    for (int i {}; i < input.size(); i++){
        string cur {input[i]};
        if (input[i] == ' '){
            varEnd = i;
            if (varStart != -1)
                variables.push_back(variable {stringSlice(input, varStart, varEnd), false});

            varStart = -1;
            continue;
        }
        else if (std::find(special_symbols.begin(), special_symbols.end(), cur) != special_symbols.end()){
            varEnd = i;
            if (varStart != -1)
                variables.push_back(variable {stringSlice(input, varStart, varEnd), false});

            varStart = -1;
            continue;
        }
        else {
            if (varStart == -1)
                varStart = i;
        }

    }
    return "variables success";
}

string getOperations(const string &input, stack<operation> &operations) {
    stack<string> opers;

    int varStart = -1;
    int varEnd = -1;

    for (int i {}; i < input.size(); i++){
        string cur {input[i]};
        if (input[i] == ' '){
            varEnd = i;
            if (varStart != -1)
                opers.push(stringSlice(input, varStart, varEnd));

            varStart = -1;
            continue;
        }
        else if (std::find(special_symbols.begin(), special_symbols.end(), cur) != special_symbols.end()){
            if (varStart == -1)
                varStart = i;
        }
        else {
            varEnd = i;
            if (varStart != -1)
                opers.push(stringSlice(input, varStart, varEnd));

            varStart = -1;
            continue;
        }

    }

    return "operations success";
}

string parseInput(const string &input, vector<variable> &variables, stack<operation> &operationStack) {
    cout << getVariables(input, variables) << endl;

    cout << getOperations(input, operationStack) << endl;


    return "success!";
}

string parseInput1(const string &input, stack<string> &unpExprs) {

    if ((input.find('/') == string::npos) &&
            (input.find(',') != string::npos))
        return "wrong commas";
    if (std::count(input.begin(), input.end(),'/') > 1)
        return "wrong '/'";

    int consequenceBarrier = false;
    int indStart = -1;

    for (int i = 0; i < input.size(); i++){
        char cur = input[i];
        if (cur == ' '){
            continue;
        }
        else if ((cur == ',') || (cur == '/')){
            if ((indStart == -1) || (consequenceBarrier && (cur == ',')))
                return "error with ',' on " + std::to_string(i);
            if (!consequenceBarrier)
                consequenceBarrier = cur == '/';

            unpExprs.push(stringSlice(input, indStart, i));
            indStart = -1;
        }
        else{
            if (indStart == -1)
                indStart = i;
        }
    }
    if (indStart != -1)
        unpExprs.push(stringSlice(input, indStart, input.size()));

    return "success, but not flexible";
}

string getVariables(const string &input, map<string, bool> &dict) {
    int varStart = -1;
    int varEnd = -1;

    for (int i {}; i < input.size(); i++){
        string cur {input[i]};
        if ((cur == " ") || (cur == ",")){
            varEnd = i;
            if (varStart != -1)
                dict[stringSlice(input, varStart, varEnd)] = false;

            varStart = -1;
            continue;
        }
        if (std::find(special_symbols.begin(), special_symbols.end(), cur) != special_symbols.end()){
            varEnd = i;
            if (varStart != -1)
                dict[stringSlice(input, varStart, varEnd)] = false;

            varStart = -1;
            continue;
        }
        else {
            if (varStart == -1)
                varStart = i;
        }

    }
    return "variables success";
}

bool implication(bool oper1, bool oper2) {
    return !oper1 || oper2;
}

inline int operationPriority(const string &operation){
    special_symbols;
    if (operation == "!")
        return 4;
    if ((operation == "&"))
        return 3;
    if ((operation == "|") || (operation == "+"))
        return 2;
    if ((operation == ">") || (operation == "~"))
        return 1;
}

string polishizeExpr(const string &expr) {
    string res {};
    stack<string> stck;
    special_symbols;

    int ind = 0;
    while (ind < expr.size()) {
        string cur {expr[ind]};
        if (std::find(special_symbols.begin(), special_symbols.end(), cur) != special_symbols.end()){
            if (cur == "(")
                stck.push(cur);
            else if (cur == ")") {
                while (stck.top() != "(") {
                    auto temp = stck.top();
                    stck.pop();
                    res.append(temp);
                }
                stck.pop();
            }
            else {
                while (!stck.empty() && (operationPriority(cur) <= operationPriority(stck.top()))) {
                    auto temp = stck.top();
                    stck.pop();
                    res.append(temp);
                }

                stck.push(cur);
            }
        }
        else if (cur == " ") {
            ind++;
            continue;
        }
        else {
            res.append(cur);
        }
        ind++;
    }

    while (!stck.empty()){
        auto temp = stck.top();
        stck.pop();
        res.append(temp);
    }

    return res;
}

string parseExpressions(stack<string> &unpExprs, vector<string> &rpnExprs) {
    while (!unpExprs.empty()){
        auto expr = unpExprs.top(); unpExprs.pop();
        rpnExprs.push_back(polishizeExpr(expr));
    }
    return "succesfully polishized!";
}

bool solveExpr(const string &expr, map<string, bool> varVal) {
    stack<bool> stck;
    string curName {};
    special_symbols;
    for (int i = 0; i < expr.size(); ++i) {
        string cur {expr[i]};
        if (cur == " "){
            continue;
        }
        else if (cur == ">"){
            bool oper1 = stck.top(); stck.pop();
            bool oper2 = stck.top(); stck.pop();
            stck.push(!oper2 || oper1);
        }
        else if (cur == "&"){
            bool oper1 = stck.top(); stck.pop();
            bool oper2 = stck.top(); stck.pop();
            stck.push(oper1 && oper2);
        }
        else if (cur == "|"){
            bool oper1 = stck.top(); stck.pop();
            bool oper2 = stck.top(); stck.pop();
            stck.push(oper1 || oper2);
        }
        else if (cur == "!"){
            bool oper1 = stck.top(); stck.pop();
            stck.push(!oper1);
        }
        else if (cur == "~"){
            bool oper1 = stck.top(); stck.pop();
            bool oper2 = stck.top(); stck.pop();
            stck.push((!oper1 && !oper2) || (oper1 && oper2));
        }
        else if (cur == "+"){
            bool oper1 = stck.top(); stck.pop();
            bool oper2 = stck.top(); stck.pop();
            stck.push((!oper1 && oper2) || (oper1 && !oper2));
        }
        else {
            curName = cur;
//            string next {expr[i + 1]};
//            if ((next != " ") && (std::find(special_symbols.begin(), special_symbols.end(), next) == special_symbols.end()))
//                curName.append(next);
//            else {
                stck.push(varVal[curName]);
//            }
        }
    }
    return stck.top();
}