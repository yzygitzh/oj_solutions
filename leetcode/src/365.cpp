class Solution {
public:
    int exGcd(int a, int b, int& x, int &y) {
        if (a < b) return exGcd(b, a, y, x);
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        int gcd = exGcd(b, a % b, y, x);
        y -= (a / b) * x;
        return gcd;
    }
    
    bool canMeasureWater(int a, int b, int z) {
        if (z == 0) return true;
        if (a + b < z) return false;
        int x, y;
        int gcd = exGcd(a, b, x, y);
        return !(z % gcd);
    }
};