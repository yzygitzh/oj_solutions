class Solution {
public:
    long long result = 0;
    
    void addToResult(long long x) {
        result += x;
        result %= 1000000007LL;
    }
    
    int uniqueLetterString(string S) {
        long long SLen = S.length();
        long long idx = 0;
        map<char, vector<long long>> charIndices;
        while (idx < SLen) {
            // invariant: all substrings in S[0, idx - 1] has been counted
            // need count [?, idx] for all characters
            charIndices[S[idx]].push_back(idx);
            for (auto itr = charIndices.begin();
                 itr != charIndices.end(); ++itr) {
                if (itr->second.size() == 1) {
                    addToResult(*(itr->second.begin()) + 1LL);
                } else {
                    addToResult(*(itr->second.rbegin()) -
                                *(++(itr->second.rbegin())));
                }
            }
            idx++;
        }
        return (int)result;
    }
};