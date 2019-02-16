class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        // F[m][n]: maximum gas rest after m stations and n times refueling
        // -1 means not reachable
        int stationNum = stations.size();
        vector<vector<long long>> F(2, vector<long long>(stationNum + 1, 0));
        for (int i = 0; i <= stationNum; i++) {
            F[0][i] = (long long)startFuel;
        }
        for (int i = 1; i <= stationNum; i++) {
            long long dis = i > 1 ? stations[i - 1][0] - stations[i - 2][0] :
                                    stations[i - 1][0];
            long long fuel = stations[i - 1][1];
            F[i % 2][0] = max(-1LL, F[(i - 1) % 2][0] - dis);
            for (int j = 1; j <= stationNum; j++) {
                int nonRefuel = max(-1LL, F[(i - 1) % 2][j] - dis);
                int refuel = F[(i - 1) % 2][j - 1] - dis >= 0 ?
                             F[(i - 1) % 2][j - 1] - dis + fuel : -1;
                F[i % 2][j] = max(nonRefuel, refuel);
            }
        }
        long long finalDis = stationNum > 0 ? target - stations[stationNum - 1][0] : target;
        for (int i = 0; i <= stationNum; i++) {
            if (finalDis <= F[stationNum % 2][i]) return i;
        }
        return -1;
    }
};