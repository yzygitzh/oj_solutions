class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<int> partResult;
        vector<string> result;
        genIP(4, s, partResult, result);
        return result;
    }
    
    void genIP(int restLen, string &s,
               vector<int> &partResult, vector<string> &result) {
        if (restLen == 0) {
            int sLen = s.length();
            int totalLen = 0;
            for (int i = 0; i < 4; i++) {
                totalLen += partResult[i];
            }
            if (totalLen != sLen) return;
            int fields[4] = {0};
            int sIdx = 0;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < partResult[i]; j++) {
                    fields[i] = fields[i] * 10 + (s[sIdx] - '0');
                    if (partResult[i] > 1 && fields[i] == 0) return;
                    sIdx++;
                }
                if (fields[i] > 255) return;
            }
            string ip;
            for (int i = 0; i < 3; i++) {
                ip += to_string(fields[i]);
                ip += ".";
            }
            ip += to_string(fields[3]);
            result.push_back(ip);
        } else {
            for (int i = 1; i <= 3; i++) {
                partResult.push_back(i);
                genIP(restLen - 1, s, partResult, result);
                partResult.pop_back();
            }
        }
    }
};