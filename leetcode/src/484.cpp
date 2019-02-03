class Solution {
public:
    vector<int> findPermutation(string s) {
        // find I+D+ groups, and greedily place them
        int sLen = s.length();
        int n = sLen + 1;
        vector<int> result;
        int idx = 0, currMax = 1;
        while (idx < sLen) {
            int oldIdx = idx;
            while (idx < sLen && s[idx] == 'I') idx++;
            int iLen = idx - oldIdx;
            while (idx < sLen && s[idx] == 'D') idx++;
            int dLen = idx - oldIdx - iLen;
            
            if (oldIdx == 0 && iLen > 0) result.push_back(1);
            
            // place I
            for (int i = 0; i + 1 < iLen; i++) {
                result.push_back(currMax + i + 1);
            }
            if (iLen > 0) {
                result.push_back(currMax + dLen + iLen);
            }
            // place D
            int iBase = iLen > 1 ? iLen - 1 : 0;
            for (int i = 0; i < dLen; i++) {
                result.push_back(currMax + iBase + dLen - i);
            }
            
            if (oldIdx == 0 && iLen == 0) result.push_back(1);
            
            currMax += iLen + dLen;
        }
        if (sLen == 0) result.push_back(1);
        return result;
    }
};