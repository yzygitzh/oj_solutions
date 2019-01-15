class Solution {
public:
    vector<string> result;
    string center;
    unordered_map<char, int> letterCnt;
    
    vector<string> generatePalindromes(string s) {
        // divide letters into two same parts
        int sLen = s.length();
        for (int i = 0; i < sLen; i++) {
            letterCnt[s[i]]++;
        }
        int oddCnt = 0;
        char oddLetter;
        for (auto itr = letterCnt.begin(); itr != letterCnt.end(); ++itr) {
            if (itr->second % 2) {
                oddCnt += 1;
                oddLetter = itr->first;
            }
        }
        if (oddCnt > 1) {
            return result;
        } else if (oddCnt == 1) {
            center += oddLetter;
            letterCnt[oddLetter]--;
        }
        
        // build half string
        string halfStr, partResult;
        for (auto itr = letterCnt.begin(); itr != letterCnt.end(); ++itr) {
            itr->second /= 2;
            while (itr->second--) {
                halfStr += itr->first;
            }
        }
        vector<int> visited(halfStr.length(), 0);
        dfs(halfStr, partResult, visited);
        
        return result;
    }
    
    void dfs(string &halfStr, string &partResult, vector<int>& visited) {
        if (partResult.length() == halfStr.length()) {
            string rPartResult = partResult;
            reverse(rPartResult.begin(), rPartResult.end());
            result.push_back(partResult + center + rPartResult);
        } else {
            for (int i = 0; i < halfStr.length(); i++) {
                if (visited[i]) continue;
                visited[i] = 1;
                partResult.push_back(halfStr[i]);
                dfs(halfStr, partResult, visited);
                partResult.pop_back();
                visited[i] = 0;
                while (i + 1 < halfStr.length() &&
                       halfStr[i] == halfStr[i + 1]) i++;
            }
        }
    }
};