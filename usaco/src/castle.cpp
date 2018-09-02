/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: castle
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <string>

using namespace std;

int maze[60][60];
int room[60][60] = {0};
int roomSize[3000] = {0};
int W, H;
int roomNum = 0;
int maxRoomSize = 0;
int maxBiRoomSize = 0;

void DFS(int w, int h, int mark) {
    if (w < 0 || w >= W || h < 0 || h >= H || room[h][w]) return;
    room[h][w] = mark;
    // cout << h << " " << w << " " << maze[h][w] << " " << mark << endl;
    roomSize[mark]++;
    maxRoomSize = roomSize[mark] > maxRoomSize ? roomSize[mark] : maxRoomSize;
    int wall = maze[h][w];
    if (!(wall & 0x1)) DFS(w - 1, h, mark);
    if (!(wall & 0x2)) DFS(w, h - 1, mark);
    if (!(wall & 0x4)) DFS(w + 1, h, mark);
    if (!(wall & 0x8)) DFS(w, h + 1, mark);
}

void findWall(int *w, int *h, char *direction) {
    for (int i = 0; i < W; i++) {
        for (int j = H - 1; j >= 0; j--) {
            int wall = maze[j][i];
            if (j != 0 && (wall & 0x2) && room[j][i] != room[j - 1][i]) {
                int tmpSize = roomSize[room[j][i]] + roomSize[room[j - 1][i]];
                if (tmpSize > maxBiRoomSize) {
                    *w = i;
                    *h = j;
                    *direction = 'N';
                    maxBiRoomSize = tmpSize;
                }
            }
            if (i != W - 1 && (wall & 0x4) && room[j][i] != room[j][i + 1]) {
                // cout << j << " " << i << " " << maze[j][i] << " " << roomSize[room[j][i]] << endl;
                int tmpSize = roomSize[room[j][i]] + roomSize[room[j][i + 1]];
                // cout << tmpSize << endl;
                if (tmpSize > maxBiRoomSize) {
                    *w = i;
                    *h = j;
                    *direction = 'E';
                    maxBiRoomSize = tmpSize;
                }
            }
        }
    }
}

int main() {
    ofstream fout ("castle.out");
    ifstream fin ("castle.in");

    fin >> W >> H;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            fin >> maze[i][j];
        }
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (!room[i][j]) DFS(j, i, ++roomNum);
        }
    }

    int resultW, resultH;
    char resultDir;
    findWall(&resultW, &resultH, &resultDir);

    fout << roomNum << endl;
    fout << maxRoomSize << endl;
    fout << maxBiRoomSize << endl;
    fout << resultH + 1 << " " << resultW + 1 << " " << resultDir << endl;

    return 0;
}

