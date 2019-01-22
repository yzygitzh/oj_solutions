class Solution {
public:
    static bool envSort(const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first != b.first) return a.first < b.first;
        else return a.second > b.second;
    }
    
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        int envLen = envelopes.size();
        if (envLen == 0) return 0;
        
        sort(envelopes.begin(), envelopes.end(), envSort);
        
        vector<int> seqLenToEnd(envLen + 1, -1);
        seqLenToEnd[1] = envelopes[0].second;
        int maxLen = 1;
        
        for (int i = 1; i < envLen; i++) {
            int left = 1, right = maxLen;
            while (left + 1 < right) {
                int mid = (left + right) / 2;
                if (seqLenToEnd[mid] <= envelopes[i].second) {
                    left = mid;
                } else {
                    right = mid;
                }
            }
            if (seqLenToEnd[left] > envelopes[i].second) {
                seqLenToEnd[left] = envelopes[i].second;
            } else if (seqLenToEnd[right] > envelopes[i].second &&
                       envelopes[i].second > seqLenToEnd[left]) {
                seqLenToEnd[right] = envelopes[i].second;
            } else if (seqLenToEnd[maxLen] < envelopes[i].second &&
                       maxLen + 1 <= envLen) {
                maxLen++;
                seqLenToEnd[maxLen] = envelopes[i].second;
            }
        }
        return maxLen;
    }
};