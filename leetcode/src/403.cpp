class Solution {
public:
    bool canCross(vector<int>& stones) {
        int stonesNum = stones.size();
        unordered_map<int, int> disToIdx;
        for (int i = 0; i < stonesNum; i++) {
            disToIdx[stones[i]] = i;
        }
        vector<unordered_set<int>> steps(stonesNum);
        // first jump
        if (disToIdx.count(1)) {
            steps[disToIdx[1]].insert(1);
        }
        for (int i = 1; i + 1 < stonesNum; i++) {
            for (auto itr = steps[i].begin();
                 itr != steps[i].end(); ++itr) {
                for (int k = max((*itr) - 1, 1); k <= (*itr) + 1; k++) {
                    if (disToIdx.count(stones[i] + k)) {
                        steps[disToIdx[stones[i] + k]].insert(k);
                    }
                }
            }
        }
        return steps[stonesNum - 1].size() > 0;
    }
};