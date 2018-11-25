class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        DFS(n, n, "", result);
        return result;
    }
    
    void DFS(int leftRest, int rightRest, string currStr, vector<string> &result) {
        if (leftRest == 0 && rightRest == 0) {
            result.push_back(currStr);
        } else {
            if (leftRest > 0) {
                DFS(leftRest - 1, rightRest, currStr + '(', result);
            }
            if (rightRest > 0 && rightRest > leftRest) {
                DFS(leftRest, rightRest - 1, currStr + ')', result);
            }
        }
    }
};