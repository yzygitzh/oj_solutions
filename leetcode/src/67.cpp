class Solution {
public:
    string addBinary(string a, string b) {
        string result;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int aIdx = 0, bIdx = 0;
        int aLen = a.length(), bLen = b.length();
        int carry = 0;
        while (aIdx < aLen || bIdx < bLen) {
            int sum = carry;
            if (aIdx < aLen) {
                sum += a[aIdx] - '0';
                aIdx++;
            }
            if (bIdx < bLen) {
                sum += b[bIdx] - '0';
                bIdx++;
            }
            result.push_back((char)('0' + (sum % 2)));
            carry = sum / 2;
        }
        if (carry > 0) result.push_back((char)('0' + carry));
        reverse(result.begin(), result.end());
        return result;
    }
};