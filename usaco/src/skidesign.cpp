/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: skidesign
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
#include <string>

using namespace std;

/*
 * Note that the cost's derivative is monotonous
 * so it's fine to bin-search
 */

int N, hill;
vector<int> hills;

// calculate the y's derivative relative to [x, x+17]
int calcDeriCost(int x) {
    int totalCost = 0, y;
    for (int i = 0; i < N; i++) {
        y = hills[i];
        if (x > y) {
            totalCost += 2 * (x - y);
        } else if (x < y - 17) {
            totalCost += 2 * (x - y + 17);
        }
    }
    return totalCost;
}

int calcCost(int x) {
    int totalCost = 0, y;
    for (int i = 0; i < N; i++) {
        y = hills[i];
        if (x > y) {
            totalCost += (x - y) * (x - y);
        } else if (x + 17 < y) {
            totalCost += (x - y + 17) * (x - y + 17);
        }
    }
    return totalCost;
}

int binSearch() {
    int minHill = hills[0];
    int maxHill = hills[N - 1];
    if (minHill + 17 >= maxHill) {
        return 0;
    }
    int left = minHill, right = maxHill - 17, mid, cost;
    while (left + 1 < right) {
        mid = (left + right) / 2; 
        cost = calcDeriCost(mid);
        // cout << "mid " << mid << endl;
        // cout << "cost " << cost << endl;
        if (cost < 0) {
            left = mid;
        } else if (cost > 0) {
            right = mid;
        } else {
            return calcCost(mid);
        }
    }
    // cout << left << endl;
    // cout << right << endl;
    int leftVal = calcCost(left);
    int rightVal = calcCost(right);
    return leftVal < rightVal ? leftVal : rightVal;
}

int main() {
    ofstream fout ("skidesign.out");
    ifstream fin ("skidesign.in");

    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> hill;
        hills.push_back(hill);
    }
    sort(hills.begin(), hills.end());

    fout << binSearch() << endl; 

    return 0;
}

