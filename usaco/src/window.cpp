/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: window
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
#include <utility>

#pragma pack(1)
using namespace std;

/*
 * Special trick in rectangle dividing
 */

ifstream fin ("window.in");
ofstream fout ("window.out");

int getMin(int x, int y) {
    return x < y ? x : y;
}

int getMax(int x, int y) {
    return x > y ? x : y;
}

class Window {
public:
    int x, X, y, Y;
    char wid;
    Window *next, *prev;
    Window(char _wid, int _x, int _X, int _y, int _Y)
        : wid(_wid), x(_x), X(_X), y(_y), Y(_Y), next(NULL), prev(NULL) {}
};
map<char, Window*> wid2wptr;
Window *whead = NULL, *wtail = NULL;

void createWindow(char wid, int x, int X, int y, int Y, bool reverse) {
    Window *wptr = new Window(wid, x, X, y, Y);
    wid2wptr[wptr->wid] = wptr;
    if (whead == NULL && wtail == NULL) {
        whead = wtail = wptr;
    } else {
        if (reverse) {
            whead->prev = wptr;
            wptr->next = whead;
            whead = wptr;
        } else {
            wtail->next = wptr;
            wptr->prev = wtail;
            wtail = wptr;
        }
    }
}

void deleteWindow(char wid) {
    Window *wptr = wid2wptr[wid];
    if (whead == wptr) {
        whead = wptr->next;
        if (whead != NULL) whead->prev = NULL;
    }
    if (wtail == wptr) {
        wtail = wptr->prev;
        if (wtail != NULL) wtail->next = NULL;
    }
    if (wptr->prev != NULL) wptr->prev->next = wptr->next;
    if (wptr->next != NULL) wptr->next->prev = wptr->prev;
    delete wptr;
}

void bringTop(char wid) {
    Window *p = wid2wptr[wid];
    Window q = *p;
    deleteWindow(wid);
    createWindow(q.wid, q.x, q.X, q.y, q.Y, false);
}

void putBottom(char wid) {
    Window *p = wid2wptr[wid];
    Window q = *p;
    deleteWindow(wid);
    createWindow(q.wid, q.x, q.X, q.y, q.Y, true);
}

int floatUpWindow(Window *p, int x, int X, int y, int Y) {
    // no more window
    if (p == NULL) return (X - x + 1) * (Y - y + 1);
    // no intersection, float up all window area
    if (x > p->X || X < p->x || y > p->Y || Y < p->y) {
        return floatUpWindow(p->next, x, X, y, Y);
    }
    // there being intersections, float up non-intersecting area
    // intersections from four directions
    int area = 0;
    // up 
    if (x < p->x) {
        area += floatUpWindow(p->next, x, p->x - 1, y, Y);
        x = p->x;
    }
    // down
    if (X > p->X) {
        area += floatUpWindow(p->next, p->X + 1, X, y, Y);
        X = p->X;
    }
    // now head and foot are erased
    // left
    if (y < p->y) {
        area += floatUpWindow(p->next, x, X, y, p->y - 1);
        y = p->y;
    }
    // right
    if (Y > p->Y) {
        area += floatUpWindow(p->next, x, X, p->Y + 1, Y);
        Y = p->Y;
    }
    return area;
}

double calcPercentage(char wid) {
    Window *p = wid2wptr[wid];
    double totalArea = (p->X - p->x + 1) * (p->Y - p->y + 1);
    double restArea = floatUpWindow(p->next, p->x, p->X, p->y, p->Y);
    return restArea / totalArea * 100;
}

int main() {
    string inputLine;
    char inputChar;
    while (true) {
        char command;
        char wid;
        if (!(fin >> command)) break;
        fin >> inputChar;
        fin >> wid;
        fin >> inputChar;
        // cout << command << " " << wid << endl;
        // if (whead != NULL) cout << whead->wid << " " << wtail->wid << endl;
        switch (command) {
            case 'w':
                int x1, x2, y1, y2;
                fin >> x1 >> inputChar >> y1 >> inputChar >> x2 >> inputChar >> y2;
                createWindow(wid,
                             getMin(x1, x2), getMax(x1, x2) - 1,
                             getMin(y1, y2), getMax(y1, y2) - 1, false);
                break;
            case 't':
                bringTop(wid);
                break;
            case 'b':
                putBottom(wid);
                break;
            case 'd':
                deleteWindow(wid);
                break;
            case 's':
                double per = calcPercentage(wid);
                fout << setprecision(3) << fixed << per << endl;
                break;
        }
        getline(fin, inputLine);
    }
    return 0;
}
