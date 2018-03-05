/*
 * TIMUS 1010 - Discrete Function
 *
 * 1. The inclination is the abs value
 * 2. The long long type cannot hold input properly
 */

#include <cstdio>

using namespace std;

long double points[100010];

int main() {
    int pointNum, left;
    long double k, currK;
    scanf("%d", &pointNum);
    for (int i = 0; i < pointNum; i++) {
        scanf("%llf", points + i);
        if (i == 0) continue;
        currK = points[i] - points[i - 1];
        currK = currK < 0 ? -currK : currK;
        if (i == 1 || currK > k) {
            k = currK;
            left = i;
        }
    }
    printf("%d %d\n", left, left + 1);

    return 0;
}
