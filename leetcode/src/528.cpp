class Solution {
public:
    map<int, int> prefixProbToIdx;
    int prefixProb;
    
    Solution(vector<int>& w) {
        prefixProb = 0;
        for (int i = 0; i < w.size(); i++) {
            prefixProb += w[i];
            prefixProbToIdx[prefixProb] = i;
        }
    }

    // 0: 1, 2, 3
    // 1: 4
    // {3:0, 4:1}
    // lower_bound
    int pickIndex() {
        // [1, prefixProb]
        int randIdx = int(double(rand()) / (RAND_MAX + 1U) * prefixProb) + 1;
        return prefixProbToIdx.lower_bound(randIdx)->second;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */