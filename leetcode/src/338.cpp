class Solution {
public:
    vector<int> countBits(int num) {
        // get high bit and substract it from num
        // find which 2^n segment it's in
        
        vector<int> thresholds; // thresholds[i] == 2^i
        for (int i = 0; i <= 30; i++) {
            thresholds.push_back(1 << i);
        }
        
        vector<int> bitSum(num + 1, 0);
        bitSum[0] = 0;
        if (num == 0) return bitSum;
        bitSum[1] = 1;
        if (num == 1) return bitSum;
        
        int thIdx = 0;
        for (int i = 2; i <= num; i++) {
            if (i == thresholds[thIdx + 1]) {
                thIdx++;
            }
            bitSum[i] = 1 + bitSum[i - thresholds[thIdx]];
        }
        
        return bitSum;
    }
};