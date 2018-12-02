class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int wordLen = word.length();
        if (wordLen == 0) return false;
        int m = board.size();
        if (m == 0) return false;
        int n = board[0].size();
        if (n == 0) return false;
        
        vector<vector<int> > visited(m, vector<int>(n, 0));
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (searchWord(i, j, visited, board, word)) return true;
            }
        }
        return false;
    }
    
    bool searchWord(int row, int col, vector<vector<int> > &visited,
                    vector<vector<char> > &board, string word) {
        int wordLen = word.length();
        if (wordLen == 1) {
            return board[row][col] == word[0];
        } else if (word[0] == board[row][col]) {
            int m = board.size(), n = board[0].size();
            visited[row][col] = 1;
            if (row - 1 >= 0 && !visited[row - 1][col]) {
                if (searchWord(row - 1, col, visited, board, word.substr(1))) return true;
            }
            if (row + 1 < m && !visited[row + 1][col]) {
                if (searchWord(row + 1, col, visited, board, word.substr(1))) return true;
            }
            if (col - 1 >= 0 && !visited[row][col - 1]) {
                if (searchWord(row, col - 1, visited, board, word.substr(1))) return true;
            }
            if (col + 1 < n && !visited[row][col + 1]) {
                if (searchWord(row, col + 1, visited, board, word.substr(1))) return true;
            }
            visited[row][col] = 0;
        }
        return false;
    }
};