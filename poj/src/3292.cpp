/*
 * POJ 3292 - Semi-prime H-numbers
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

unsigned char sieve[250010] = {0};
vector<long long> primes;
set<long long> semiPrimesSet;
vector<long long> semiPrimes;

void calcSemiPrimes() {
    for (long long i = 1; i <= 250000; i++) {
        if (!sieve[i]) {
            primes.push_back(4 * i + 1);
            for (long long j = 0; (4 * i + 1) * (4 * j + 1) <= 1000001; j++) {
                sieve[(4 * i + 1) * (4 * j + 1) / 4] = 1;
            }
        }
    }

    for (int i = 0; i < primes.size(); i++) {
        for (int j = i; j < primes.size(); j++) {
            long long semiPrime = primes[i] * primes[j];
            if (semiPrime > 1000001) {
                break;
            }
            if (semiPrimesSet.find(semiPrime) == semiPrimesSet.end()) {
                semiPrimesSet.insert(semiPrime);
                semiPrimes.push_back(semiPrime);
            }
        }
    }

    sort(semiPrimes.begin(), semiPrimes.end());
}

int main() {
    calcSemiPrimes();
    long long h;
    while (true) {
        cin >> h;
        if (h == 0) break;
        int left = 0, right = semiPrimes.size() - 1;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (semiPrimes[mid] < h) {
                left = mid;
            } else {
                right = mid;
            }
        }
        cout << h << " ";
        if (semiPrimes[left] > h) {
            cout << left;
        } else if (semiPrimes[right] > h) {
            cout << right;
        } else {
            cout << right + 1;
        }
        cout << endl;
    }
    return 0;
}

