class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<vector<double> > flow(100, vector<double>(100, 0));
        
        // calculate flow
        flow[0][0] = poured;
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j <= i; j++) {
                if (j > 0 && flow[i - 1][j - 1] > 1.0) {
                    flow[i][j] += (flow[i - 1][j - 1] - 1.0) / 2;
                }
                if (j < i && flow[i - 1][j] > 1.0) {
                    flow[i][j] += (flow[i - 1][j] - 1.0) / 2;
                }
            }
        }
        if (flow[query_row][query_glass] >= 1.0) return 1.0;
        else return flow[query_row][query_glass];
    }
};