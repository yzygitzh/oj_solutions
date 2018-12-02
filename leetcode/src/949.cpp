class Solution {
public:
    int maxHour = -1, maxMinute = -1;
    
    string largestTimeFromDigits(vector<int>& A) {
        vector<int> visited(4, 0);
        vector<int> partResult;
        genTime(4, partResult, A, visited);
        
        string result;
        if (maxHour < 0) return result;
        result += '0' + (maxHour / 10);
        result += '0' + (maxHour % 10);
        result += ':';
        result += '0' + (maxMinute / 10);
        result += '0' + (maxMinute % 10);
        return result;
    }
    
    void genTime(int restLen, vector<int>& partResult,
                 vector<int>& A, vector<int>& visited) {
        if (restLen == 0) {
            int hour = partResult[0] * 10 + partResult[1];
            int minute = partResult[2] * 10 + partResult[3];
            if (hour <= 23 && minute <= 59 &&
                (hour > maxHour || hour == maxHour && minute > maxMinute)) {
                maxHour = hour;
                maxMinute = minute;
            }
        } else {
            for (int i = 0; i < 4; i++) {
                if (!visited[i]) {
                    visited[i] = 1;
                    partResult.push_back(A[i]);
                    genTime(restLen - 1, partResult, A, visited);
                    partResult.pop_back();
                    visited[i] = 0;
                }
            }
        }
    }
};