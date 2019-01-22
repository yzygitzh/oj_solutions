class Solution {
public:
    vector<vector<int>> result;
    vector<int> partResult;

    vector<vector<int>> getFactors(int n) {
        vector<int> factors;
        int tmpN = n;
        for (int i = 2; tmpN > 1; i++) {
            if (!(tmpN % i)) {
                factors.push_back(i);
                while (!(tmpN % i)) tmpN /= i;
            }
        }
        int facLen = factors.size();
        if (facLen == 0 || facLen == 1 && factors[0] == n) return result;
        
        // generate humble numbers k that n mod k == 0
        vector<int> fullFacs{1};
        unordered_set<int> visited{1};
        int idx = 0, lastStartIdx = 0;
        while (idx < fullFacs.size()) {
            bool found = false;
            for (int i = lastStartIdx; i < facLen; i++) {
                int nextFullFac = factors[i] * fullFacs[idx];
                if (!visited.count(nextFullFac) && nextFullFac < n && !(n % nextFullFac)) {
                    found = true;
                    fullFacs.push_back(nextFullFac);
                    visited.insert(nextFullFac);
                    sort(fullFacs.begin(), fullFacs.end());
                    lastStartIdx = i + 1;
                    break;
                }
            }
            if (!found) {
                idx++;
                lastStartIdx = 0;
            }
        }
        // return vector<vector<int>>{fullFacs};
        dfs(n, fullFacs.size() - 1, fullFacs);
        return result;
    }
    
    void dfs(int n, int maxIdx, vector<int>& fullFacs) {
        if (n == 1) {
            result.push_back(partResult);
        } else {
            for (int i = maxIdx; i >= 1; i--) {
                if (!(n % fullFacs[i])) {
                    partResult.push_back(fullFacs[i]);
                    dfs(n / fullFacs[i], i, fullFacs);
                    partResult.pop_back();
                }
            }
        }
    }
};