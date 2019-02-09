/*
 * POJ 2388 - Who's in the Middle
 *
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

int main() {
    int cowNum;
    cin >> cowNum;
    vector<int> cows(cowNum);
    for (int i = 0; i < cowNum; i++) {
        cin >> cows[i];
    }
    nth_element(cows.begin(), cows.begin() + cowNum / 2, cows.end());
    cout << cows[cowNum / 2] << endl;
    return 0;
}

