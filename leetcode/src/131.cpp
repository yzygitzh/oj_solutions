class Solution {
public:
    vector<vector<string>> partition(string s) {
        int sLen = s.length();
        vector<vector<string> > result;
        if (sLen == 0) return result;
        
        // calculate possible palindrome lengths, O(N^2)
        vector<vector<int> > palinLen(sLen, vector<int>());
        for (int i = 0; i < sLen; i++) {
            for (int j = 0; i - j >= 0 && i + j < sLen; j++) {
                if (s[i - j] == s[i + j]) {
                    palinLen[i - j].push_back(2 * j + 1);
                } else {
                    break;
                }
            }
            for (int j = 0; i - j >= 0 && i + j + 1 < sLen; j++) {
                if (s[i - j] == s[i + j + 1]) {
                    palinLen[i - j].push_back(2 * (j + 1));
                } else {
                    break;
                }
            }
        }
        
        for (int i = 0; i < sLen; i++) {
            sort(palinLen[i].begin(), palinLen[i].end());
        }
        
        vector<string> partResult;
        genPartition(0, s, palinLen, partResult, result);
        return result;
    }
    
    void genPartition(int startIdx, string &s, vector<vector<int> > &palinLen,
                      vector<string> &partResult, vector<vector<string> > &result) {
        if (startIdx == s.length()) {
            result.push_back(partResult);
        } else {
            int numOfLens = palinLen[startIdx].size();
            for (int i = 0; i < numOfLens; i++) {
                if (startIdx + palinLen[startIdx][i] > s.length()) break;
                partResult.push_back(s.substr(startIdx, palinLen[startIdx][i]));
                genPartition(startIdx + palinLen[startIdx][i], s, palinLen, partResult, result);
                partResult.pop_back();
            }
        }
    }
};