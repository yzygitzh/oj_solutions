class Solution {
public:
    static bool cmp(const string& a, const string& b) {
        return a.length() > b.length();
    }
    
    string frequencySort(string s) {
        int sLen = s.length();
        unordered_map<char, string> charToStr;
        for (int i = 0; i < sLen; i++) {
            charToStr[s[i]] += s[i];
        }
        vector<string> strs;
        for (auto itr = charToStr.begin();
             itr != charToStr.end(); ++itr) {
            strs.push_back(itr->second);
        }
        sort(strs.begin(), strs.end(), cmp);
        string result;
        for (auto itr = strs.begin();
             itr != strs.end(); ++itr) {
            result += *itr;
        }
        return result;
    }
};