class Solution {
public:
    string addNum(string n1, string n2) {
        reverse(n1.begin(), n1.end());
        reverse(n2.begin(), n2.end());
        string result;
        int idx = 0, carry = 0;
        while (idx < n1.length() || idx < n2.length()) {
            int sum = carry;
            if (idx < n1.length()) sum += n1[idx] - '0';
            if (idx < n2.length()) sum += n2[idx] - '0';
            carry = sum / 10;
            result += (char)('0' + (sum % 10));
            idx++;
        }
        if (carry) result += (char)('0' + carry);
        reverse(result.begin(), result.end());
        return result;
    }
    
    bool isAdditiveNumber(string num) {
        for (int i = 1; i < num.length(); i++) {
            if (i > 1 && num[0] == '0') break;
            for (int j = 1; i + j < num.length(); j++) {
                if (j > 1 && num[i] == '0') break;
                if (tryNum(num, i + j,
                           num.substr(0, i), num.substr(i, j))) {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool tryNum(string& num, int startIdx,
                string n1, string n2) {
        if (startIdx == num.length()) {
            return true;
        } else {
            string sum = addNum(n1, n2);
            if (num.length() - sum.length() >= startIdx &&
                sum == num.substr(startIdx, sum.length())) {
                return tryNum(num, startIdx + sum.length(), n2, sum);
            } else {
                return false;
            }
        }
    }
};