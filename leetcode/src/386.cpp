class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> result(n, 0);
        int currNum = 1;
        for (int i = 0; i < n; i++) {
            // invariant: currNum is valid
            result[i] = currNum;
            if (currNum * 10 <= n) {
                // first try expand
                currNum *= 10;
            } else {
                // add last Digit
                if (currNum >= n) {
                    currNum /= 10;
                }
                currNum++;
                while (currNum % 10 == 0) currNum /= 10;
            }
        }
        return result;
    }
};