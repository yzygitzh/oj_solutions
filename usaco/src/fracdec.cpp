/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: fracdec
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

using namespace std;

ifstream fin ("fracdec.in");
ofstream fout ("fracdec.out");

int N, D;
int visited[1000010] = {0};
string rightDot;

int main() {
    fin >> N >> D;

    // get rid of digits left by dot
    int leftDot = N / D;
    N -= leftDot * D;
    N *= 10;

    int step = 1;
    while (!visited[N] && N) {
        visited[N] = step++;
        if (N < D) {
            rightDot += '0';
        } else {
            rightDot += (char)('0' + N / D);
            N %= D;
        }
        // cout << N << " " << D << " " << N / D << endl;
        N *= 10;
    }

    stringstream output;
    output << leftDot << ".";
    if (N == 0) {
        if (!rightDot.length()) output << "0";
        else output << rightDot;
    } else {
        int cycBeg = visited[N] - 1;
        int cycEnd = step;
        output << rightDot.substr(0, cycBeg)
               << "(" << rightDot.substr(cycBeg) << ")";
    }
    string outputStr = output.str();
    for (int i = 0; i < outputStr.length(); i += 76) {
        fout << outputStr.substr(i, 76) << endl;
    }

    return 0;
}

