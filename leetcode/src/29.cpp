class Solution {
public:
    int divide(int dividend, int divisor) {
        int sign = 1;
        if (dividend == (1 << 31) && divisor == -1) return ~(1 << 31);
        if (dividend < 0) {
            sign = -sign;   
            dividend = -dividend;
        }
        if (divisor < 0) {
            sign = -sign;   
            divisor = -divisor;
        }
        
        unsigned uDividend = dividend;
        unsigned uDivisor = divisor;
        unsigned quotient = 0;
        while (uDividend >= uDivisor) {
            unsigned sub = uDivisor;
            unsigned partQuotient = 1;
            while (sub < (1 << 31) && sub + sub <= uDividend) {
                sub += sub;
                partQuotient += partQuotient;
            }
            quotient += partQuotient;
            uDividend -= sub;
        }
        
        return sign < 0 ? -(int)quotient : (int)quotient;
    }
};