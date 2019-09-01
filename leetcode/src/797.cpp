class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int N = graph.size();
        vector<vector<int>> result;
        queue<vector<int>> bfsQ;
        bfsQ.push(vector<int>{0});
        while (!bfsQ.empty()) {
            vector<int> path = bfsQ.front();
            bfsQ.pop();
            if (path.back() == N - 1) {
                result.push_back(path);
                continue;
            }
            for (auto node : graph[path.back()]) {
                bfsQ.push(path);
                bfsQ.back().push_back(node);
            }
        }
        return result;
    }
};