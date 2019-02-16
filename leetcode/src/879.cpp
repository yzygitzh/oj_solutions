class Solution {
public:
    long long ***F;
    
    int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
        F = new long long**[2];
        for (int i = 0; i < 2; i++) {
            F[i] = new long long*[110];
            for (int j = 0; j < 110; j++) {
                F[i][j] = new long long[110];
                for (int k = 0; k < 110; k++) {
                    F[i][j][k] = 0;
                }
            }
        }

        int gLen = group.size(), pLen = profit.size();
        for (int i = 0; i <= G; i++) {
            F[0][i][0] = 1;
        }
        for (int i = 1; i <= gLen; i++) {
            for (int j = 0; j <= G; j++) {
                for (int k = 0; k <= P; k++) {
                    F[i % 2][j][k] = F[(i - 1) % 2][j][k];
                    F[i % 2][j][k] %= 1000000007LL;
                    if (j - group[i - 1] >= 0) {
                        F[i % 2][j][k] += F[(i - 1) % 2][j - group[i - 1]]
                                           [max(0, k - profit[i - 1])];
                        F[i % 2][j][k] %= 1000000007LL;
                    }
                }
            }
        }
        return (int)F[gLen % 2][G][P];
    }
};