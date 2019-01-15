class Solution {
public:
    class OddElem {
    public:
        int val, idx;
        OddElem(int _val, int _idx): val(_val), idx(_idx) {}
        bool operator< (const OddElem& a) const {
            if (val != a.val) return val < a.val;
            return idx < a.idx;
        }
    };
    
    class EvenElem {
    public:
        int val, idx;
        EvenElem(int _val, int _idx): val(_val), idx(_idx) {}
        bool operator< (const EvenElem& a) const {
            if (val != a.val) return val > a.val;
            return idx < a.idx;
        }
    };
    
    int oddEvenJumps(vector<int>& A) {
        set<OddElem> oddSet;
        set<EvenElem> evenSet;
        int ALen = A.size();
        vector<int> oddReachable(ALen, 0);
        vector<int> evenReachable(ALen, 0);
        oddReachable[ALen - 1] = evenReachable[ALen - 1] = 1;
        for (int i = ALen - 2; i >= 0; i--) {
            oddSet.insert(OddElem(A[i + 1], i + 1));
            evenSet.insert(EvenElem(A[i + 1], i + 1));
            
            // odd jump
            auto itrOdd = oddSet.lower_bound(OddElem(A[i], i));
            if (itrOdd != oddSet.end()) oddReachable[i] = evenReachable[itrOdd->idx];
            
            // even jump
            auto itrEven = evenSet.lower_bound(EvenElem(A[i], i));
            if (itrEven != evenSet.end()) evenReachable[i] = oddReachable[itrEven->idx];
        }
        int result = 0;
        for (int i = 0; i < ALen; i++) {
            result += oddReachable[i];
        }
        return result;
    }
};