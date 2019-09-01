class Solution {
public:
    int largestSumAfterKNegations(vector<int>& A, int K) {
        map<int, int> negCnt, posCnt;
        for (int i : A) {
            if (i < 0) negCnt[-i]++;
            else posCnt[i]++;
        }
        while (K) {
            if (negCnt.size() > 0) {
                int num = negCnt.rbegin()->first;
                negCnt[num]--;
                posCnt[num]++;
                if (negCnt[num] == 0) negCnt.erase(num);
            } else {
                int num = posCnt.begin()->first;
                if (num > 0) {
                    negCnt[num]++;
                    posCnt[num]--;
                    if (posCnt[num] == 0) posCnt.erase(num);
                }
            }
            K--;
        }
        int result = 0;
        for (auto itr = negCnt.begin(); itr != negCnt.end(); ++itr) {
            result -= itr->first * itr->second;
        }
        for (auto itr = posCnt.begin(); itr != posCnt.end(); ++itr) {
            result += itr->first * itr->second;
        }
        return result;
    }
};