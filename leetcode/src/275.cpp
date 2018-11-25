class Solution {
public:
    int hIndex(vector<int>& citations) {
        int citeNum = citations.size();
        if (citeNum == 0) return 0;
        if (citeNum == 1) return citations[0] == 0 ? 0 : 1;
        
        // bin search for (right side) of h.
        int left = 0, right = citeNum - 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if (citations[mid] <= citeNum - mid) {
                left = mid;
            } else {
                right = mid;
            }
        }
        
        if (citations[left] >= citeNum - left) return citeNum - left;
        if (citations[right] >= citeNum - right) return citeNum - right;
        return citations[right];
    }
};