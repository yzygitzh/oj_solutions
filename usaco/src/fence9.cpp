/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: fence9
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

ifstream fin ("fence9.in");
ofstream fout ("fence9.out");

const double eps = 1e-10;
double N, M, P;

int main() {
    fin >> N >> M >> P;
    int latNum = 0;
    double leftDeltaX = N / M, rightDeltaX = (N - P) / M;
    for (int i = 1; i < M; i++) {
        double leftBound = leftDeltaX * i;
        int leftIn = ceil(leftBound);
        if ((double)leftIn - leftBound < eps) leftIn++;

        double rightBound = P + rightDeltaX * i;
        int rightIn = floor(rightBound);
        if (rightBound - (double)rightIn < eps) rightIn--;

        if (rightIn >= leftIn) latNum += rightIn - leftIn + 1;
    }
    fout << latNum << endl;
    return 0;
}

