/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: frameup
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

ifstream fin ("frameup.in");
ofstream fout ("frameup.out");

int H, W;
char board[50][50] = {0};
class FrameInfo {
public:
    int left, right, up, down;
    FrameInfo(): left(50), right(0), up(50), down(0) {}
};
int hasFrame[26] = {0};
int frameCount = 0;
FrameInfo frames[26];
set<char> upSet[26];

int getMin(int x, int y) {
    return x < y ? x : y;
}

int getMax(int x, int y) {
    return x > y ? x : y;
}

int visited[26] = {0};
void genSeqSet(int rest, string seq) {
    // cout << seq << endl;
    if (rest == 0) {
        // when a letter appears in upSet but not seq, this is invalid
        // i.e. all letters in upSet must appear in seq
        bool valid = true;
        for (int i = 0; i < frameCount; i++) {
            if (!hasFrame[seq[i] - 'A']) continue;
            for (set<char>::iterator itr = upSet[seq[i] - 'A'].begin();
                 itr != upSet[seq[i] - 'A'].end(); ++itr) {
                bool letterFound = false;
                // cout << seq << " " << (char)('A' + i) << " " << *itr << endl;
                for (int j = i; j < frameCount; j++) {
                    if (*itr == seq[j]) {
                        letterFound = true;
                        break;
                    }
                }
                valid &= letterFound;
            }
        }
        // if (valid) cout << seq << endl;
        if (valid) fout << seq << endl;
    } else {
        for (int i = 0; i < 26; i++) {
            // don't search invalid seq
            // check whether already appearing letter is in upSet of current letter
            bool validNext = true;
            for (int j = 0; j < seq.length(); j++) {
                // if (seq == "A") cout << *upSet[seq[j] - 'A'].begin() << endl;
                if (upSet[i].count(seq[j])) {
                    validNext = false;
                    break;
                }
            }
            // check whether current letter is in upSet of letters not appearing yet
            for (int j = 0; j < 26; j++) {
                if (i != j && !visited[j] && hasFrame[j] &&
                    upSet[j].count((char)('A' + i))) {
                    validNext = false;
                    break;
                }
            }
            if (!visited[i] && hasFrame[i] && validNext) {
                visited[i] = 1;
                genSeqSet(rest - 1, seq + (char)('A' + i));
                visited[i] = 0;
            }
        }
    }
}

int main() {
    fin >> H >> W;
    string boardLine;
    for (int i = 0; i < H; i++) {
        fin >> boardLine;
        memcpy(board[i], boardLine.c_str(), W);
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if ('A' <= board[i][j] && board[i][j] <= 'Z') {
                if (!hasFrame[board[i][j] - 'A']) {
                    hasFrame[board[i][j] - 'A'] = 1;
                    frameCount++;
                }
                frames[board[i][j] - 'A'].left = getMin(frames[board[i][j] - 'A'].left, j);
                frames[board[i][j] - 'A'].right = getMax(frames[board[i][j] - 'A'].right, j);
                frames[board[i][j] - 'A'].up = getMin(frames[board[i][j] - 'A'].up, i);
                frames[board[i][j] - 'A'].down = getMax(frames[board[i][j] - 'A'].down, i);
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (!hasFrame[i]) continue;
        for (int j = frames[i].up; j <= frames[i].down; j++) {
            for (int k = frames[i].left; k <= frames[i].right; k++) {
                if ((j == frames[i].up || j == frames[i].down ||
                     k == frames[i].left || k == frames[i].right) &&
                    'A' <= board[j][k] && board[j][k] <= 'Z') {
                    upSet[i].insert(board[j][k]);
                    // if (i == 2) cout << board[j][k] << endl;
                }
            }
        }
    }

    genSeqSet(frameCount, "");

    return 0;
}

