/*
 * POJ 2115 - C Looooops
 *
 */

#include <cstdio>
#include <cstdlib>
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

long long exgcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        long long r = exgcd(b, a % b, x, y);
        long long t = x;
        x = y;
        y = t - a / b * y;
        return r;
    }
}

// find minimum x for ax=b mod n, return -1 if no solution
// this is the same to solve ax + ny = b.
// so only have solution when gcd(a, n) | b.
long long mle(long long a, long long b, long long n) {
    long long x, y;
    long long r = exgcd(a, n, x, y);
    if (b % r) return -1;
    // now x is solution of ax + ny = r, where r | b
    long long x0 = (x * b / r) % n;
    // now x0 is solution of ax + ny = b

    // there are total r solutions in [0, n), and
    // all solutions in [0, n) have interval n/r among
    // themselves, and the minimum solution falls into
    // the [0, n/r) interval
    return (x0 % (n / r) + n / r) % (n / r);
}

int main() {
    long long A, B, C, k;
    while (true) {
        cin >> A >> B >> C >> k;
        if (k == 0) break;
        // find minimum solution of A+Cx=B mod 2^k
        // i.e. Cx=B-A mod 2^k
        long long bMinusA = B - A;
        long long kPow = (1LL << k);
        while (bMinusA < 0) bMinusA += kPow;
        long long sol = mle(C, bMinusA, kPow);
        if (sol < 0) {
            cout << "FOREVER" << endl;
        } else {
            cout << sol << endl;
        }
    }
    return 0;
}

