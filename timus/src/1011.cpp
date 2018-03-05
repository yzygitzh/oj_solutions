/*
 * TIMUS 1011 - Conductors
 *
 * "more than" and "less than" needs EPS...
 */

#include <cstdio>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

double EPS = 1e-10;

int main() {
    double P, Q;
    int citizenNum = 1;
    scanf("%lf%lf", &P, &Q);
    P += EPS;
    Q -= EPS;
    while (true) {
        if (ceil(citizenNum * P / 100) <= floor(citizenNum * Q / 100))
            break;
        citizenNum += 1;
    }
    printf("%d\n", citizenNum);

    return 0;
}
