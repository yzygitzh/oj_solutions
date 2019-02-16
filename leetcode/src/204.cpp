/*
 * LeetCode 204 Count Primes
 */

class Solution {
public:
    const int loopNum = 10;

    long long powerMod(long long a, long long b, long long n) {
      long long currPow = a, result = 1;
      while (b) {
        if (b & 1) {
          result = (result * currPow) % n;
        }
        currPow = (currPow * currPow) % n;
        b >>= 1;
      }
      return result;
    }
    
    bool millerRabin(long long n) {
        long long base = 1LL + (long long)(double(rand()) / (RAND_MAX + 1U) * (n - 1));
        // find p and q such that n - 1 == 2^p * q
        long long q = n - 1, p = 0;
        while (!(q & 1)) {
            p++;
            q >>= 1;
        }
        long long power = powerMod(base, q, n);
        while (q != n - 1 && power != 1 && power != n - 1) {
            power = (power * power) % n;
            q <<= 1;
        }
        return (q & 1) == 1 || power == n - 1;
    }

    int isPrime(int n) {
      if (n <= 1) return false;
      if (n == 2 || n == 3 || n == 5 || n == 7) return true;
      if ((n % 2) == 0 || (n % 3) == 0 ||
          (n % 5) == 0 || (n % 7) == 0) return false;
      for (int i = 0; i < loopNum; i++) {
        if (!millerRabin(n)) return false;
      }
      return true;
    }

    int countPrimes(int n) {
      int count = 0;
      for (int i = 1; i < n; i++) {
        if (isPrime(i)) count++;
      }
      return count;
    }
};
