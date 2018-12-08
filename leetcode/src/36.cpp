class Solution {
public:
    unordered_set<int> rowHas[9], colHas[9], blockHas[9];
    bool isValidSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    if (rowHas[i].count(board[i][j] - '0')) return false;
                    rowHas[i].insert(board[i][j] - '0');
                    if (colHas[j].count(board[i][j] - '0')) return false;
                    colHas[j].insert(board[i][j] - '0');
                    if (blockHas[i / 3 * 3 + j / 3]
                        .count(board[i][j] - '0')) return false;
                    blockHas[i / 3 * 3 + j / 3].insert(board[i][j] - '0');
                }
            }
        }
        return true;
    }
};