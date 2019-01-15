class TicTacToe {
public:
    int n;
    vector<int> playerRow[2], playerCol[2];
    int playerCrossCnt1[2] = {0}, playerCrossCnt2[2] = {0};
    
    /** Initialize your data structure here. */
    TicTacToe(int _n) {
        n = _n;
        playerRow[0] = playerRow[1] = playerCol[0] = playerCol[1] = vector<int>(n, 0);
    }
    
    /** Player {player} makes a move at ({row}, {col}).
        @param row The row of the board.
        @param col The column of the board.
        @param player The player, can be either 1 or 2.
        @return The current winning condition, can be either:
                0: No one wins.
                1: Player 1 wins.
                2: Player 2 wins. */
    int move(int row, int col, int player) {
        playerRow[player - 1][row]++;
        playerCol[player - 1][col]++;
        if (playerRow[player - 1][row] == n ||
            playerCol[player - 1][col] == n) return player;
        // check the cross
        if (row == col) playerCrossCnt1[player - 1]++;
        if (row + col == n - 1) playerCrossCnt2[player - 1]++;
        if (playerCrossCnt1[player - 1] == n ||
            playerCrossCnt2[player - 1] == n) return player;
        return 0;
    }
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe obj = new TicTacToe(n);
 * int param_1 = obj.move(row,col,player);
 */