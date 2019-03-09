class Solution {
public:
    int minKBitFlips(vector<int>& A, int K) {
        // flip * flip == 0, so do flip at most once.
        int ALen = A.size(), flipStatus = 0, flipCnt = 0;
        queue<int> flipEnd;
        for (int i = 0; i < ALen; i++) {
            if (flipEnd.size() > 0 && flipEnd.front() == i) {
                flipStatus = 1 - flipStatus;
                flipEnd.pop();
            }
            if (i + K <= ALen && A[i] == flipStatus) {
                // do flip
                flipCnt++;
                flipEnd.push(i + K);
                flipStatus = 1 - flipStatus;
            }
            if (A[i] == flipStatus) return -1;
        }
        return flipCnt;
    }
};