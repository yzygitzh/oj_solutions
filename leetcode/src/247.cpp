class Solution {
public:
    vector<string> result;
    
    vector<string> findStrobogrammatic(int n) {
        // 0, 1, 69, 8
        dfs(n, "", "");
        sort(result.begin(), result.end());
        return result;
    }
    
    void dfs(int restN, string left, string right) {
        if (restN == 0) {
            result.push_back(left + right);
        } else if (restN == 1) {
            result.push_back(left + "0" + right);
            result.push_back(left + "1" + right);
            result.push_back(left + "8" + right);
        } else {
            dfs(restN - 2, left + "6", string("9") + right);
            dfs(restN - 2, left + "9", string("6") + right);
            dfs(restN - 2, left + "1", string("1") + right);
            dfs(restN - 2, left + "8", string("8") + right);
            if (left.length() > 0) {
                dfs(restN - 2, left + "0", string("0") + right);
            }
        }
    }
};