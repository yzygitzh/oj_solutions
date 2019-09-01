class Solution {
public:
    class WorkerBikePair {
    public:
        vector<int> worker, bike;
        int workerIdx, bikeIdx, dis;
        WorkerBikePair(vector<int>& worker_, vector<int>& bike_,
                       int workerIdx_, int bikeIdx_)
            : worker(worker_), bike(bike_),
              workerIdx(workerIdx_), bikeIdx(bikeIdx_) {
            dis = abs(worker[0] - bike[0]) + abs(worker[1] - bike[1]);
        }
        bool operator< (const WorkerBikePair& p) const {
            if (dis != p.dis) {
                return dis < p.dis;
            }
            if (workerIdx != p.workerIdx) {
                return workerIdx < p.workerIdx;
            }
            return bikeIdx < p.bikeIdx;
        }
    };
    
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        vector<WorkerBikePair> pairs;
        for (int i = 0; i < workers.size(); i++) {
            for (int j = 0; j < bikes.size(); j++) {
                pairs.push_back(WorkerBikePair(workers[i], bikes[j], i, j));
            }
        }
        sort(pairs.begin(), pairs.end());
        int filledCount = 0, idx = 0;
        vector<int> result(workers.size(), -1);
        vector<int> bikeVisited(bikes.size(), 0);
        while (filledCount < result.size() && idx < pairs.size()) {
            WorkerBikePair& p = pairs[idx];
            if (result[p.workerIdx] == -1 &&
                !bikeVisited[p.bikeIdx]) {
                result[p.workerIdx] = p.bikeIdx;
                bikeVisited[p.bikeIdx] = 1;
                filledCount++;
            }
            idx++;
        }
        return result;
    }
};