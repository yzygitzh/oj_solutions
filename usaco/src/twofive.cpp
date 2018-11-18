/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: twofive
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <string>
#include <map>
#include <cmath>
#include <utility>
#include <bitset>

#pragma pack(1)
using namespace std;

ifstream fin ("twofive.in");
ofstream fout ("twofive.out");

/*
 * F[a][b][c][d][e]: number of possible sequences when the square's
 * first row is filled with 'a' characters
 * second row ... 'b' characters
 * ...
 * fifth row ... 'e' characters
 * where characters are first a+b+c+d+e characters in query str.
 */

int F[6][6][6][6][6] = {0};
int FVisited[6][6][6][6][6] = {0};

int DFSCharVisited[26] = {0};
char DFSMap[5][5];

int DFS(int FLen[5]) {
    if (FVisited[FLen[0]][FLen[1]][FLen[2]][FLen[3]][FLen[4]]) {
        return F[FLen[0]][FLen[1]][FLen[2]][FLen[3]][FLen[4]];
    }
    int filledCount = FLen[0] + FLen[1] + FLen[2] + FLen[3] + FLen[4];
    if (filledCount == 25) {
        F[FLen[0]][FLen[1]][FLen[2]][FLen[3]][FLen[4]] = 1;
        FVisited[FLen[0]][FLen[1]][FLen[2]][FLen[3]][FLen[4]] = 1;
        return 1;
    }

    // find minimum unused char
    int unUsedIdx = 0;
    while (DFSCharVisited[unUsedIdx]) unUsedIdx++;
    DFSCharVisited[unUsedIdx] = 1;

    // enumerate possible positions for unUsedIdx
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        if (FLen[i] < 5 && // enough space
            (i == 0 || DFSMap[i - 1][FLen[i]] <= 'A' + unUsedIdx) && //valid up character
            (FLen[i] == 0 || DFSMap[i][FLen[i] - 1] <= 'A' + unUsedIdx) && // valid left character
            (i == 0 || FLen[i - 1] > FLen[i])) { // valid position
            DFSMap[i][FLen[i]] = 'A' + unUsedIdx;
            int newFLen[5];
            memcpy(newFLen, FLen, sizeof(newFLen));
            newFLen[i]++;
            sum += DFS(newFLen);
            DFSMap[i][FLen[i]] = 0;
        }
    }
    DFSCharVisited[unUsedIdx] = 0;

    F[FLen[0]][FLen[1]][FLen[2]][FLen[3]][FLen[4]] = sum;
    FVisited[FLen[0]][FLen[1]][FLen[2]][FLen[3]][FLen[4]] = 1;
    return sum;
}

int findSum(string queryStr) {
    int leftUpLen[5] = {0};
    int fillCount = queryStr.length();
    memset(DFSMap, 0, sizeof(DFSMap));
    for (int i = 0; i < 5 && fillCount > 0; i++) {
        leftUpLen[i] = fillCount >= 5 ? 5 : fillCount;
        memcpy(DFSMap[i], queryStr.c_str() + 5 * i, leftUpLen[i]);
        fillCount -= 5;
    }

    memset(DFSCharVisited, 0, sizeof(DFSCharVisited));
    int idx = 0;
    for (string::iterator itr = queryStr.begin();
         itr != queryStr.end(); ++itr) {
        // validation check
        // 1. no repeat
        if (DFSCharVisited[*itr - 'A']) return 0;
        // 2. up/left character
        if (idx >= 5 && queryStr[idx] < queryStr[idx - 5] || // invalid left up character
            idx % 5 > 0 && queryStr[idx] < queryStr[idx - 1]) // invalid right down character
            return 0;
        DFSCharVisited[*itr - 'A'] = 1;
        idx++;
    }

    memset(F, 0, sizeof(F));
    memset(FVisited, 0, sizeof(F));

    return DFS(leftUpLen);
}

int str2id(string queryStr) {
    int sum = 0;
    for (int i = 0; i < queryStr.length(); i++) {
        for (char j = 'A'; j < queryStr[i]; j++) {
            // cout << queryStr.substr(0, i) + j << " " << findSum(queryStr.substr(0, i) + j) << endl;
            sum += findSum(queryStr.substr(0, i) + j);
        }
    }
    return sum + 1;
}

string id2str(int queryId) {
    string result;
    for (int i = 0; i < 25; i++) {
        for (char j = 'A'; j <= 'Y'; j++) {
            int sum = findSum(result + j);
            if (sum >= queryId) {
                result += j;
                break;
            } else {
                queryId -= sum;
            }
        }
    }
    return result;
}

int main() {
    // cout << findSum("ABCDEFGHIJKLMNOPQRTS") << endl;
    // return 0;
    int leftUpLen[5] = {0};
    string mode;
    fin >> mode;
    if (mode == "N") {
        int queryId;
        fin >> queryId;
        fout << id2str(queryId) << endl;
    } else if (mode == "W") {
        string queryStr;
        fin >> queryStr;
        fout << str2id(queryStr) << endl;
    }
    return 0;
}
