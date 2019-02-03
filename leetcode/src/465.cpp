class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
        unordered_map<int, int> nodeCnt;
        for (auto itr = transactions.begin();
             itr != transactions.end(); ++itr) {
            nodeCnt[(*itr)[0]] -= (*itr)[2];
            nodeCnt[(*itr)[1]] += (*itr)[2];
        }
        unordered_map<int, int> positive, negative;
        for (auto itr = nodeCnt.begin(); itr != nodeCnt.end(); ++itr) {
            if (itr->second > 0) {
                positive[itr->second]++;
            } else if (itr->second < 0) {
                negative[-itr->second]++;
            }
        }
        // eliminate same pairs
        int sameCnt = 0;
        vector<int> eliminated;
        for (auto itr = positive.begin(); itr != positive.end(); ++itr) {
            if (negative.count(itr->first)) {
                int delta = min(positive[itr->first], negative[itr->first]);
                positive[itr->first] -= delta;
                negative[itr->first] -= delta;
                sameCnt += delta;
                if (negative[itr->first] == 0) negative.erase(itr->first);
                if (positive[itr->first] == 0) eliminated.push_back(itr->first);
            }
        }
        for (auto itr = eliminated.begin(); itr != eliminated.end(); ++itr) {
            positive.erase(*itr);
        }
        // dfs
        return sameCnt + dfs(positive, negative);
    }
    
    int dfs(unordered_map<int, int> positive,
            unordered_map<int, int> negative) {
        if (positive.size() == 0) return 0;
        // use positive's first element
        int minStep = ~(1 << 31);
        for (auto itr = negative.begin(); itr != negative.end(); ++itr) {
            auto newPositive = positive;
            auto newNegative = negative;
            int delta = min(positive.begin()->first, itr->first);
            // modify newPositive
            newPositive[positive.begin()->first]--;
            if (newPositive[positive.begin()->first] == 0) {
                newPositive.erase(positive.begin()->first);
            }
            if (positive.begin()->first - delta > 0) {
                newPositive[positive.begin()->first - delta]++;
            }
            // modify newNgative
            newNegative[itr->first]--;
            if (newNegative[itr->first] == 0) {
                newNegative.erase(itr->first);
            }
            if (itr->first - delta > 0) {
                newNegative[itr->first - delta]++;
            }
            minStep = min(minStep, dfs(newPositive, newNegative) + 1);
        }
        return minStep;
    }
};