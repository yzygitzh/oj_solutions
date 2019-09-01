class Solution {
public:
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    
    bool canMeasureWater(int a, int b, int z) {
        if (z == 0) return true;
        if (a + b < z) return false;
        return !(z % gcd(a, b));
    }
};