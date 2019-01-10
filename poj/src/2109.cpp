/*
 * POJ 2109 - Power of Cryptography
 *
 * Note constant optimization by make k range thinner
 * Test data might contain k such that k^n != p,
 * actually it's argmax(k)(k^n <= p)
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class BigInt {
public:
    string digits;
    BigInt(const string &_digits) {
        digits = _digits;
        reverse(digits.begin(), digits.end());
    }
    BigInt(unsigned long long _num) {
        if (_num == 0) {
            digits = "0";
        } else {
            while (_num) {
                digits += '0' + (_num % 10);
                _num /= 10;
            }
        }
    }
    string toString() const {
        string result = digits;
        reverse(result.begin(), result.end());
        return result;
    }
    BigInt operator+ (const BigInt& b) {
        string result;
        int selfLen = digits.length(), bLen = b.digits.length();
        int idx = 0;
        int sum, carry = 0;
        while (idx < selfLen || idx < bLen) {
            sum = carry;
            if (idx < selfLen) sum += (digits[idx] - '0');
            if (idx < bLen) sum += (b.digits[idx] - '0');
            result += (sum % 10) + '0';
            carry = sum / 10;
            idx++;
        }
        if (carry) result += carry + '0';
        reverse(result.begin(), result.end());
        return BigInt(result);
    }
    BigInt operator* (const BigInt& b) {
        string zeroStr = "";
        BigInt result(0);
        int bLen = b.digits.length();
        for (int i = 0; i < bLen; i++) {
            string base = zeroStr + digits;
            reverse(base.begin(), base.end());
            for (int j = 0; j < b.digits[i] - '0'; j++) {
                result = result + BigInt(base);
            }
            zeroStr += '0';
        }
        return result;
    }
    BigInt pow(int n) {
        string normalDigits = digits;
        reverse(normalDigits.begin(), normalDigits.end());
        BigInt tmpPow(normalDigits), result(1);
        while (n) {
            if (n & 1) result = result * tmpPow;
            tmpPow = tmpPow * tmpPow;
            n >>= 1;
        }
        return result;
    }
    bool operator< (const BigInt& b) const {
        if (digits.length() != b.digits.length()) {
            return digits.length() < b.digits.length();
        } else {
            return toString() < b.toString();
        }
    }
    bool operator== (const BigInt& b) const {
        return digits == b.digits;
    }
};

int main() {
    int n;
    string pStr;
    while (cin >> n) {
        cin >> pStr;
        BigInt p(pStr);
        int kLen = (int)ceil((double)pStr.length() / n); 
        unsigned long long left = 1, right = 1;
        while (kLen--) {
            left *= 10;
            right *= 10;
        }
        left /= 10;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            BigInt midResult = BigInt(mid).pow(n);
            if (midResult < p) left = mid;
            else right = mid;
        }
        if (BigInt(right).pow(n) == p) cout << BigInt(right).toString() << endl;
        else cout << BigInt(left).toString() << endl;
    }
    return 0;
}
