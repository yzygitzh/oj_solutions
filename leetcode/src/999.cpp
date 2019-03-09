class Solution {
public:
    int numRookCaptures(vector<vector<char>>& board) {
        // first find R
        int Rx, Ry;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j] == 'R') {
                    Rx = i, Ry = j;
                }
            }
        }
        // try four directions
        int pCnt = 0;
        for (int i = Rx - 1; i >= 0; i--) {
            if (board[i][Ry] == 'B') break;
            else if (board[i][Ry] == 'p') {
                pCnt++;
                break;
            }
        }
        for (int i = Rx + 1; i < 8; i++) {
            if (board[i][Ry] == 'B') break;
            else if (board[i][Ry] == 'p') {
                pCnt++;
                break;
            }
        }
        for (int i = Ry - 1; i >= 0; i--) {
            if (board[Rx][i] == 'B') break;
            else if (board[Rx][i] == 'p')  {
                pCnt++;
                break;
            }
        }
        for (int i = Ry + 1; i < 8; i++) {
            if (board[Rx][i] == 'B') break;
            else if (board[Rx][i] == 'p')  {
                pCnt++;
                break;
            }
        }
        return pCnt;
    }
};