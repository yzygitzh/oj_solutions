class Solution {
public:
    bool validTicTacToe(vector<string>& board) {
        int crossCnt = 0, circleCnt = 0;
        int rowCrossCnt[3] = {0}, colCrossCnt[3] = {0};
        int rowCircleCnt[3] = {0}, colCircleCnt[3] = {0};
        int xCrossCnt[2] = {0}, xCircleCnt[2] = {0};
        
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.size(); j++) {
                if (board[i][j] == 'X') {
                    crossCnt++;
                    rowCrossCnt[i]++;
                    colCrossCnt[j]++;
                    if (i == j) {
                        xCrossCnt[0]++;
                    }
                    if (i + j == board.size() - 1) {
                        xCrossCnt[1]++;
                    }
                } else if (board[i][j] == 'O') {
                    circleCnt++;
                    rowCircleCnt[i]++;
                    colCircleCnt[j]++;
                    if (i == j) {
                        xCircleCnt[0]++;
                    }
                    if (i + j == board.size() - 1) {
                        xCircleCnt[1]++;
                    }
                }
            }
        }
        
        int maxCross = 0;
        for (int i = 0; i < 3; i++) {
            maxCross = max(maxCross, rowCrossCnt[i]);
            maxCross = max(maxCross, colCrossCnt[i]);
        }
        maxCross = max(maxCross, max(xCrossCnt[0], xCrossCnt[1]));
        int maxCircle = 0;
        for (int i = 0; i < 3; i++) {
            maxCircle = max(maxCircle, rowCircleCnt[i]);
            maxCircle = max(maxCircle, colCircleCnt[i]);
        }
        maxCircle = max(maxCircle, max(xCircleCnt[0], xCircleCnt[1]));
        
        if (maxCross == 3 && maxCircle == 3) {
            return false;
        }
        
        if (!(circleCnt == crossCnt || circleCnt + 1 == crossCnt)) {
            return false;
        }
        
        if (maxCross == 3 && circleCnt == crossCnt ||
            maxCircle == 3 && circleCnt + 1 == crossCnt) {
            return false;
        }
        
        return true;
    }
};