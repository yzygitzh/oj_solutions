/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: combo
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

bool validKey(int key[3], int origin[3], int mod) {
    for (int i = 0; i < 3; i++) {
        if (!((origin[i] - key[i] + mod) % mod <= 2 ||
              (key[i] - origin[i] + mod) % mod <= 2)) {
            return false;
        }
    }
    return true;
}

int main() {
    ofstream fout ("combo.out");
    ifstream fin ("combo.in");

    int circle;
    int farmer[3], master[3];
    fin >> circle;
    for (int i = 0; i < 3; i++) {
        fin >> farmer[i];
        farmer[i]--;
    }
    for (int i = 0; i < 3; i++) {
        fin >> master[i];
        master[i]--;
    }
    
    int keyNum = 0, currKey;
    int key[3];
    for (int i = 0; i < circle * circle * circle; i++) {
        currKey = i;
        for (int j = 0; j < 3; j++) {
            key[j] = currKey % circle;
            currKey /= circle;
        }
        if (validKey(key, farmer, circle) ||
            validKey(key, master, circle)) {
            keyNum += 1;
        }
    }

    fout << keyNum << endl;

    return 0;
}

