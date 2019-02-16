class Solution {
public:
    vector<int> addToArrayForm(vector<int>& A, int KInt) {
        if (KInt == 0) return vector<int>(A.begin(), A.end());
        
        reverse(A.begin(), A.end());
        vector<int> K;
        while (KInt) {
            K.push_back(KInt % 10);
            KInt /= 10;
        }
        
        vector<int> result;
        int ALen = A.size(), KLen = K.size();
        int idxA = 0, idxK = 0;
        int carry = 0;
        while (idxA < ALen || idxK < KLen) {
            int sum = carry;
            if (idxA < ALen) sum += A[idxA++];
            if (idxK < KLen) sum += K[idxK++];
            result.push_back(sum % 10);
            carry = sum / 10;
        }
        if (carry) result.push_back(carry);
        reverse(result.begin(), result.end());
        return result;
    }
};