class Solution {
public:
    int findJudge(int N, vector<vector<int>>& trust) {
        unordered_set<int> candidates;
        unordered_map<int, unordered_set<int>> trustSet;
        for (int i = 1; i <= N; i++) {
            candidates.insert(i);
        }
        for (auto& vec : trust) {
            candidates.erase(vec[0]);
            trustSet[vec[1]].insert(vec[0]);
        }
        if (candidates.size() == 1 &&
            trustSet[*candidates.begin()].size() == N - 1) {
            return *candidates.begin();
        } else {
            return -1;
        }
    }
};