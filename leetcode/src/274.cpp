class Solution {
public:
    int hIndex(vector<int>& citations) {
        int citationNum = citations.size();
        if (citationNum == 0) return 0;
        sort(citations.begin(), citations.end(), greater<int>());
        if (citations[0] == 0) return 0;
        
        int cIdx = 0;
        while (cIdx < citationNum) {
            if (cIdx + 1 > citations[cIdx]) {
                break;
            } else {
                cIdx++;
            }
        }
        return cIdx;
    }
};