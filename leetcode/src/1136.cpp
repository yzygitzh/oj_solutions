class Solution {
public:
    vector<int> inDegrees;
    vector<unordered_set<int>> adjList;
    
    int minimumSemesters(int N, vector<vector<int>>& relations) {
        adjList.resize(N + 1);
        inDegrees.resize(N + 1, 0);
        for (auto rel : relations) {
            adjList[rel[0]].insert(rel[1]);
            inDegrees[rel[1]]++;
        }
        queue<pair<int, int>> zeroQ; // <node_id, level>
        for (int i = 1; i <= N; i++) {
            if (inDegrees[i] == 0) {
                zeroQ.push(make_pair(i, 1));
            }
        }
        int courseStudied = 0;
        int maxLevel = 0;
        while (!zeroQ.empty()) {
            int currLevel = zeroQ.front().second;
            while (!zeroQ.empty() && currLevel == zeroQ.front().second) {
                int course = zeroQ.front().first;
                zeroQ.pop();
                courseStudied++;
                for (auto nextCourse: adjList[course]) {
                    inDegrees[nextCourse]--;
                    if (inDegrees[nextCourse] == 0) {
                        zeroQ.push(make_pair(nextCourse, currLevel + 1));
                    }
                }
            }
            maxLevel = max(maxLevel, currLevel);
        }
        return courseStudied == N ? maxLevel : -1;
    }
};