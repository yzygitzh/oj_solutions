class Solution {
public:
    vector<int> idxToSquare(int idx, int n) {
        vector<int> square(2);
        square[0] = n - 1 - idx / n;
        square[1] = ((idx / n) % 2) == 0 ? (idx % n) : n - 1 - (idx % n);
        return square;
    }
    
    vector<vector<int>> getNextSquares(vector<int> square, int n,
                                       vector<vector<int>>& board) {
        vector<vector<int>> result;
        while (result.size() < 6 &&
               idxToSquare(n * n - 1, n) != square) {
            if (((n - 1 - square[0]) % 2) == 0) {
                if ((square[1] % n) == n - 1) {
                    square[0] -= 1;
                } else {
                    square[1] += 1;
                }
            } else {
                if ((square[1] % n) == 0) {
                    square[0] -= 1;
                } else {
                    square[1] -= 1;
                }
            }
            if (board[square[0]][square[1]] != -1) {
                result.push_back(idxToSquare(board[square[0]][square[1]] - 1, n));
            } else {
                result.push_back(square);
            }
        }
        return result;
    }
    
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        vector<vector<int>> visited(n, vector<int>(n, 0));
        queue<pair<vector<int>, int>> bfsQ;
        bfsQ.push(make_pair(vector<int>{n - 1, 0}, 0));
        visited[n - 1][0] = 1;
        while (!bfsQ.empty()) {
            auto state = bfsQ.front();
            bfsQ.pop();
            if (idxToSquare(n * n - 1, n) == state.first) {
                return state.second;
            }
            auto nextSquares = getNextSquares(state.first, n, board);
            for (auto square : nextSquares) {
                if (!visited[square[0]][square[1]]) {
                    bfsQ.push(make_pair(square, state.second + 1));
                    visited[square[0]][square[1]] = 1;
                }
            }
        }
        return -1;
    }
};