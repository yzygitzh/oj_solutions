class Solution {
public:
    vector<vector<int>> rects;
    map<int, int> areaToIdx;
    int totalArea = 0;
    
    Solution(vector<vector<int>> _rects) {
        rects = _rects;
        int rectsNum = rects.size();
        for (int i = 0; i < rectsNum; i++) {
            totalArea += (rects[i][2] - rects[i][0] + 1) *
                    (rects[i][3] - rects[i][1] + 1);
            areaToIdx[totalArea] = i;
        }
    }
    
    vector<int> pick() {
        int randArea = (int)(((double)rand() / (RAND_MAX + 1u)) * totalArea);
        auto itr = areaToIdx.upper_bound(randArea);
        vector<int> rect = rects[itr->second];
        int x = rect[0] + (int)((double)rand() / (RAND_MAX + 1u) *
                                (rect[2] - rect[0] + 1));
        int y = rect[1] + (int)((double)rand() / (RAND_MAX + 1u) *
                                (rect[3] - rect[1] + 1));
        return vector<int>{x, y};
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(rects);
 * vector<int> param_1 = obj.pick();
 */