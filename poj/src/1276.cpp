/*
 * POJ 1276 - Cash Machine
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

int F[2][100010];
int bills[200];
int billNum = 0;
int totalCash;

int main() {
    while (cin >> totalCash) {
        billNum = 0;
        int tmpBillNum;
        cin >> tmpBillNum;
        for (int i = 0; i < tmpBillNum; i++) {
            int billCnt, billVal;
            cin >> billCnt >> billVal;
            int tmpCnt = 1;
            while (billCnt > tmpCnt) {
                bills[billNum++] = tmpCnt * billVal;
                billCnt -= tmpCnt;
                tmpCnt *= 2;
            }
            if (billCnt) {
                bills[billNum++] = billCnt * billVal;
            }
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 100010; j++) {
                F[i][j] = 0;
            }
        }
        F[0][0] = 1;
        for (int i = 1; i <= billNum; i++) {
            for (int j = 0; j <= totalCash; j++) {
                // don't use cash i
                F[i % 2][j] |= F[(i - 1) % 2][j];
                // use cash i
                if (j + bills[i - 1] <= totalCash) {
                    F[i % 2][j + bills[i - 1]] |= F[(i - 1) % 2][j];
                }
            }
        }
        int maxCash = 0;
        for (int i = 0; i <= totalCash; i++) {
            if (F[billNum % 2][i]) maxCash = i;
        }
        cout << maxCash << endl;
    }
    return 0;
}

