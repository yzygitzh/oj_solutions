/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: hamming
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

int N, B, D;
int maxWord;
unsigned char words[100];
bool found = false;

// binary merge bit count
int hamDis(unsigned char x, unsigned char y) { 
    unsigned char dis = x ^ y;
    unsigned char mask1, mask2;
    mask1 = 0x1 + 0x4 + 0x10 + 0x40;
    mask2 = 0x2 + 0x8 + 0x20 + 0x80;
    unsigned char sum2 = ((dis & mask2) >> 1) + (dis & mask1);
    mask1 = 0x3 + 0x30;
    mask2 = 0xC + 0xC0;
    unsigned char sum4 = ((sum2 & mask2) >> 2) + (sum2 & mask1);
    mask1 = 0xF;
    mask2 = 0xF0;
    unsigned char sum8 = ((sum4 & mask2) >> 4) + (sum4 & mask1);
    return (int)sum8;
}

void DFS(int rest, int idx) {
    if (found) return;
    if (rest > maxWord - idx) {
        return;
    } else if (rest == 0) {
        found = true;
        return;
    } else {
        words[N - rest] = (unsigned char)idx;
        bool valid = true;
        for (int i = 0; i < N - rest; i++) {
            if (hamDis(words[i], words[N - rest]) < D) valid = false;
        }
        if (valid) DFS(rest - 1, idx + 1);
        DFS(rest, idx + 1);
    }
}

int main() {
    ofstream fout ("hamming.out");
    ifstream fin ("hamming.in");

    fin >> N >> B >> D;
    maxWord = 1 << B;
    DFS(N, 0);

    for (int i = 0; i < N; i++) {
        fout << (int)words[i];
        if (i + 1 == N || (i % 10) == 9) fout << endl;
        else fout << " ";
    }

    return 0;
}

