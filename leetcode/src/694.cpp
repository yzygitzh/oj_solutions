class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        set<vector<pair<int, int>>> islands;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    vector<pair<int, int>> islandId;
                    queue<vector<int>> bfsQ;
                    bfsQ.push(vector<int>{i, j});
                    grid[i][j] = -1;
                    while (!bfsQ.empty()) {
                        vector<int> state = bfsQ.front();
                        bfsQ.pop();
                        islandId.push_back(make_pair(state[0], state[1]));
                        if (state[0] - 1 >= 0 && grid[state[0] - 1][state[1]] == 1) {
                            grid[state[0] - 1][state[1]] = -1;
                            bfsQ.push(vector<int>{state[0] - 1, state[1]});
                        }
                        if (state[1] - 1 >= 0 && grid[state[0]][state[1] - 1] == 1) {
                            bfsQ.push(vector<int>{state[0], state[1] - 1});
                            grid[state[0]][state[1] - 1] = -1;
                        }
                        if (state[0] + 1 < grid.size() && grid[state[0] + 1][state[1]] == 1) {
                            bfsQ.push(vector<int>{state[0] + 1, state[1]});
                            grid[state[0] + 1][state[1]] = -1;
                        }
                        if (state[1] + 1 < grid[0].size() && grid[state[0]][state[1] + 1] == 1) {
                            bfsQ.push(vector<int>{state[0], state[1] + 1});
                            grid[state[0]][state[1] + 1] = -1;
                        }
                    }
                    sort(islandId.begin(), islandId.end());
                    for (int i = islandId.size() - 1; i >= 0; i--) {
                        islandId[i].first -= islandId[0].first;
                        islandId[i].second -= islandId[0].second;
                    }
                    islands.insert(islandId);
                }
            }
        }
        return islands.size();
    }
};