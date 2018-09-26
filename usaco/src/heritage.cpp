/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: heritage
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

ifstream fin ("heritage.in");
ofstream fout ("heritage.out");

string inOrder;
string preOrder;

string genPostOrder(string in, string pre) {
    if (in.length() <= 1) return in;
    char root = pre[0];
    int rootIdx;
    for (int i = 0; i < in.length(); i++) {
        if (in[i] == root) {
            rootIdx = i;
            break;
        }
    }
    int leftStrLen = rootIdx;
    int rightStrLen = in.length() - rootIdx - 1;
    string leftStr = genPostOrder(in.substr(0, leftStrLen), pre.substr(1, leftStrLen));
    string rightStr = genPostOrder(in.substr(leftStrLen + 1), pre.substr(leftStrLen + 1));
    return leftStr + rightStr + pre.substr(0, 1);
}

int main() {
    fin >> inOrder >> preOrder;
    fout << genPostOrder(inOrder, preOrder) << endl;
    return 0;
}

