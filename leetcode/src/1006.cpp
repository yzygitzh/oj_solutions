class Solution {
public:
    int clumsy(int N) {
        long long lN = N;
        vector<long long> numStack;
        int currOp = 0;
        while (lN > 0) {
            if (currOp == 0) {
                if (lN >= 3) {
                    numStack.push_back(lN * (lN - 1) / (lN - 2));
                    lN -= 3;
                } else if (lN == 2) {
                    numStack.push_back(lN * (lN - 1));
                    lN -= 2;
                } else if (lN == 1) {
                    numStack.push_back(lN);
                    lN--; 
                }
            } else {
                numStack.push_back(lN);
                lN--;
            }
            currOp = 1 - currOp;
        }
        long long result = 0;
        for (int i = 0; i < numStack.size(); i++) {
            if (i == 0 || i % 2) {
                result += numStack[i];
            } else {
                result -= numStack[i];
            }
        }
        return int(result);
    }
};