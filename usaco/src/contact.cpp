/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: contact
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

/*
 * Note that a pattern never appears more than its subset
 */

/*
 * Simpler solution: since pattern length is limited, we can
 * just count all patterns appeared in the sequence.
 */

ifstream fin ("contact.in");
ofstream fout ("contact.out");

int A, B, N;
string S;
class Elem {
public:
    int count;
    string pattern;
    Elem(int _count, string _pattern): count(_count), pattern(_pattern) {}
    bool operator< (const Elem& e) const {
        if (count < e.count) return true;
        else if (count == e.count) {
            if (pattern.length() > e.pattern.length()) return true;
            else if (pattern.length() == e.pattern.length())
                return pattern > e.pattern;
            return false;
        }
        return false;
    }
};
priority_queue<Elem> bfsQ;
vector<Elem> result;

int countPattern(string pattern) {
    int hitCount = 0;
    for (int i = 0; i < S.length() - pattern.length() + 1; i++) {
        bool hit = true;
        for (int j = 0; j < pattern.length(); j++) {
            if (S[i + j] != pattern[j]) {
                hit = false;
                break;
            }
        }
        if (hit) hitCount++;
    }
    return hitCount;
}

map<string, int> initCount;

void BFS() {
    int patternCount;

    if (A > S.length()) return;

    // add "0" "1" sequences of at least length A
    // appearing in S
    for (int i = 0; i < S.length() - A + 1; i++) {
        initCount[S.substr(i, A)]++;
    }
    for (map<string, int>::iterator itr = initCount.begin();
         itr != initCount.end(); ++itr) {
        if (itr->second > 0) bfsQ.push(Elem(itr->second, itr->first));
    }
    // cout << bfsQ.size() << endl;

    int currMax = 200010, n = 0;
    int validLenInQ = bfsQ.size();
    while (validLenInQ) {
        Elem top = bfsQ.top();
        bfsQ.pop();
        validLenInQ--;
        // cout << top.count << " " <<  top.pattern << endl;
        if (top.pattern.length() >= A &&
            top.pattern.length() <= B) {
            if (currMax > top.count) {
                currMax = top.count;
                n++;
                if (n > N) break;
            }
            result.push_back(top);
        }
        if (top.pattern.length() + 1 >= A &&
            top.pattern.length() + 1 <= B &&
            top.pattern.length() + 1 <= S.length()) {
            // add "x0"
            patternCount = countPattern(top.pattern + "0");
            if (patternCount > 0) {
                bfsQ.push(Elem(patternCount, top.pattern + "0"));
                validLenInQ++;
            }
            // add "x1"
            patternCount = countPattern(top.pattern + "1");
            if (patternCount > 0) {
                bfsQ.push(Elem(patternCount, top.pattern + "1"));
                validLenInQ++;
            }
        }
    }
}

int main() {
    string tmpSeq;
    fin >> A >> B >> N;
    getline(fin, tmpSeq);
    while (fin >> tmpSeq) {
        S += tmpSeq;
    }
    BFS();

    int currMax = 200010, sixCount;
    for (vector<Elem>::iterator itr = result.begin();
         itr != result.end(); ++itr) {
        if (currMax > (*itr).count) {
            if (itr != result.begin()) fout << endl;
            currMax = (*itr).count;
            fout << (*itr).count;
            sixCount = 0;
        }
        if (sixCount) {
            fout << " ";
        } else {
            fout << endl;
        }
        sixCount = (sixCount + 1) % 6;
        fout << (*itr).pattern;
    }
    fout << endl;

    return 0;
}

