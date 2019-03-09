class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> result;
        int carry = 1;
        for (auto itr = digits.rbegin(); itr != digits.rend(); ++itr) {
            int sum = carry + (*itr);
            result.push_back(sum % 10);
            carry = sum / 10;
        }
        if (carry > 0) result.push_back(carry);
        reverse(result.begin(), result.end());
        return result;
    }
};