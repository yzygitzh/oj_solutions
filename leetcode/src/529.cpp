class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        if (board[click[0]][click[1]] == 'M') {
            board[click[0]][click[1]] = 'X';
            return board;
        }
        queue<pair<int, int>> bfsQ;
        bfsQ.push(make_pair(click[0], click[1]));
        while (!bfsQ.empty()) {
            auto pos = bfsQ.front();
            bfsQ.pop();
            int mineCnt = 0;
            queue<pair<int, int>> tempQ;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0 ||
                        pos.first + i < 0 || pos.first + i >= board.size() ||
                        pos.second + j < 0 || pos.second + j >= board[0].size()) {
                        continue;
                    }
                    if (board[pos.first + i][pos.second + j] == 'E') {
                        tempQ.push(make_pair(pos.first + i, pos.second + j));
                    } else if (board[pos.first + i][pos.second + j] == 'M') {
                        mineCnt++;
                    }
                }
            }
            if (mineCnt == 0) {
                while (!tempQ.empty()) {
                    bfsQ.push(tempQ.front());
                    board[tempQ.front().first][tempQ.front().second] = 'e';
                    tempQ.pop();
                }
                board[pos.first][pos.second] = 'B';
            } else {
                board[pos.first][pos.second] = '0' + mineCnt;
            }
        }
        return board;
    }
};