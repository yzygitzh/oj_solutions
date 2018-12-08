class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size();
        if (m == 0) return;
        int n = board[0].size();
        if (n == 0) return;
        
        for (int i = 0; i < m; i++) {
            if (board[i][0] == 'O') color(board, i, 0);
            if (board[i][n - 1] == 'O') color(board, i, n - 1);
        }
        
        for (int i = 0; i < n; i++) {
            if (board[0][i] == 'O') color(board, 0, i);
            if (board[m - 1][i] == 'O') color(board, m - 1, i);
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'C') board[i][j] = 'O';
                else if (board[i][j] == 'O') board[i][j] = 'X';
            }
        }
    }
    
    void color(vector<vector<char>>& board, int row, int col) {
        board[row][col] = 'C';
        if (row - 1 >= 0 && board[row - 1][col] == 'O') color(board, row - 1, col);
        if (row + 1 < board.size() && board[row + 1][col] == 'O') color(board, row + 1, col);
        if (col - 1 >= 0 && board[row][col - 1] == 'O') color(board, row, col - 1);
        if (col + 1 < board[0].size() && board[row][col + 1] == 'O') color(board, row, col + 1);
    }
};