class Solution {
public:
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        unordered_map<int, unordered_set<int>> AIdx, BIdx;
        int dLen = A.size();
        for (int i = 0; i < dLen; i++) {
            AIdx[A[i]].insert(i);
            BIdx[B[i]].insert(i);
        }
        int minResult = ~(1 << 31);
        // try six numbers
        for (int i = 1; i <= 6; i++) {
            // try A or B
            unordered_set<int> aIdx, bIdx;
            aIdx = AIdx[i], bIdx = BIdx[i];
            for (int j : bIdx) {
                aIdx.insert(j);
            }
            if (aIdx.size() == dLen) minResult = min(minResult, int(dLen - AIdx[i].size()));
            aIdx = AIdx[i], bIdx = BIdx[i];
            for (int j : aIdx) {
                bIdx.insert(j);
            }
            if (bIdx.size() == dLen) minResult = min(minResult, int(dLen - BIdx[i].size()));
        }
        if (minResult == ~(1 << 31)) return -1;
        return minResult;
    }
};