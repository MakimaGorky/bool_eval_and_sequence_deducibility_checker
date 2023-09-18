#ifndef SEQDERIVCHECK_QUINE_METH_H
#define SEQDERIVCHECK_QUINE_METH_H

#include "pre_process.h"

void expressionPrint(string baseExpression, map<string, bool> variableValues);

bool derivCheckQuine(string &baseExpression, vector<string> expressions, map<string, bool> &variableValues);

#endif //SEQDERIVCHECK_QUINE_METH_H
