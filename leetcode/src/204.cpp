class Solution {
public:
    int loopNum = 10;
    
    long long powerMod(long long a, long long b, long long n) {
        long long result = 1, currPow = a;
        while (b) {
            if (b & 1) result = (result * currPow) % n;
            currPow = (currPow * currPow) % n;
            b >>= 1;
        }
        return result;
    }
    
    bool millerRabin(long long n) {
        long long base = 1LL + (long long)(double(rand()) / (RAND_MAX + 1U) * (n - 1));
        long long power = n - 1;
        while (!(power & 1)) {
            power >>= 1;
        }
        long long root = powerMod(base, power, n);
        while (power != n - 1 && root != 1 && root != n - 1) {
            root = (root * root) % n;
            power <<= 1;
        }
        return (power & 1) || root == n - 1;
    }

    bool isPrime(long long n) {
        if (n <= 1) return false;
        if (n == 2) return true;
        if ((n % 2) == 0) return false;
        for (int i = 0; i < loopNum; i++) {
            if (!millerRabin(n)) return false;
        }
        return true;
    }
    
    int countPrimes(int n) {
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (isPrime(i)) result++;
        }
        return result;
    }
};