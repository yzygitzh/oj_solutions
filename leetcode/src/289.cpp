class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int bitCnt = 0;
                for (int p = -1; p <= 1; p++) {
                    for (int q = -1; q <= 1; q++) {
                        if (!(p == 0 && q == 0) &&
                            0 <= i + p && i + p < m &&
                            0 <= j + q && j + q < n) {
                            bitCnt += board[i + p][j + q] & 1;
                        }
                    }
                }
                if (board[i][j] & 1) {
                    if (bitCnt == 2 || bitCnt == 3) board[i][j] |= (1 << 1);
                } else {
                    if (bitCnt == 3) board[i][j] |= (1 << 1);
                }
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] >>= 1;
            }
        }
    }
};