/*
 * POJ 3349 - Snowflake Snow Snowflakes
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

vector<int> getLexMin(vector<int> snow) {
    vector<int> result = snow;
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < 6; i++) {
            int firstLeg = snow[0];
            for (int i = 0; i < 5; i++) {
                snow[i] = snow[i + 1];
            }
            snow[5] = firstLeg;
            result = min(result, snow);
        }
        reverse(snow.begin(), snow.end());
    }
    return result;
}

int main() {
    int snowNum;
    cin >> snowNum;
    set<vector<int> > snowSet;
    bool found = false;
    for (int i = 0; i < snowNum; i++) {
        vector<int> snow(6);
        for (int j = 0; j < 6; j++) {
            cin >> snow[j];
        }
        vector<int> minSnow = getLexMin(snow);
        if (snowSet.count(minSnow)) {
            found = true;
        }
        snowSet.insert(minSnow);
    }
    if (found) cout << "Twin snowflakes found." << endl;
    else cout << "No two snowflakes are alike." << endl;
    return 0;
}

