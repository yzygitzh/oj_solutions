class Solution {
public:
    int minKBitFlips(vector<int>& A, int K) {
        // make use of input array to record whether it's flipped
        int totalFlip = 0, flipInK = 0;
        for (int i = 0 ; i < A.size(); i++) {
            if (i >= K && A[i - K] >= 2) {
                A[i - K] -= 2;
                flipInK--;
            }
            if (A[i] == (flipInK & 1)) {
                if (i + K > A.size()) {
                    return -1;
                }
                totalFlip++;
                flipInK++;
                A[i] += 2;
            }
        }
        return totalFlip;
    }
};