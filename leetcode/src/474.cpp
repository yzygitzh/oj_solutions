class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        // 2-dim 0-1 knapsack.
        int strsLen = strs.size();
        if (strsLen == 0) return 0;
        
        vector<pair<int, int>> strWeights(strsLen);
        for (int i = 0; i < strsLen; i++) {
            map<int, int> charCnt;
            for (auto itr = strs[i].begin(); itr != strs[i].end(); ++itr) {
                charCnt[*itr]++;
            }
            strWeights[i].first = charCnt['0'];
            strWeights[i].second = charCnt['1'];
        }
        
        // F[M][N1][N2]: max strings chosen with N1 and N2 volume and first M strs
        // F[M][N1][N2] = max(F[M-1][N1][N2], 1 + F[M-1][N1-weight1(M)][N2-weight2(M)])
        int ***F = new int**[2];
        for (int i = 0; i < 2; i++) {
            F[i] = new int*[m + 1];
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j <= m; j++) {
                F[i][j] = new int[n + 1];
                for (int k = 0; k <= n; k++) F[i][j][k] = 0;
            }
        }
        
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (strWeights[0].first <= i && strWeights[0].second <= j) {
                    F[0][i][j] = 1;
                }
            }
        }
        
        for (int i = 1; i < strWeights.size(); i++) {
            for (int j = 0; j <= m; j++) {
                for (int k = 0; k <= n; k++) {
                    int skipNum = F[(i - 1) % 2][j][k];
                    int useNum = 0;
                    if (strWeights[i].first <= j && strWeights[i].second <= k) {
                        useNum = F[(i - 1) % 2]
                                  [j - strWeights[i].first]
                                  [k - strWeights[i].second] + 1;
                    }
                    F[i % 2][j][k] = skipNum > useNum ? skipNum : useNum;
                }
            }
        }

        return F[(strWeights.size() - 1) % 2][m][n];
    }
    
};