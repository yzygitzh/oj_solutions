class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> result(n, 0);
        // func id, duration
        vector<pair<int, int>> funcStack;
        funcStack.push_back(make_pair(-1, 0)); // idle time
        int lastTime = 0;
        for (auto& log : logs) {
            int idx = 0;
            while (log[idx] != ':') idx++;
            int funcId = stoi(log.substr(0, idx));
            idx++;
            char logType = log[idx];
            while (log[idx] != ':') idx++;
            idx++;
            int timeStamp = stoi(log.substr(idx));
            
            if (logType == 's') {
                funcStack.back().second += timeStamp - lastTime;
                funcStack.push_back(make_pair(funcId, 0));
                lastTime = timeStamp;
            } else {
                funcStack.back().second += timeStamp + 1 - lastTime;
                result[funcStack.back().first] += funcStack.back().second;
                funcStack.pop_back();
                lastTime = timeStamp + 1;
            }
        }
        return result;
    }
};