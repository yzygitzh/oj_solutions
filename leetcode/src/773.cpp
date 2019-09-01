class Solution {
public:
    unsigned boardToState(vector<vector<int>>& board) {
        unsigned state = 0;
        for (auto& row : board) {
            for (auto& num : row) {
                state *= 10;
                state += num;
            }
        }
        return state;
    }
    
    vector<unsigned> getNextStates(unsigned state) {
        vector<vector<int>> board(2, vector<int>(3));
        int zeroRow, zeroCol;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                board[1 - i][2 - j] = state % 10;
                if ((state % 10) == 0) {
                    zeroRow = 1 - i;
                    zeroCol = 2 - j;
                }
                state /= 10;
            }
        }
        vector<unsigned> result;
        
        swap(board[0][zeroCol], board[1][zeroCol]);
        result.push_back(boardToState(board));
        swap(board[0][zeroCol], board[1][zeroCol]);
        
        if (zeroCol - 1 >= 0) {
            swap(board[zeroRow][zeroCol], board[zeroRow][zeroCol - 1]);
            result.push_back(boardToState(board));
            swap(board[zeroRow][zeroCol], board[zeroRow][zeroCol - 1]);
        }
        
        if (zeroCol + 1 < 3) {
            swap(board[zeroRow][zeroCol], board[zeroRow][zeroCol + 1]);
            result.push_back(boardToState(board));
            swap(board[zeroRow][zeroCol], board[zeroRow][zeroCol + 1]);
        }
        return result;
    }
    
    int slidingPuzzle(vector<vector<int>>& board) {
        unordered_set<unsigned> visited;
        unsigned initState = boardToState(board);
        queue<pair<unsigned, int>> bfsQ;
        bfsQ.push(make_pair(initState, 0));
        visited.insert(initState);
        while (!bfsQ.empty()) {
            auto state = bfsQ.front();
            bfsQ.pop();
            if (state.first == 123450) {
                return state.second;
            }
            vector<unsigned> nextStates = getNextStates(state.first);
            for (auto nextState : nextStates) {
                if (visited.find(nextState) == visited.end()) {
                    visited.insert(nextState);
                    bfsQ.push(make_pair(nextState, state.second + 1));
                }
            }
        }
        return -1;
    }
};