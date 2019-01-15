class Solution {
public:
    void connectNodes(int a, int b, vector<vector<int>>& adjList) {
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }
    
    int numberOfPatterns(int m, int n) {
        // calculate corner, edge for 1 to 9 is sufficient
        // nodes from 0 to 8
        vector<int> cornerCases(10, 0), edgeCases(10, 0), centerCases(10, 0);
        vector<int> cornerCasesWithoutCenter(10, 0), edgeCasesWithoutCenter(10, 0);
        vector<vector<int>> adjList(9);
        vector<int> visited(9, 0);

        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (i < j) connectNodes(i, j, adjList);
            }
        }
        // calculate "corner cases"
        dfs(0, 1, adjList, cornerCases, visited);
        // calculate "edgeg cases"
        dfs(1, 1, adjList, edgeCases, visited);
        
        // caculate cases without center
        visited[4] = 1;
        dfs(0, 1, adjList, cornerCasesWithoutCenter, visited);
        dfs(1, 1, adjList, edgeCasesWithoutCenter, visited);
        
        // calculate "center cases", note that center point is already visited
        centerCases[1] = 1;
        for (int i = 2; i <= 9; i++) {
            centerCases[i] = cornerCasesWithoutCenter[i - 1] * 4 +
                             edgeCasesWithoutCenter[i - 1] * 4;
        }
        int result = 0;
        for (int i = m; i <= n; i++) {
            result += centerCases[i] + edgeCases[i] * 4 + cornerCases[i] * 4;
        }
        return result;
    }

    void dfs(int node, int len, vector<vector<int>>& adjList,
             vector<int>& cases, vector<int>& visited) {
        visited[node] = 1;
        cases[len]++;
        for (auto itr = adjList[node].begin(); itr != adjList[node].end(); ++itr) {
            if (!visited[*itr]) {
                // check passing nodes
                if (node + (*itr) == 8 && !visited[4] ||
                    (!visited[1] && (node == 0 && (*itr) == 2 || node == 2 && (*itr) == 0)) ||
                    (!visited[3] && (node == 0 && (*itr) == 6 || node == 6 && (*itr) == 0)) ||
                    (!visited[5] && (node == 2 && (*itr) == 8 || node == 8 && (*itr) == 2)) ||
                    (!visited[7] && (node == 6 && (*itr) == 8 || node == 8 && (*itr) == 6))) {
                    continue;
                }
                dfs(*itr, len + 1, adjList, cases, visited);
            }
        }
        visited[node] = 0;
    }
};