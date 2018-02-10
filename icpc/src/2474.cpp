/*
 * ICPC 2474 - Balloons in a Box
 *
 * Note that there should be a BLANK LINE after each answer...
 */

#include <cstdio>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

const int maxPointNum = 6;
const int pointDim = 3;

int pointNum;
double lCorner[pointDim], hCorner[pointDim];
double points[maxPointNum][pointDim];
double pointR[maxPointNum];
int pointVisited[maxPointNum];

double maxVol;

double getDis(double *pointA, double *pointB) {
    double dis = 0.0;
    for (int i = 0; i < pointDim; i++) {
        dis += pow(pointA[i] - pointB[i], 2);
    }
    return sqrt(dis);
}

double getMaxR(double *point) {
    double maxR = abs(lCorner[0] - point[0]);
    double currDis;
    for (int i = 0; i < pointDim; i++) {
        currDis = abs(lCorner[i] - point[i]);
        maxR = currDis < maxR ? currDis: maxR;
        currDis = abs(hCorner[i] - point[i]);
        maxR = currDis < maxR ? currDis: maxR;
    }
    for (int i = 0; i < pointNum; i++) {
        if (pointVisited[i] == 1) {
            currDis = getDis(point, points[i]);
            currDis -= pointR[i];
            maxR = currDis < maxR ? currDis: maxR;
        }
    }
    return maxR >= 0.0 ? maxR: 0.0;
}

void readPoint(double *buf) {
    for (int i = 0; i < pointDim; i++) {
        scanf("%lf", buf + i);
    }
    return;
}

void calcVol(int restPointNum, double currVol) {
    if (restPointNum == 0) {
        maxVol = currVol > maxVol ? currVol: maxVol;
        return;
    } else {
        for (int i = 0; i < pointNum; i++) {
            if (pointVisited[i] == 0) {
                pointR[i] = getMaxR(points[i]);
                pointVisited[i] = 1;
                calcVol(restPointNum - 1, currVol + pow(pointR[i], 3) * M_PI * 4.0 / 3.0);
                pointVisited[i] = 0;
                pointR[i] = 0.0;
            }
        }
    }
    return;
}

double calcBoxVol(){
    double vol = 1.0;
    for (int i = 0; i < pointDim; i++) {
        vol *= abs(lCorner[i] - hCorner[i]);
    }
    return vol;
}

int main() {
    int count = 0;
    while (true) {
        count += 1;
        scanf("%d", &pointNum);
        if (pointNum == 0)
            break;
        readPoint(lCorner);
        readPoint(hCorner);
        for (int i = 0; i < maxPointNum; i++) {
            pointVisited[i] = 1;
            pointR[i] = 0.0;
        }
        for (int i = 0; i < pointNum; i++) {
            readPoint(points[i]);
            pointVisited[i] = 0;
        }
        maxVol = 0.0;
        calcVol(pointNum, 0.0);
        printf("Box %d: %d\n\n", count, (int)round(calcBoxVol() - maxVol));
    }
    return 0;
}
