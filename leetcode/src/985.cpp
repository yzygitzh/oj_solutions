class Solution {
public:
    bool isEven(int x) {
        return !(((long long)x + 200000000LL) % 2);
    }
    
    vector<int> sumEvenAfterQueries(vector<int>& A, vector<vector<int>>& queries) {
        vector<int> result;
        int ASum = 0;
        for (auto itr = A.begin(); itr != A.end(); ++itr) {
            if (isEven(*itr)) ASum += *itr;
        }
        for (auto itr = queries.begin(); itr != queries.end(); ++itr) {
            if (isEven(A[(*itr)[1]])) ASum -= A[(*itr)[1]];
            A[(*itr)[1]] += (*itr)[0];
            if (isEven(A[(*itr)[1]])) ASum += A[(*itr)[1]];
            result.push_back(ASum);
        }
        return result;
    }
};