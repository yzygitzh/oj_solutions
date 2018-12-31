class Solution {
public:
    int powerN(int a, int n) {
        int result = 1;
        for (int i = 0; i < n; i++) {
            result = (result * a) % 1337;
        }
        return result;
    }
    
    int superPow(int a, vector<int>& b) {
        // a^13 = a^10 * a^3 = (a^1)^10 * (a^3)
        int bLen = b.size();
        if (bLen == 0) return 0;
        if (bLen == 1 && b[0] == 0) return 1;
        int result = 1;
        int currPow = (a % 1337);
        for (int i = bLen - 1; i >= 0; i--) {
            result = (result * powerN(currPow, b[i])) % 1337;
            currPow = powerN(currPow, 10);
        }
        return result;
    }
};