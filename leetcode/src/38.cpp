class Solution {
public:
    string countAndSay(int n) {
        string result = "1";
        for (int i = 2; i <= n; i++) {
            string newResult;
            int idx = 0, resultLen = result.length();
            while (idx < resultLen) {
                int oldIdx = idx;
                while (idx < resultLen && result[oldIdx] == result[idx]) {
                    idx++;
                }
                newResult += to_string(idx - oldIdx);
                newResult += result[oldIdx];
            }
            result = newResult;
        }
        return result;
    }
};