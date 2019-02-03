class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> sumToCntAB, sumToCntCD;
        for (auto itr = A.begin(); itr != A.end(); ++itr) {
            for (auto itr2 = B.begin(); itr2 != B.end(); ++itr2) {
                sumToCntAB[(*itr) + (*itr2)]++;
            }
        }
        for (auto itr = C.begin(); itr != C.end(); ++itr) {
            for (auto itr2 = D.begin(); itr2 != D.end(); ++itr2) {
                sumToCntCD[(*itr) + (*itr2)]++;
            }
        }
        int result = 0;
        for (auto itr = sumToCntAB.begin(); itr != sumToCntAB.end(); ++itr) {
            if (sumToCntCD.count(-itr->first)) {
                result += itr->second * sumToCntCD[-itr->first];
            }
        }
        return result;
    }
};