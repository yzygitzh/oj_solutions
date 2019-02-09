/*
 * POJ 3020 - Antenna Placement
 *
 * Build bi-partie graph, where positions are edges and antennas are nodes.
 * Find minimum edge coverage, i.e. n - maximum match.
 */

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

int row, col;
char maze[50][20];
int nodes;
int stars;

/* TODO: define data structure */

int posToId(pair<int, int> pos) {
    return pos.first * col + pos.second;
}

/* TODO: implement hungarian algorithm */
int hungarian() {
    return 0;
}

int main() {
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        cin >> row >> col;
        nodes = row * col;
        stars = 0;
        /* TODO: initialization */
        for (int i = 0; i < row; i++) {
            string inputLine;
            cin >> inputLine;
            memcpy(maze[i], inputLine.c_str(), col);
            for (int j = 0; j < col; j++) {
                // see left and up
                if (maze[i][j] == '*') {
                    stars++;
                    if (j - 1 >= 0 && maze[i][j - 1] == '*') {
                        /* TODO: initialization */
                    }
                    if (i - 1 >= 0 && maze[i - 1][j] == '*') {
                        /* TODO: initialization */
                    }
                }
            }
        }
        cout << (2 * stars - hungarian()) / 2 << endl;
    }
    return 0;
}

