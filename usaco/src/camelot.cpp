/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: camelot
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

ifstream fin ("camelot.in");
ofstream fout ("camelot.out");

/*
 * 1. Use BFS to calculate pairwise shortest paths; O(N^2)
 * 2. For each knight, enumerate ending point and king's pickup point,
 *    calculate minimum distance when there is a picking up; O(N^3)
 * For this answer, we ASSUME that the pickup point is near king
 * or (26*30)^3 is too large.
 *
 * To eliminate the N^3, one need to enumerate pickup points
 * when doing BFS on knights and find the minimum cost. Doing so
 * avoids enumerating in knight and ending point loop later.
 * See USACO analysis for details.
 */

class Pos {
public:
    int row, col, dis;
    Pos(int _row, int _col, int _dis): row(_row), col(_col), dis(_dis) {}
};

int R, C;
short pKi[35][35][35][35] = {0}; // shortest king path
short pKn[35][35][35][35] = {0}; // shortest knight path
int vis[35][35] = {0};
int chess[35][35];
queue<Pos> bfsQ;
int minMov = 10000;
int kir, kic; // king row and col

int getAbs(int x) {
    return x < 0 ? -x: x;
}

void BFSKi() {
    for (int r1 = 0; r1 < R; r1++) {
        for (int c1 = 0; c1 < C; c1++) {
            for (int r2 = 0; r2 < R; r2++) {
                for (int c2 = 0; c2 < C; c2++) {
                    pKi[r1][c1][r2][c2] = 10000;
                }
            }
        }
    }
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            memset(vis, 0, sizeof(vis));
            while (!bfsQ.empty()) bfsQ.pop();
            vis[r][c] = 1;
            bfsQ.push(Pos(r, c, 0));
            while (!bfsQ.empty()) {
                Pos p = bfsQ.front();
                bfsQ.pop();
                pKi[r][c][p.row][p.col] = pKi[p.row][p.col][r][c] = p.dis;
                // cout << "INFO " << r << " " << c << " " << p.row << " " << p.col << " " << p.dis << endl;
                for (int rOff = -1; rOff <= 1; rOff++) {
                    for (int cOff = -1; cOff <= 1; cOff++) {
                        if (p.row + rOff >= 0 && p.row + rOff < R &&
                            p.col + cOff >= 0 && p.col + cOff < C &&
                            !vis[p.row + rOff][p.col + cOff]) {
                            vis[p.row + rOff][p.col + cOff] = 1;
                            bfsQ.push(Pos(p.row + rOff, p.col + cOff, p.dis + 1));
                        }
                    }
                }
            }
        }
    }
}

void BFSKn() {
    for (int r1 = 0; r1 < R; r1++) {
        for (int c1 = 0; c1 < C; c1++) {
            for (int r2 = 0; r2 < R; r2++) {
                for (int c2 = 0; c2 < C; c2++) {
                    pKn[r1][c1][r2][c2] = 10000;
                }
            }
        }
    }
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            memset(vis, 0, sizeof(vis));
            while (!bfsQ.empty()) bfsQ.pop();
            vis[r][c] = 1;
            bfsQ.push(Pos(r, c, 0));
            while (!bfsQ.empty()) {
                Pos p = bfsQ.front();
                bfsQ.pop();
                pKn[r][c][p.row][p.col] = pKn[p.row][p.col][r][c] = p.dis;
                // cout << "INFO " << r << " " << c << " " << p.row << " " << p.col << " " << p.dis << endl;
                for (int rOff = -2; rOff <= 2; rOff++) {
                    for (int cOff = -2; cOff <= 2; cOff++) {
                        if (p.row + rOff >= 0 && p.row + rOff < R &&
                            p.col + cOff >= 0 && p.col + cOff < C &&
                            getAbs(rOff) + getAbs(cOff) == 3 &&
                            !vis[p.row + rOff][p.col + cOff]) {
                            vis[p.row + rOff][p.col + cOff] = 1;
                            bfsQ.push(Pos(p.row + rOff, p.col + cOff, p.dis + 1));
                        }
                    }
                }
            }
        }
    }
}

void findMinMov() {
    // enumerate ending point
    for (int er = 0; er < R; er++) {
        for (int ec = 0; ec < C; ec++) {
            short mov = 0;
            // if no pickup 
            for (int knr = 0; knr < R; knr++) {
                for (int knc = 0; knc < C; knc++) {
                    if (chess[knr][knc] != 1) continue;
                    mov += pKn[er][ec][knr][knc];
                    if (mov >= 10000) mov = 10000;
                }
            }
            mov += pKi[er][ec][kir][kic];
            if (mov >= 10000) continue;
            if (mov < minMov) minMov = mov;
            // enumerate pickup knight
            for (int knr = 0; knr < R; knr++) {
                for (int knc = 0; knc < C; knc++) {
                    if (chess[knr][knc] != 1) continue;
                    // enumerate pickup point
                    for (int rOff = -4; rOff <= 4; rOff++) {
                        for (int cOff = -4; cOff <= 4; cOff++) {
                            int pr = kir + rOff;
                            int pc = kic + cOff;
                            if (pr >= 0 && pr < R && pc >= 0 && pc < C &&
                                pKn[knr][knc][er][ec] < 10000 &&
                                pKi[kir][kic][er][ec] < 10000 &&
                                pKn[knr][knc][pr][pc] < 10000 &&
                                pKi[kir][kic][pr][pc] < 10000 &&
                                pKn[pr][pc][er][ec] < 10000) {
                                int pickMov = mov - pKn[knr][knc][er][ec] - pKi[kir][kic][er][ec] +
                                              pKn[knr][knc][pr][pc] + pKi[kir][kic][pr][pc] +
                                              pKn[pr][pc][er][ec];
                                if (pickMov < minMov) minMov = pickMov;
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    fin >> R >> C;
    int chessR;
    string chessC;
    fin >> chessC >> chessR;
    kir = chessR - 1;
    kic = chessC[0] - 'A';
    chess[kir][kic] = 2;

    while (fin >> chessC) {
        fin >> chessR;
        chess[chessR - 1][chessC[0] - 'A'] = 1;
    }

    BFSKi();
    BFSKn();
    findMinMov();

    fout << minMov << endl;

    return 0;
}

