/*
 * POJ 2993 - Emag eht htiw Em Pleh
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

char board[8][8] = {0};

int main() {
    string inputLine;
    for (int isBlack = 0; isBlack < 2; isBlack++) {
        getline(cin, inputLine);
        inputLine = inputLine.substr(inputLine.length() < 8 ? inputLine.length() - 1 : 7);
        int inputLen = inputLine.length();
        for (int i = 0; i < inputLen; i++) {
            if ('A' <= inputLine[i] && inputLine[i] <= 'Z') {
                board[8 - (inputLine[i + 2] - '0')]
                     [inputLine[i + 1] - 'a'] = inputLine[i] + (isBlack ? ('a' - 'A') : 0);
                i += 3;
            } else {
                board[8 - (inputLine[i + 1] - '0')]
                     [inputLine[i] - 'a'] = isBlack ? 'p' : 'P';
                i += 2;
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        cout << "+---+---+---+---+---+---+---+---+" << endl;
        for (int j = 0; j < 8; j++) {
            char background = ((i + j) % 2) ? ':' : '.';
            cout << '|' << background
                 << (board[i][j] == '\0' ? background : board[i][j])
                 << background;
        }
        cout << '|' << endl;
    }
    cout << "+---+---+---+---+---+---+---+---+" << endl;

    return 0;
}
