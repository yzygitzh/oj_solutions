class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) return 1;
        vector<long long> selectN(11);
        vector<long long> selectNNonZero(11);
        vector<long long> answer(11);
        
        selectN[1] = 10;
        selectNNonZero[1] = 9;
        answer[1] = 10;

        for (int i = 2; i <= n; i++) {
            selectN[i] = selectN[i - 1] * (10 - i + 1);
            selectNNonZero[i] = selectNNonZero[i - 1] * (9 - i + 1);
            answer[i] = selectN[i] - selectNNonZero[i - 1];
        }
        
        int result = 0;
        for (int i = 1; i <= n; i++) {
            result += answer[i];
        }
        return result;
    }
};