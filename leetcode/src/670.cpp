class Solution {
public:
    int maximumSwap(int num) {
        map<int, set<int>> digitToPos;
        vector<int> digits;
        while (num) {
            digitToPos[num % 10].insert(digits.size());
            digits.push_back(num % 10);
            num /= 10;
        }
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] < digitToPos.rbegin()->first) {
                swap(digits[i], digits[*(digitToPos.rbegin()->second.begin())]);
                break;
            }
            digitToPos[digits[i]].erase(i);
            if (digitToPos[digits[i]].empty()) {
                digitToPos.erase(digits[i]);
            }
        }
        int result = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            result *= 10;
            result += digits[i];
        }
        return result;
    }
};