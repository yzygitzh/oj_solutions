/*
 * POJ 3295 - Tautology
 *
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class WFFNode {
public:
    char op;
    int beg, end;
    WFFNode *left, *right;
    WFFNode(char _op): op(_op), beg(0), end(0), left(NULL), right(NULL) {}
};

WFFNode *getWFF(string &raw, int idx) {
    WFFNode *result = new WFFNode(raw[idx]);
    result->beg = idx;
    if (raw[idx] == 'N') {
        result->left = getWFF(raw, idx + 1);
        int leftLen = result->left->end - result->left->beg + 1;
        result->end = idx + leftLen;
    } else if ('A' <= raw[idx] && raw[idx] <= 'Z') {
        result->left = getWFF(raw, idx + 1);
        int leftLen = result->left->end - result->left->beg + 1;
        result->right = getWFF(raw, idx + leftLen + 1);
        int rightLen = result->right->end - result->right->beg + 1;
        result->end = idx + leftLen + rightLen;
    } else {
        result->end = idx;
    }
    return result;
}

void freeWFF(WFFNode *p) {
    if (p == NULL) return;
    freeWFF(p->left);
    freeWFF(p->right);
    delete p;
}

// least five significant bits: p, q, r, s, t
bool evalWFF(WFFNode *p, unsigned elements) {
    if ('a' <= p->op && p->op <= 'z') {
        return (elements & (1 << (p->op - 'p')));
    } else if (p->op == 'K') {
        return evalWFF(p->left, elements) && evalWFF(p->right, elements);
    } else if (p->op == 'A') {
        return evalWFF(p->left, elements) || evalWFF(p->right, elements);
    } else if (p->op == 'N') {
        return !evalWFF(p->left, elements);
    } else if (p->op == 'C') {
        return !evalWFF(p->left, elements) || evalWFF(p->right, elements);
    } else {
        return evalWFF(p->left, elements) == evalWFF(p->right, elements);
    }
}

int main() {
    string inputLine;
    while (true) {
        cin >> inputLine;
        if (inputLine[0] == '0') break;
        WFFNode *wff = getWFF(inputLine, 0);
        bool valid = true;
        for (unsigned i = 0; i < (1U << 5); i++) {
            if (!evalWFF(wff, i)) {
                valid = false;
                break;
            }
        }
        if (valid) cout << "tautology" << endl;
        else cout << "not" << endl;
        freeWFF(wff);
    }
    return 0;
}
