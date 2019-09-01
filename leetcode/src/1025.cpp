class Solution {
public:
    bool divisorGame(int N) {
        vector<int> canWin(N + 1, 0);
        for (int i = 2; i <= N; i++) {
            for (int j = 1; j < i; j++) {
                if (i % j == 0 && !canWin[i - j]) {
                    canWin[i] = 1;
                    break;
                }
            }
        }
        return canWin[N];
    }
};