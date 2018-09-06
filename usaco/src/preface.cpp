/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: preface
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
#include <map>

using namespace std;

map<char, int> charCount;
map<int, char> romanMap;

void num2roman(int num) {
    int ratio = 1, digit;
    while (num) {
        digit = num % 10;
        if (digit <= 3) {
            for (int i = 0; i < digit; i++) {
                charCount[romanMap[ratio]]++;
            }
        } else if (digit <= 5) {
            if (digit == 4) {
                charCount[romanMap[ratio]]++;
            }
            charCount[romanMap[5 * ratio]]++;
        } else if (digit <= 8) {
            charCount[romanMap[5 * ratio]]++;
            for (int i = 5; i < digit; i++) {
                charCount[romanMap[ratio]]++;
            }
        } else {
            if (digit == 9) {
                charCount[romanMap[ratio]]++;
            }
            charCount[romanMap[10 * ratio]]++;
        }
        num /= 10;
        ratio *= 10;
    }
}

int main() {
    ofstream fout ("preface.out");
    ifstream fin ("preface.in");

    int N;
    fin >> N;
    romanMap[1] = 'I';
    romanMap[5] = 'V';
    romanMap[10] = 'X';
    romanMap[50] = 'L';
    romanMap[100] = 'C';
    romanMap[500] = 'D';
    romanMap[1000] = 'M';
    for (int i = 1; i <= N; i++) {
        num2roman(i);
    }
    for (map<int, char>::iterator itr = romanMap.begin();
         itr != romanMap.end(); ++itr) {
        if (charCount[itr->second] > 0) {
            fout << itr->second << " " << charCount[itr->second] << endl;
        }
    }

    return 0;
}

