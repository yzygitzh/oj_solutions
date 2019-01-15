/*
 * POJ 2586 - Y2K Accounting Bug
 *
 * S for surplus, D for deficit
 * Greedily use sequences of S..D.. cominations such that total sum is the max
 * eg: SDDDDSDDDDSD or SSDDDSSDDDSS
 * Proof: for any interval, we can replace it by the optimal solution
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    long long s, d;
    while (cin >> s >> d) {
        long long sNum = 0, dNum = 5;
        // maximize sNum
        while ((sNum + 1) * s < (dNum - 1) * d) {
            sNum++;
            dNum--;
        }
        long long annualSum = 2 * (sNum * s - dNum * d);
        if (sNum == 0) annualSum -= 2 * d;
        else if (sNum == 1) annualSum += s - d;
        else annualSum += 2 * s;
        if (annualSum < 0) cout << "Deficit" << endl;
        else cout << annualSum << endl;
    }
    return 0;
}
