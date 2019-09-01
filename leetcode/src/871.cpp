class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        priority_queue<vector<int>> reachedStations;
        stations.push_back(vector<int>{target, 0});
        int currFuel = startFuel, addCnt = 0, currDis = 0;
        for (int i = 0; i < stations.size(); i++) {
            int currCost = stations[i][0] - currDis;
            while (currCost > currFuel && reachedStations.size() > 0) {
                currFuel += reachedStations.top()[0];
                reachedStations.pop();
                addCnt++;
            }
            if (currFuel < currCost) {
                return -1;
            }
            currFuel -= currCost;
            currDis = stations[i][0];
            reachedStations.push(vector<int>{stations[i][1], stations[i][0]});
        }
        return addCnt;
    }
};