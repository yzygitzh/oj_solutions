class Solution {
public:
    class CustomCmp {
    public:
        bool operator() (const pair<int, int> &i, const pair<int, int> &j) const {
            if (i.first == j.first)
                return i.second < j.second;
            return i.first < j.first;
        }
    };
    
    int maxEnvelopes(vector<pair<int, int>>& _envelopes) {
        // build graph than do dfs with memo
        // k-d tree ?

        int _envelopesLen = _envelopes.size();
        if (_envelopesLen == 0) return 0;
        
        set<pair<int, int>> uniqEnvelopes(_envelopes.begin(), _envelopes.end());
        vector<pair<int, int>> envelopes(uniqEnvelopes.begin(), uniqEnvelopes.end());
        int envelopesLen = envelopes.size();
        sort(envelopes.begin(), envelopes.end(), CustomCmp());

        int maxLen = 1;
        vector<int> maxLenArray(envelopesLen, 1);
        for (int i = 0; i < envelopesLen; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (envelopes[i].first > envelopes[j].first &&
                    envelopes[i].second > envelopes[j].second) {
                    if (maxLenArray[i] < maxLenArray[j] + 1) {
                        maxLenArray[i] = maxLenArray[j] + 1;
                        if (maxLen < maxLenArray[i]) {
                            maxLen = maxLenArray[i];
                        }
                    }
                }
            }
        }

        return maxLen;
    }
};