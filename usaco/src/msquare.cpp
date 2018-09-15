/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: msquare
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

ifstream fin ("msquare.in");
ofstream fout ("msquare.out");

string transA(string origin) {
    return origin.substr(4, 4) + origin.substr(0, 4);
}

string transB(string origin) {
    string result;
    result += origin[3];
    result += origin.substr(0, 3);
    result += origin[7];
    result += origin.substr(4, 3);
    return result;
}

string transC(string origin) {
    string result;
    result += origin[0];
    result += origin[5];
    result += origin[1];
    result += origin[3];
    result += origin[4];
    result += origin[6];
    result += origin[2];
    result += origin[7];
    return result;
}

class BfsElem {
public:
    string key, path;
    BfsElem(string _key, string _path): key(_key), path(_path) {}
};

map<string, int> visited;
queue<BfsElem> bfsQ;
string initStr = "12348765";
string targetStr;

string BFS() {
    bfsQ.push(BfsElem(initStr, ""));
    visited[initStr] = 1;
    while (true) {
        BfsElem top = bfsQ.front();
        bfsQ.pop();
        // if (top.path == "A") cout << "A" << top.key << endl;
        // if (top.path == "B") cout << "B" << top.key << endl;
        // if (top.path == "C") cout << "C" << top.key << endl;
        // cout << top.key << endl;
        if (top.key == targetStr) return top.path;
        // cout << top.path.length() << endl;
        
        string strA = transA(top.key);
        if (!visited[strA]) {
            visited[strA] = 1;
            bfsQ.push(BfsElem(strA, top.path + "A"));
        }
        string strB = transB(top.key);
        if (!visited[strB]) {
            visited[strB] = 1;
            bfsQ.push(BfsElem(strB, top.path + "B"));
        }
        string strC = transC(top.key);
        if (!visited[strC]) {
            visited[strC] = 1;
            bfsQ.push(BfsElem(strC, top.path + "C"));
        }
    }
}

int main() {
    string initLine;
    getline(fin, initLine);
    for (int i = 0; i < 4; i++) targetStr += initLine[2 * i];
    for (int i = 0; i < 4; i++) targetStr += initLine[14 - 2 * i];
    string result = BFS();
    fout << result.length() << endl;
    for (int i = 0; i < result.length(); i += 60) {
        int strLen = 60;
        if (result.substr(i * 60).length() < 60) strLen = result.substr(i * 60).length();
        fout << result.substr(i * 60, strLen) << endl;
    }
    if (result.length() == 0) fout << endl;

    return 0;
}

