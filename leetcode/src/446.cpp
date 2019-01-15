class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        unordered_map<long long, vector<pair<int, int>>> diffToIdxPairs;
        int ALen = A.size();
        
        for (int i = 0; i < ALen; i++) {
            for (int j = i + 1; j < ALen; j++) {
                diffToIdxPairs[(long long)A[j] - (long long)A[i]].push_back(make_pair(i, j));
            }
        }

        int totalNums = 0;
        for (auto itr = diffToIdxPairs.begin(); itr != diffToIdxPairs.end(); ++itr) {
            vector<pair<int, int>>& idxPairs = itr->second;
            map<int, vector<int>> adjList;
            map<int, int> idxToSeqNum;
            for (auto itr2 = idxPairs.begin(); itr2 != idxPairs.end(); ++itr2) {
                adjList[itr2->second].push_back(itr2->first);
                idxToSeqNum[itr2->first] = idxToSeqNum[itr2->second] = 0;
            }
            for (auto itr2 = adjList.begin(); itr2 != adjList.end(); ++itr2) {
                vector<int>& targets = itr2->second;
                for (auto itr3 = targets.begin(); itr3 != targets.end(); ++itr3) {
                    idxToSeqNum[itr2->first] += idxToSeqNum[*itr3] + 1;
                }
                // substract 1-length sequences
                totalNums += idxToSeqNum[itr2->first] - targets.size();
            }
        }
        
        return totalNums;
    }
};