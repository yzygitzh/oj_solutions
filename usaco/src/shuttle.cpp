/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: shuttle
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

ifstream fin ("shuttle.in");
ofstream fout ("shuttle.out");

/*
 * Actually there is an optimal strategy, see analysis on USACO
 */

int N;

class BfsElem {
public:
    string seq;
    BfsElem(string _seq): seq(_seq) {}
};
queue<BfsElem> bfsQ;

class VisitElem {
public:
    char visited, s1, s2;
    VisitElem(char _v, char _s1, char _s2): visited(_v), s1(_s1), s2(_s2) {}
    VisitElem(): visited(0), s1(0), s2(0) {}
};
map<string, VisitElem> visited;
vector<int> minAction;

void BFS() {
    string initStr, endStr;
    for (int i = 0; i < N; i++) {
        initStr += 'W';
        endStr += 'B';
    }
    initStr += ' ';
    endStr += ' ';
    for (int i = 0; i < N; i++) {
        initStr += 'B';
        endStr += 'W';
    }

    visited[initStr] = VisitElem(1, -1, -1);
    bfsQ.push(BfsElem(initStr));
    // int counter = 0;
    while (!bfsQ.empty()) {
        // counter++;
        BfsElem top = bfsQ.front();
        bfsQ.pop();
        if (top.seq == endStr) {
            string currSeq = top.seq;
            cout << visited.size() << endl;
            while (true) {
                char s1 = visited[currSeq].s1;
                char s2 = visited[currSeq].s2;
                if (s1 < 0) break;
                char swp = currSeq[s1];
                currSeq[s1] = currSeq[s2];
                currSeq[s2] = swp;
                minAction.push_back(s1 + 1);
            }
            return;
        }
        for (int i = 0; i < top.seq.length(); i++) {
            // W move
            if (top.seq[i] == 'W' && i + 1 < top.seq.length() &&
                top.seq[i + 1] == ' ') {
                string newStr = top.seq;
                newStr[i] = ' ';
                newStr[i + 1] = 'W';
                if (!visited[newStr].visited) {
                    visited[newStr].visited = 1;
                    visited[newStr].s1 = i;
                    visited[newStr].s2 = i + 1;
                    bfsQ.push(BfsElem(newStr));
                }
            }
            // W jump
            if (top.seq[i] == 'W' && i + 2 < top.seq.length() &&
                top.seq[i + 1] == 'B' && top.seq[i + 2] == ' ') {
                string newStr = top.seq;
                newStr[i] = ' ';
                newStr[i + 2] = 'W';
                if (!visited[newStr].visited) {
                    visited[newStr].visited = 1;
                    visited[newStr].s1 = i;
                    visited[newStr].s2 = i + 2;
                    bfsQ.push(BfsElem(newStr));
                }
            }
            // B move
            if (top.seq[i] == 'B' && i - 1 >= 0 &&
                top.seq[i - 1] == ' ') {
                string newStr = top.seq;
                newStr[i] = ' ';
                newStr[i - 1] = 'B';
                if (!visited[newStr].visited) {
                    visited[newStr].visited = 1;
                    visited[newStr].s1 = i;
                    visited[newStr].s2 = i - 1;
                    bfsQ.push(BfsElem(newStr));
                }
            }
            // B jump
            if (top.seq[i] == 'B' && i - 2 >= 0 &&
                top.seq[i - 1] == 'W' && top.seq[i - 2] == ' ') {
                string newStr = top.seq;
                newStr[i] = ' ';
                newStr[i - 2] = 'B';
                if (!visited[newStr].visited) {
                    visited[newStr].visited = 1;
                    visited[newStr].s1 = i;
                    visited[newStr].s2 = i - 2;
                    bfsQ.push(BfsElem(newStr));
                }
            }
        }
    }
}

int main() {
    fin >> N;
    BFS();
    int newLineCounter = 0;
    for (vector<int>::reverse_iterator itr = minAction.rbegin();
         itr != minAction.rend(); ++itr, newLineCounter++) {
        fout << *itr;
        if (itr + 1 == minAction.rend() || (newLineCounter + 1) % 20 == 0) fout << endl;
        else fout << " ";
    }
    return 0;
}

