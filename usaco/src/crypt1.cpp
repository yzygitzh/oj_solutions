/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: crypt1
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool digitEnabled[10] = {false};

bool validNum(int num) {
    while (num) {
        if (!digitEnabled[num % 10]) return false;
        num /= 10;
    }
    return true;
}

int main() {
    ofstream fout ("crypt1.out");
    ifstream fin ("crypt1.in");

    int N, currDigit;
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> currDigit;
        digitEnabled[currDigit] = true;
    }

    int temp1, temp2, result;
    int resultNum = 0;
    for (int i = 100; i <= 999; i++) {
        for (int j = 10; j <= 99; j++) {
            temp1 = i * (j % 10); 
            temp2 = i * (j / 10); 
            result = i * j;
            if (validNum(i) && validNum(j) &&
                validNum(temp1) && validNum(temp2) && validNum(result) &&
                temp1 >= 100 && temp1 <= 999 && temp2 >= 100 && temp2 <= 999 &&
                result >= 1000 && result <= 9999) {
                resultNum += 1;
            }
        }
    }

    fout << resultNum << endl;

    return 0;
}

