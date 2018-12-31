class Solution {
public:
    int maxWidthRamp(vector<int>& A) {
        int ALen = A.size();
        vector<int> prefixMin(ALen, 0); // bin search in this, mono down
        
        prefixMin[0] = A[0];
        for (int i = 1; i < ALen; i++) {
            if (A[i] < prefixMin[i - 1]) prefixMin[i] = A[i];
            else prefixMin[i] = prefixMin[i - 1];
        }
        
        int maxRamp = 0;
        for (int i = 1; i < ALen; i++) {
            int left = 0, right = i;
            while (left + 1 < right) {
                int mid = (left + right) / 2;
                if (prefixMin[mid] <= A[i]) right = mid;
                else left = mid;
            }
            if (prefixMin[left] <= A[i]) {
                if (i - left > maxRamp) maxRamp = i - left;
            } else if (prefixMin[right] <= A[i]) {
                if (i - right > maxRamp) maxRamp = i - right;
            }
        }
        
        return maxRamp;
    }
};