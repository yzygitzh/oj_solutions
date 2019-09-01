class Solution {
public:
    long long findSubtreeSize(long long node, long long limit) {
        long long result = 0, layerCnt = 1;
        while (node <= limit) {
            result += min(limit - node + 1, layerCnt);
            node *= 10;
            layerCnt *= 10;
        }
        return result;
    }
    
    int findKthNumber(int n, int k) {
        int result = 1;
        long long lK = k - 1;
        while (lK > 0) {
            long long subsize = findSubtreeSize(result, n);
            if (subsize > lK) {
                result *= 10;
                lK -= 1;
            } else {
                result += 1;
                lK -= subsize;
            }
        }
        return result;
    }
};