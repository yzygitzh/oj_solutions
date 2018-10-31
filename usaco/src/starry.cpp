/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: starry
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

ifstream fin ("starry.in");
ofstream fout ("starry.out");

class Point {
public:
    int x, y;
    Point(int _x, int _y): x(_x), y(_y) {}
    bool operator< (const Point& p) const {
        if (x < p.x) return true;
        else if (x == p.x) return y < p.y;
        else return false;
    }
};

int patternId = 0;

class Pattern {
public:
    set<Point> pts;
    int minX, maxX, minY, maxY;
    Pattern() {};
    void insertPoint(const Point &p) {
        pts.insert(p);
        if (pts.size() == 1) {
            minX = maxX = p.x;
            minY = maxY = p.y;
        } else {
            if (p.x < minX) minX = p.x;
            if (p.x > maxX) maxX = p.x;
            if (p.y < minY) minY = p.y;
            if (p.y > maxY) maxY = p.y;
        }
    }
    void normalize() {
        set<Point> newPts;
        for (set<Point>::iterator itr = pts.begin();
             itr != pts.end(); ++itr) {
            newPts.insert(Point(itr->x - minX, itr->y - minY));
        }
        pts = newPts;
        maxX -= minX;
        maxY -= minY;
        minX = minY = 0;
    }
    bool operator==(const Pattern &p) const {
        if (p.pts.size() != pts.size()) return false;
        set<Point> tmpPts = p.pts;
        // 8 possible transforms
        int currH = p.maxX - p.minX;
        int currW = p.maxY - p.minY;
        for (int i = 0; i < 8; i++) {
            set<Point> newTmpPts;
            for (set<Point>::iterator itr = tmpPts.begin();
                 itr != tmpPts.end(); ++itr) {
                if (i == 0) { // origin pattern
                    newTmpPts.insert(Point(itr->x, itr->y));
                } else if (i != 4) { // rotate, 0,0 -> 0,1 -> 1,1 -> 1,0 -> 0,0
                    newTmpPts.insert(Point(itr->y, currH - itr->x));
                } else { // mirror, 0,0 -> 1,0 -> 0,0
                    newTmpPts.insert(Point(itr->x, currW - itr->y));
                }
            }
            tmpPts = newTmpPts;
            if (i > 0 && i != 4) {
                int tmp = currH;
                currH = currW;
                currW = tmp;
            }

            bool ptsEqual = true;
            for (set<Point>::iterator itr1 = tmpPts.begin(),
                 itr2 = pts.begin();
                 itr1 != tmpPts.end() && itr2 != pts.end();
                 ++itr1, ++itr2) {
                if (*itr1 < *itr2 || *itr2 < *itr1) {
                    ptsEqual = false;
                    break;
                }
            }
            if (ptsEqual) return true;
        }
        return false;
    }
};

int W, H;
char skyMap[110][110];
int visited[110][110];

Pattern nonSimilarPattern[30];

void findAndCompare(const Point& startP) {
    Pattern result, normResult;
    memset(visited, 0, sizeof(visited));
    queue<Point> bfsQ;
    bfsQ.push(startP);
    visited[startP.x][startP.y] = 1;
    while (!bfsQ.empty()) {
        Point currP = bfsQ.front();
        bfsQ.pop();
        result.insertPoint(currP);
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int newX = currP.x + i;
                int newY = currP.y + j;
                if (newX >= 0 && newX < H &&
                    newY >= 0 && newY < W &&
                    !visited[newX][newY] &&
                    skyMap[newX][newY] == '1') {
                    visited[newX][newY] = 1;
                    bfsQ.push(Point(newX, newY));
                }
            }
        }
    }
    normResult = result;
    normResult.normalize();
    int hitId = 0;
    for (; hitId < patternId; hitId++) {
        if (nonSimilarPattern[hitId] == normResult) {
            break;
        }
    }
    if (hitId == patternId) {
        nonSimilarPattern[patternId++] = normResult;
    }
    for (set<Point>::iterator itr = result.pts.begin();
         itr != result.pts.end(); ++itr) {
        skyMap[itr->x][itr->y] = 'a' + hitId;
    }
}

int main() {
    string inLine;
    fin >> W >> H;
    for (int i = 0; i < H; i++) {
        fin >> inLine;
        memcpy(skyMap[i], inLine.c_str(), W);
        skyMap[i][W] = '\0';
    }
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (skyMap[i][j] == '1') {
                findAndCompare(Point(i, j));
            }
        }
    }
    for (int i = 0; i < H && W > 0; i++) {
        fout << skyMap[i] << endl;
    }
    return 0;
}

