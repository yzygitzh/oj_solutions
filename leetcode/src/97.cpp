class Solution {
public:
    map<vector<int>, bool> memo;
    
    bool isInterleave(string s1, string s2, string s3) {
        int s1Len = s1.length(), s2Len = s2.length(), s3Len = s3.length();
        if (s1Len + s2Len != s3Len) {
            return false;
        }
        if (memo.find(vector<int>{s1Len, s2Len, s3Len}) != memo.end()) {
            return memo[vector<int>{s1Len, s2Len, s3Len}];
        }
        if (s1Len == 0) {
            memo[vector<int>{s1Len, s2Len, s3Len}] = s2 == s3;
            return memo[vector<int>{s1Len, s2Len, s3Len}];
        }
        if (s2Len == 0) {
            memo[vector<int>{s1Len, s2Len, s3Len}] = s1 == s3;
            return memo[vector<int>{s1Len, s2Len, s3Len}];
        }
        bool lastInS1 = s1[s1Len - 1] == s3[s3Len - 1] &&
                        isInterleave(s1.substr(0, s1Len - 1), s2,
                                     s3.substr(0, s3Len - 1));
        bool lastInS2 = s2[s2Len - 1] == s3[s3Len - 1] &&
                        isInterleave(s1, s2.substr(0, s2Len - 1),
                                     s3.substr(0, s3Len - 1));
        if (lastInS1 || lastInS2) {
            memo[vector<int>{s1Len, s2Len, s3Len}] = true;
            return memo[vector<int>{s1Len, s2Len, s3Len}];
        }
        memo[vector<int>{s1Len, s2Len, s3Len}] = false;
        return memo[vector<int>{s1Len, s2Len, s3Len}];
    }
};