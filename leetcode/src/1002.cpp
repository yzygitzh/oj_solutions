class Solution {
public:
    vector<string> commonChars(vector<string>& A) {
        int ALen = A.size();
        unordered_map<char, int> intersectCnt;
        for (auto c : A[0]) {
            intersectCnt[c]++;
        }
        for (int i = 1; i < ALen; i++) {
            unordered_map<char, int> currCnt;
            for (auto c : A[i]) {
                currCnt[c]++;
            }
            for (auto itr = intersectCnt.begin();
                 itr != intersectCnt.end(); ++itr) {
                itr->second = min(itr->second, currCnt[itr->first]);
            }
        }
        vector<string> result;
        for (auto itr = intersectCnt.begin();
             itr != intersectCnt.end(); ++itr) {
            for (int i = 0; i < itr->second; i++) {
                result.push_back(string() + itr->first);
            }
        }
        return result;
    }
};