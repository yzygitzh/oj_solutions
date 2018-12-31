class Solution {
public:
    vector<int> numsSameConsecDiff(int N, int K) {
        vector<int> result;
        queue<string> bfsQueue;
        if (N == 1) bfsQueue.push(to_string(0));
        for (int i = 1; i <= 9; i++) bfsQueue.push(to_string(i));
        
        while (!bfsQueue.empty()) {
            string currNumStr = bfsQueue.front();
            bfsQueue.pop();
            if (currNumStr.length() == N) {
                result.push_back(atoi(currNumStr.c_str()));
            } else {
                int lastDigit = (*currNumStr.rbegin()) - '0';
                if (K == 0) {
                    bfsQueue.push(currNumStr + to_string(lastDigit));
                } else {
                    if (lastDigit - K >= 0) bfsQueue.push(currNumStr + to_string(lastDigit - K));
                    if (lastDigit + K <= 9) bfsQueue.push(currNumStr + to_string(lastDigit + K));
                }
            }
        }
        
        return result;
    }
};