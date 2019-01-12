/*
 * POJ 2632 - Crashing Robots
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

char turnLeft(char c) {
    if (c == 'N') return 'W';
    else if (c == 'W') return 'S';
    else if (c == 'S') return 'E';
    else return 'N';
}

char turnRight(char c) {
    if (c == 'N') return 'E';
    else if (c == 'W') return 'N';
    else if (c == 'S') return 'W';
    else return 'S';
}

pair<int, int> moveOneStep(pair<int, int> pos, char dir) {
    if (dir == 'N') pos.first += 1;
    else if (dir == 'W') pos.second -= 1;
    else if (dir == 'S') pos.first -= 1;
    else pos.second += 1;
    return pos;
}

int main() {
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        int rowNum, colNum;
        int robotNum, instrNum;
        map<int, pair<int, int> > robotPos;
        map<pair<int, int>, int> occupied;
        map<int, char> robotDir;

        bool valid = true;
        int crashId, crashIntoId;
        string crashCause;

        cin >> colNum >> rowNum;
        cin >> robotNum >> instrNum;
        for (int i = 0; i < robotNum; i++) {
            int row, col;
            string dir;
            cin >> col >> row >> dir;
            robotPos[i + 1] = make_pair(row, col);
            occupied[make_pair(row, col)] = i + 1;
            robotDir[i + 1] = dir[0];
        }

        for (int i = 0; i < instrNum; i++) {
            int rId, repeat;
            string action;
            cin >> rId >> action >> repeat;

            if (!valid) continue;

            if (action[0] == 'L') {
                repeat = repeat % 4;
                for (int j = 0; j < repeat; j++) {
                    robotDir[rId] = turnLeft(robotDir[rId]);
                }
            } else if (action[0] == 'R') {
                repeat = repeat % 4;
                for (int j = 0; j < repeat; j++) {
                    robotDir[rId] = turnRight(robotDir[rId]);
                }
            } else {
                pair<int, int> currPos = robotPos[rId];
                occupied.erase(currPos);
                for (int j = 0; j < repeat; j++) {
                    currPos = moveOneStep(currPos, robotDir[rId]);
                    if (currPos.first == 0 || currPos.first > rowNum ||
                        currPos.second == 0 || currPos.second > colNum ||
                        occupied.find(currPos) != occupied.end()) {
                        crashId = rId;
                        if (occupied.find(currPos) != occupied.end()) {
                            crashIntoId = occupied[currPos];
                            crashCause = "robot";
                        } else {
                            crashCause = "wall";
                        }
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    robotPos[rId] = currPos;
                    occupied[currPos] = rId;
                }
            }
        }
        if (valid) {
            cout << "OK" << endl;
        } else if (crashCause == "robot") {
            cout << "Robot " << crashId << " crashes into robot " << crashIntoId << endl;
        } else {
            cout << "Robot " << crashId << " crashes into the wall" << endl;
        }
    }
    return 0;
}
