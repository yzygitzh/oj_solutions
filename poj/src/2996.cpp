/*
 * POJ 2996 - Help Me with the Game
 *
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Grid {
public:
    bool isWhite;
    char piece;
};

Grid board[8][8];
map<char, vector<pair<int, int> > > whiteMap, blackMap;

bool whiteLessThan(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
}

bool blackLessThan(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second < b.second;
}

int main() {
    string inputLine;
    for (int i = 0; i < 8; i++) {
        cin >> inputLine;
        cin >> inputLine;
        for (int j = 0; j < 8; j++) {
            board[i][j].isWhite = inputLine[j * 4 + 1] == '.';
            board[i][j].piece = inputLine[j * 4 + 2];
            if ('a' <= board[i][j].piece && 'z' >= board[i][j].piece) {
                blackMap[board[i][j].piece + 'A' - 'a'].push_back(make_pair(i, j));
            } else if ('A' <= board[i][j].piece && 'Z' >= board[i][j].piece) {
                whiteMap[board[i][j].piece].push_back(make_pair(i, j));
            }
        }
    }
    cin >> inputLine;

    char letters[6] = {'K', 'Q', 'R', 'B', 'N', 'P'};
    for (int i = 0; i < 6; i++) {
        sort(whiteMap[letters[i]].begin(), whiteMap[letters[i]].end(), whiteLessThan);
        sort(blackMap[letters[i]].begin(), blackMap[letters[i]].end(), blackLessThan);
    }

    bool firstPiece;
    // print white
    firstPiece = true;
    cout << "White: ";
    for (int i = 0; i < 6; i++) {
        for (vector<pair<int, int> >::iterator itr = whiteMap[letters[i]].begin();
             itr != whiteMap[letters[i]].end(); ++itr) {
            if (firstPiece) firstPiece = false;
            else cout << ',';
            if (letters[i] != 'P') cout << letters[i];
            cout << (char)('a' + itr->second) << 8 - itr->first;
        }
    }
    cout << endl;
    // print black
    firstPiece = true;
    cout << "Black: ";
    for (int i = 0; i < 6; i++) {
        for (vector<pair<int, int> >::iterator itr = blackMap[letters[i]].begin();
             itr != blackMap[letters[i]].end(); ++itr) {
            if (firstPiece) firstPiece = false;
            else cout << ',';
            if (letters[i] != 'P') cout << letters[i];
            cout << (char)('a' + itr->second) << 8 - itr->first;
        }
    }
    cout << endl;

    return 0;
}
