class Solution {
public:
    class BfsState {
    public:
        int node, dis;
        BfsState(int node_, int dis_): node(node_), dis(dis_) {}
        bool operator< (const BfsState& s) const {
            return dis > s.dis;
        }
    };

    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        unordered_map<int, unordered_map<int, int>> adjList;
        for (auto& time : times) {
            adjList[time[0]][time[1]] = time[2];
        }
        priority_queue<BfsState> pq;
        vector<int> visited(N + 1, 0);
        pq.push(BfsState(K, 0));
        int visitedCnt = 0;
        while (!pq.empty()) {
            BfsState state = pq.top();
            pq.pop();
            if (visited[state.node]) {
                continue;
            }
            visited[state.node] = 1;
            visitedCnt++;
            if (visitedCnt == N) {
                return state.dis;
            }
            for (auto& p : adjList[state.node]) {
                pq.push(BfsState(p.first, state.dis + p.second));
            }
        }
        return -1;
    }
};