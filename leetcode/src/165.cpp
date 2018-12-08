class Solution {
public:
    int compareVersion(string version1, string version2) {
        vector<int> v1Nums, v2Nums;
        int v1Len = version1.length(), v2Len = version2.length();
        
        for (int i = 0; i < v1Len; i++) {
            if (version1[i] != '.') {
                int vNum = 0;
                while (i < v1Len && version1[i] != '.') {
                    vNum *= 10;
                    vNum += version1[i] - '0';
                    i++;
                }
                v1Nums.push_back(vNum);
            }
        }
        
        for (int i = 0; i < v2Len; i++) {
            if (version2[i] != '.') {
                int vNum = 0;
                while (i < v2Len && version2[i] != '.') {
                    vNum *= 10;
                    vNum += version2[i] - '0';
                    i++;
                }
                v2Nums.push_back(vNum);
            }
        }
        
        int v1VerLen = v1Nums.size(), v2VerLen = v2Nums.size();
        int maxVerLen = v1VerLen > v2VerLen ? v1VerLen : v2VerLen;
        while (v1Nums.size() < maxVerLen) v1Nums.push_back(0);
        while (v2Nums.size() < maxVerLen) v2Nums.push_back(0);
        
        for (int i = 0; i < maxVerLen; i++) {
            if (v1Nums[i] < v2Nums[i]) return -1;
            else if (v1Nums[i] > v2Nums[i]) return 1;
        }
        return 0;
    }
};