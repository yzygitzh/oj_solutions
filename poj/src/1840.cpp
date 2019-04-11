/*
 * POJ 1840 - Eqs
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
#include <unordered_map>
#include <cmath>

using namespace std;

int main() {
    int coeff[5];
    for (int i = 0; i < 5; i++) {
        cin >> coeff[i];
    }
    unordered_map<int, long long> cnt1, cnt2;
    for (int i = -50; i <= 50; i++) {
        for (int j = -50; j <= 50; j++) {
            if (i == 0 || j == 0) continue;
            cnt1[coeff[0] * i * i * i + coeff[1] * j * j * j]++;
            cnt2[coeff[2] * i * i * i + coeff[3] * j * j * j]++;
        }
    }
    long long result = 0;
    for (int i = -50; i <= 50; i++) {
        if (i == 0) continue;
        // do two-sum for cnt1 and cnt2
        int sum = -coeff[4] * i * i * i;
        for (auto itr = cnt2.begin(); itr != cnt2.end(); ++itr) {
            if (cnt1.find(sum - itr->first) != cnt1.end()) {
                result += itr->second * cnt1[sum - itr->first];
            }
        }
    }
    cout << result << endl;

    return 0;
}

