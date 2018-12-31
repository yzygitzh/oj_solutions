class Solution {
public:
    int repeatedNTimes(vector<int>& A) {
        int ALen = A.size();
        map<int, int> ACount;
        for (int i = 0; i < ALen; i++) {
            if (ACount.find(A[i]) == ACount.end() &&
                ACount.size() == 2) {
                ACount.begin()->second--;
                if (ACount.begin()->second == 0) ACount.erase(ACount.begin()->first);
                ACount.rbegin()->second--;
                if (ACount.rbegin()->second == 0) ACount.erase(ACount.rbegin()->first);
            }
            ACount[A[i]]++;
        }
        int testNum, testCount;
        testNum = ACount.begin()->first;
        testCount = 0;
        for (int i = 0; i < ALen; i++) {
            if (A[i] == testNum) testCount++;
            if (testCount > 1) return testNum;
        }
        return ACount.rbegin()->first;
    }
};