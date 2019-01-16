class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> result(length);
        if (length == 0) return result;
        // sweep line
        vector<pair<int, long long>> deltas;
        for (auto itr = updates.begin(); itr != updates.end(); ++itr) {
            deltas.push_back(make_pair((*itr)[0], (long long)(*itr)[2]));
            deltas.push_back(make_pair((*itr)[1] + 1, -(long long)(*itr)[2]));
        }
        sort(deltas.begin(), deltas.end());
        int deltaIdx = 0;
        int currVal = 0;
        for (int i = 0; i < length; i++) {
            if (deltaIdx < deltas.size() &&
                deltas[deltaIdx].first == i) {
                while (deltaIdx < deltas.size() &&
                       deltas[deltaIdx].first == i) {
                    currVal += deltas[deltaIdx].second;
                    deltaIdx++;
                }
            }
            result[i] = currVal;
        }
        return result;
    }
};