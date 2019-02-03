class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int result = 0;
        
        int m = board.size();
        if (m == 0) return result;
        int n = board[0].size();
        if (n == 0) return result;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'X' &&
                    (i - 1 < 0 || board[i - 1][j] == '.') &&
                    (j - 1 < 0 || board[i][j - 1] == '.')) {
                    result++;
                }
            }
        }
        
        return result;
    }
};