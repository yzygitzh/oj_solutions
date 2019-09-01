class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        vector<int> result(T.size(), 0);
        vector<int> idxStack;
        for (int i = 0; i < T.size(); i++) {
            while (!idxStack.empty() && T[i] > T[idxStack.back()]) {
                result[idxStack.back()] = i - idxStack.back();
                idxStack.pop_back();
            }
            idxStack.push_back(i);
        }
        return result;
    }
};