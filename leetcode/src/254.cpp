class Solution {
public:
    vector<int> factors;
    vector<int> partResult;
    vector<vector<int>> result;
    
    vector<vector<int>> getFactors(int n) {
        long long lN = (long long)n;
        for (long long i = 2; i < lN; i++) {
            if (!(lN % i)) {
                factors.push_back((int)i);
            }
        }
        if (factors.empty()) return result;
        dfs(n, *factors.rbegin());
        return result;
    }
    
    void dfs(int n, int largest) {
        if (n == 1) {
            result.push_back(partResult);
        } else {
            for (auto itr = factors.rbegin(); itr != factors.rend(); ++itr) {
                if (*itr <= largest && !(n % (*itr))) {
                    partResult.push_back(*itr);
                    dfs(n / (*itr), *itr);
                    partResult.pop_back();
                }
            }
        }
    }
};