class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        int ALen = A.size();
        if (ALen == 0) return 0;
        sort(A.begin(), A.end());
        
        int repeatNum = 0;
        vector<int> repeatSet;
        vector<int> emptySlots;
        
        for (int i = 1; i < ALen; i++) {
            if (A[i] == A[i - 1]) {
                repeatSet.push_back(A[i]);
                repeatNum++;
            } else {
                if (repeatNum > 0) {
                    for (int j = A[i - 1] + 1; j < A[i] && repeatNum > 0; j++) {
                        emptySlots.push_back(j);
                        repeatNum--;
                    }
                }
            }
        }
        
        // if emptySlots is not enough, add them
        int emptyIdx = A[ALen - 1] + 1;
        repeatNum = repeatSet.size();
        int emptySlotsSize = emptySlots.size();
        for (int i = 0; i < repeatNum - emptySlotsSize; i++) {
            emptySlots.push_back(emptyIdx++);
        }
        
        // calc sum
        int sum = 0;
        vector<int>::iterator itr1 = repeatSet.begin();
        vector<int>::iterator itr2 = emptySlots.begin();
        while (itr1 != repeatSet.end()) {
            sum += (*itr2) - (*itr1);
            ++itr1;
            ++itr2;
        }
        return sum;
    }
};