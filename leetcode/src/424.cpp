class Solution {
public:
    int characterReplacement(string s, int k) {
        // for each character extract their segments
        // and fill k characters in them
        
        // 'a', 1(len), 0(endIdx)
        unordered_map<char, vector<pair<int, int>>> charSeg;
        int sLen = s.length();
        int idx = 0;
        while (idx < sLen) {
            int oldIdx = idx;
            while (idx < sLen && s[idx] == s[oldIdx]) idx++;
            if (charSeg[s[oldIdx]].size() > 0) {
                charSeg[s[oldIdx]].rbegin()->second -= sLen - oldIdx;
            }
            charSeg[s[oldIdx]].push_back(make_pair(idx - oldIdx, sLen - idx));
        }
        
        int maxResult = min(sLen, k);
        for (auto itr = charSeg.begin(); itr != charSeg.end(); ++itr) {
            deque<pair<int, int>> segWindow;
            int rest = k, connLen = 0;
            for (auto itr2 = itr->second.begin();
                 itr2 != itr->second.end(); ++itr2) {
                // connection but no move fill
                maxResult = max(maxResult, itr2->first + connLen + 
                                min(rest, sLen - (itr2->first + connLen)));
                // connection and move fill
                while (segWindow.size() > 0 && rest < itr2->second) {
                    connLen -= segWindow.front().first + segWindow.front().second;
                    rest += segWindow.front().second;
                    segWindow.pop_front();
                }
                if (rest >= itr2->second) {
                    segWindow.push_back(*itr2);
                    connLen += itr2->first + itr2->second;
                    rest -= itr2->second;
                }
                maxResult = max(maxResult, connLen + min(rest, sLen - connLen));
            }
        }
        
        return maxResult;
    }
};