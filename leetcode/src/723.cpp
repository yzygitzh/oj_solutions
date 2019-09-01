class Solution {
public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        int m = board.size(), n = board[0].size();
        bool changed = true;
        vector<vector<int>> deltas{vector<int>{-1, 0},
                                   vector<int>{0, -1},
                                   vector<int>{1, 0},
                                   vector<int>{0, 1}};
        while (changed) {
            changed = false;
            vector<vector<int>> visited(m, vector<int>(n, 0));
            for (int i = 0; i < m; i++) {
                int lastIdx = -1, currIdx = 0, lastCandy = -1;
                while (currIdx < n) {
                    if (board[i][currIdx] != lastCandy) {
                        if (currIdx - lastIdx >= 3 && lastCandy > 0) {
                            changed = true;
                            for (int j = lastIdx; j < currIdx; j++) {
                                visited[i][j] = 1;
                            }
                        }
                        lastIdx = currIdx;
                        lastCandy = board[i][currIdx];
                    }
                    currIdx++;
                }
                if (currIdx - lastIdx >= 3 && lastCandy > 0) {
                    changed = true;
                    for (int j = lastIdx; j < currIdx; j++) {
                        visited[i][j] = 1;
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                int lastIdx = -1, currIdx = 0, lastCandy = -1;
                while (currIdx < m) {
                    if (board[currIdx][i] != lastCandy) {
                        if (currIdx - lastIdx >= 3 && lastCandy > 0) {
                            changed = true;
                            for (int j = lastIdx; j < currIdx; j++) {
                                visited[j][i] = 1;
                            }
                        }
                        lastIdx = currIdx;
                        lastCandy = board[currIdx][i];
                    }
                    currIdx++;
                }
                if (currIdx - lastIdx >= 3 && lastCandy > 0) {
                    changed = true;
                    for (int j = lastIdx; j < currIdx; j++) {
                        visited[j][i] = 1;
                    }
                }
            }
            if (changed) {
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n; j++) {
                        if (visited[i][j]) {
                            board[i][j] = 0;
                        }
                    }
                }
                for (int i = 0; i < n; i++) {
                    int left = m - 1, right = m - 1;
                    while (right >= 0) {
                        if (board[right][i] != 0) {
                            board[left][i] = board[right][i];
                            left--;
                        }
                        right--;
                    }
                    while (left >= 0) {
                        board[left][i] = 0;
                        left--;
                    }
                }
            }
        }
        return board;
    }
};