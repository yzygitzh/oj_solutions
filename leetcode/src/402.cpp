class Solution {
public:
    string removeKdigits(string num, int k) {
        // greedy choose smallest digit
        // use mono stack
        
        int idx = 0;
        int numLen = num.length();
        vector<int> numStack;
        while (idx < numLen) {
            while (numStack.size() > 0 &&
                   *numStack.rbegin() > num[idx] - '0' &&
                   numStack.size() + k > idx) {
                numStack.pop_back();
            }
            if (numStack.size() < numLen - k) {
                numStack.push_back(num[idx] - '0');
            }
            idx++;
        }
        string result;
        bool firstZero = true;
        for (auto itr = numStack.begin();
             itr != numStack.end(); ++itr) {
            if (firstZero && (*itr) == 0) continue;
            firstZero = false;
            result += '0' + (*itr);
        }
        if (result.length() == 0) return "0";
        else return result;
    }
};