class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int sLen = s.length();
        int leftCnt = 0, rightCnt = 0;
        for (int i = 0; i < sLen; i++) {
            if (s[i] == '(') {
                leftCnt++;
            } else if (s[i] == ')') {
                if (leftCnt > 0) leftCnt--;
                else rightCnt++;
            }
        }
        set<string> result;
        string partResult;
        dfs(s, 0, 0, 0, leftCnt, rightCnt, partResult, result);
        return vector<string>(result.begin(), result.end());
    }
    
    void dfs(string &s, int idx, int leftCnt, int rightCnt,
             int restLeft, int restRight,
             string &partResult, set<string> &result) {
        int sLen = s.length();
        if (idx == sLen) {
            if (restLeft == 0 && restRight == 0) {
                result.insert(partResult);
            }
        } else {
            // ")(", idx == 0, restLeft == restRight == 1, sLen == 2
            if (idx > sLen - restLeft - restRight) return;
            if (s[idx] == '(' && restLeft > 0) {
                dfs(s, idx + 1, leftCnt, rightCnt, restLeft - 1, restRight, partResult, result);
            } else if (s[idx] == ')' && restRight > 0) {
                dfs(s, idx + 1, leftCnt, rightCnt, restLeft, restRight - 1, partResult, result);
            }
            partResult.push_back(s[idx]);
            if (s[idx] == '(') {
                dfs(s, idx + 1, leftCnt + 1, rightCnt, restLeft, restRight, partResult, result);
            } else if (s[idx] == ')') {
                if (rightCnt < leftCnt) {
                    dfs(s, idx + 1, leftCnt, rightCnt + 1, restLeft, restRight, partResult, result);
                }
            } else {
                dfs(s, idx + 1, leftCnt, rightCnt, restLeft, restRight, partResult, result);
            }
            partResult.pop_back();
        }
    }
};