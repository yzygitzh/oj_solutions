class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
        vector<int> result;
        for (auto itr = A.begin(); itr != A.end(); ++itr) {
            result.push_back((*itr) * (*itr));
        }
        sort(result.begin(), result.end());
        return result;
    }
};