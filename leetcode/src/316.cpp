class Solution {
public:
    string removeDuplicateLetters(string s) {
        int sLen = s.length();
        map<char, set<int> > charIdx;
        set<char> charSet;
        for (int i = 0; i < sLen; i++) {
            charIdx[s[i]].insert(i);
            charSet.insert(s[i]);
        }
        
        int resultLen = charIdx.size();
        string result;
        for (int i = 0; i < resultLen; i++) {
            for (set<char>::iterator itr1 = charSet.begin();
                 itr1 != charSet.end(); ++itr1) {
                int currIdx = *charIdx[*itr1].begin();
                bool found = true;
                for (set<char>::iterator itr2 = charSet.begin();
                     itr2 != charSet.end(); ++itr2) {
                    if (*itr1 == *itr2) continue;
                    if (charIdx[*itr2].upper_bound(currIdx) == charIdx[*itr2].end()) {
                        found = false;
                        break;
                    }
                }
                if (found) {
                    charIdx.erase(*itr1);
                    charSet.erase(*itr1);
                    result += *itr1;
                    // clean other indices
                    for (set<char>::iterator itr2 = charSet.begin();
                         itr2 != charSet.end(); ++itr2) {
                        while (!charIdx[*itr2].empty() && *charIdx[*itr2].begin() < currIdx) {
                            charIdx[*itr2].erase(*charIdx[*itr2].begin());
                        }
                    }
                    break;
                }
            }
        }
        return result;
    }
};