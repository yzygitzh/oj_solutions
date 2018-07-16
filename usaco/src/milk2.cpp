/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: milk2
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Interval {
public:
    int left;
    int right;
    bool milking;
    Interval *next;
    Interval(int l, int r, bool m):left(l),right(r),milking(m),next(NULL){}
};

bool compareInterval(const Interval a, const Interval b) {
    if (a.left < b.left || a.left == b.left && a.right < b.right) {
        return true;
    }
    return false;
}

using namespace std;

int main() {
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");

    int N;
    fin >> N;
    int left, right;
    vector<Interval> intervals;

    for (int i = 0; i < N; i++) {
        fin >> left >> right;
        intervals.push_back(Interval(left, right, true));
    }

    sort(intervals.begin(), intervals.end(), compareInterval);

    Interval *listHead = NULL;
    Interval *listTail = NULL;

    for (int i = 0; i < N; i++) {
        Interval *currInterval = new Interval(intervals[i].left, intervals[i].right, true);
        if (i == 0) {
            listHead = listTail = currInterval;
        }
        if (currInterval->left <= listTail->right) {
            if (currInterval->right > listTail->right) {
                listTail->right = currInterval->right;
            }
        } else {
            listTail->next = new Interval(listTail->right, currInterval->left, false);
            listTail->next->next = currInterval;
            listTail = currInterval;
        }
    }

    int maxMilking = 0;
    int maxEmpty = 0;
    for (Interval *p = listHead; p != NULL; p = p->next) {
        int val = p->right - p->left;
        if (p->milking && val > maxMilking) {
            maxMilking = val;
        } else if (!p->milking && val > maxEmpty) {
            maxEmpty = val;
        }
    }

    fout << maxMilking << " " << maxEmpty << endl;

    return 0;
}

