class Solution {
public:
    class BfsState {
    public:
        int city, dis, cost;
        BfsState(int city_, int dis_, int cost_): city(city_), dis(dis_), cost(cost_) {}
        bool operator< (const BfsState& s) const {
            if (dis != s.dis) return dis > s.dis;
            return cost > s.cost;
        }
    };
    
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        // heap-based bfs
        unordered_map<int, unordered_map<int, int>> adjList;
        for (auto& flight : flights) {
            adjList[flight[0]][flight[1]] = flight[2];
        }
        priority_queue<BfsState> bfsQ;
        bfsQ.push(BfsState(src, 0, 0));
        vector<vector<int>> minCost(n, vector<int>(K + 2, 0x3FFFFFFF));
        minCost[src][0] = 0;
        while (!bfsQ.empty()) {
            BfsState state = bfsQ.top();
            bfsQ.pop();
            if (state.dis == K + 1) {
                break;
            }
            for (auto& p : adjList[state.city]) {
                int newCost = state.cost + p.second;
                if (newCost < minCost[p.first][state.dis + 1]) {
                    minCost[p.first][state.dis + 1] = newCost;
                    bfsQ.push(BfsState(p.first, state.dis + 1, newCost));
                }
            }
        }
        int result = 0x3FFFFFFF;
        for (int i = 0; i < K + 2; i++) {
            result = min(result, minCost[dst][i]);
        }
        return result < 0x3FFFFFFF ? result : -1;
    }
};