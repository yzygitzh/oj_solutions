/*
 * POJ 2031 - Building a Space Station
 *
 */

#include <cstdio>
#include <cstdlib>
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

class Point {
public:
    double x, y, z, r;
    Point() {};
    Point(double _x, double _y, double _z, double _r)
        : x(_x), y(_y), z(_z), r(_r) {}
};

Point cells[110];
int cellParent[110];
int cellNum;
vector<vector<int> > cellGroups;
vector<vector<double> > groupDis;

double getDis(Point &p, Point &q) {
    return max(0., sqrt(pow(p.x - q.x, 2) +
                        pow(p.y - q.y, 2) +
                        pow(p.z - q.z, 2)) - p.r - q.r);
}

double getGroupDis(int idx1, int idx2) {
    double dis = 1e12;
    for (int i = 0; i < cellGroups[idx1].size(); i++) {
        for (int j = 0; j < cellGroups[idx2].size(); j++) {
            dis = min(dis, getDis(cells[cellGroups[idx1][i]],
                                  cells[cellGroups[idx2][j]]));
        }
    }
    return dis;
}

bool overlaps(Point &p, Point &q) {
    return getDis(p, q) <= 1e-6;
}

void calcGroupDis() {
    groupDis.resize(cellGroups.size());
    for (int i = 0; i < cellGroups.size(); i++) {
        groupDis[i].resize(cellGroups.size());
    }
    for (int i = 0; i < cellGroups.size(); i++) {
        for (int j = 0; j < i; j++) {
            groupDis[i][j] = groupDis[j][i] = getGroupDis(i, j);
        }
        groupDis[i][i] = 0.;
    }
}

int findCellParent(int idx) {
    if (cellParent[idx] != idx) {
        cellParent[idx] = findCellParent(cellParent[idx]);
    }
    return cellParent[idx];
}

void groupCellPair(int idx1, int idx2) {
    int group1 = findCellParent(idx1);
    int group2 = findCellParent(idx2);
    cellParent[group1] = group2;
}

void groupCells() {
    cellGroups.clear();
    for (int i = 0; i < cellNum; i++) {
        for (int j = 0; j < i; j++) {
            if (overlaps(cells[i], cells[j])) {
                groupCellPair(i, j);
                break;
            }
        }
    }
    map<int, vector<int> > parentToGroup;
    for (int i = 0; i < cellNum; i++) {
        parentToGroup[findCellParent(i)].push_back(i);
    }
    for (map<int, vector<int> >::iterator itr = parentToGroup.begin();
         itr != parentToGroup.end(); ++itr) {
        cellGroups.push_back(itr->second);
    }
}

double prim() {
    calcGroupDis();
    vector<double> minDis(cellGroups.size(), 1e12);
    minDis[0] = 0.;
    vector<int> visited(cellGroups.size(), 0);
    double result = 0.;
    for (int i = 0; i < cellGroups.size(); i++) {
        // find minimum dis
        double currMinIdx = 0, currMinDis = 1e12;
        for (int j = 0; j < cellGroups.size(); j++) {
            if (!visited[j] && minDis[j] < currMinDis) {
                currMinDis = minDis[j];
                currMinIdx = j;
            }
        }
        visited[currMinIdx] = 1;
        result += minDis[currMinIdx];
        // update minimum dis
        for (int j = 0; j < cellGroups.size(); j++) {
            if (!visited[j] && minDis[j] > groupDis[currMinIdx][j]) {
                minDis[j] = groupDis[currMinIdx][j];
            }
        }
    }
    return result;
}

int main() {
    while (true) {
        scanf("%d", &cellNum);
        if (cellNum == 0) break;
        for (int i = 0; i < cellNum; i++) {
            double x, y, z, r;
            scanf("%lf%lf%lf%lf", &x, &y, &z, &r);
            cells[i] = Point(x, y, z, r);
            cellParent[i] = i;
        }
        groupCells();
        printf("%.3f\n", prim());
    }
    return 0;
}

