/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: sort3
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <string>

using namespace std;

int digitCount[4];
int N;
int input[1010];
int exNum = 0;

int main() {
    ofstream fout ("sort3.out");
    ifstream fin ("sort3.in");

    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> input[i];
        digitCount[input[i]]++;
    }

    int ex1in2 = 0, ex1in3 = 0, ex2in1 = 0, ex2in3 = 0, ex3in1 = 0, ex3in2 = 0;

    for (int i = 0; i < digitCount[1]; i++) {
        if (input[i] == 2) ex2in1++;
        if (input[i] == 3) ex3in1++;
    }
    for (int i = digitCount[1]; i < digitCount[1] + digitCount[2]; i++) {
        if (input[i] == 1) ex1in2++;
        if (input[i] == 3) ex3in2++;
    }
    for (int i = N - digitCount[3]; i < N; i++) {
        if (input[i] == 1) ex1in3++;
        if (input[i] == 2) ex2in3++;
    }

    while (ex2in1 && ex1in2) ex2in1--, ex1in2--, exNum++;
    while (ex1in3 && ex3in1) ex1in3--, ex3in1--, exNum++;
    while (ex2in3 && ex3in2) ex2in3--, ex3in2--, exNum++;
    // 231 or 312 left
    exNum += ex2in1 * 2;
    exNum += ex3in1 * 2;

    fout << exNum << endl;

    return 0;
}

