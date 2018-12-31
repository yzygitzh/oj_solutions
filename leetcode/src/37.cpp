class Solution {
public:
    unordered_set<int> rowHas[9], colHas[9], blockHas[9];
    bool found = false;
    vector<pair<int, int> > slots;

    void solveSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    rowHas[i].insert(board[i][j] - '0');
                    colHas[j].insert(board[i][j] - '0');
                    blockHas[i / 3 * 3 + j / 3].insert(board[i][j] - '0');
                } else {
                    slots.push_back(make_pair(i, j));
                }
            }
        }
        DFS(0, board);
    }
    
    void DFS(int slotIdx, vector<vector<char>>& board) {
        if (slotIdx == slots.size()) {
            found = true;
        } else {
            pair<int, int> slot = slots[slotIdx];
            for (int i = 1; i <= 9; i++) {
                if (!rowHas[slot.first].count(i) &&
                    !colHas[slot.second].count(i) &&
                    !blockHas[slot.first / 3 * 3 +
                              slot.second / 3].count(i)) {
                    rowHas[slot.first].insert(i);
                    colHas[slot.second].insert(i);
                    blockHas[slot.first / 3 * 3 +
                             slot.second / 3].insert(i);
                    board[slot.first][slot.second] = '0' + i;
                    DFS(slotIdx + 1, board);
                    rowHas[slot.first].erase(i);
                    colHas[slot.second].erase(i);
                    blockHas[slot.first / 3 * 3 +
                             slot.second / 3].erase(i);
                }
                if (found) break;
            }
        }
    }
};