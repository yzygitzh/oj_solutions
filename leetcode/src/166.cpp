class Solution {
public:
    string fractionToDecimal(int numerator_int, int denominator_int) {
        long long numerator = numerator_int;
        long long denominator = denominator_int;
        vector<long long> quotient;
        unordered_map<long long, long long> divPos;
        
        long long sign = 1;
        if (numerator < 0) {
            numerator = -numerator;
            sign *= -1;    
        }
        if (denominator < 0) {
            denominator = -denominator;
            sign *= -1;
        }
        if (numerator == 0 || denominator == 0) sign = 0;
        
        // get integer part first
        quotient.push_back(numerator / denominator);
        numerator = (numerator % denominator) * 10;
        
        while (numerator && divPos.find(numerator) == divPos.end()) {
            divPos[numerator] = quotient.size();
            quotient.push_back(numerator / denominator);
            numerator = (numerator % denominator) * 10;
        }
        
        string result;
        if (sign < 0) result += '-';
        result += to_string(quotient[0]);
        if (quotient.size() == 1) return result; // no fraction
        result += '.';
        if (!numerator) { // no loop
            for (int i = 1; i < quotient.size(); i++) result += to_string(quotient[i]);
        } else {
            for (int i = 1; i < divPos[numerator]; i++) result += to_string(quotient[i]);
            result += '(';
            for (int i = divPos[numerator]; i < quotient.size(); i++) {
                result += to_string(quotient[i]);
            }
            result += ')';
        }
        return result;
    }
};