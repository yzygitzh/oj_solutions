class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> restChar;
        unordered_set<char> charSet;
        
        for (auto c : p) {
            restChar[c]++;
            charSet.insert(c);
        }
        
        vector<int> result;
        for (int i = 0; i < s.length(); i++) {
            if (charSet.find(s[i]) != charSet.end()) {
                restChar[s[i]]--;
                if (restChar[s[i]] == 0) {
                    restChar.erase(s[i]);
                }
            }
            if (i >= p.length() &&
                charSet.find(s[i - p.length()]) != charSet.end()) {
                restChar[s[i - p.length()]]++;
                if (restChar[s[i - p.length()]] == 0) {
                    restChar.erase(s[i - p.length()]);
                }
            }
            if (restChar.size() == 0) {
                result.push_back(i - p.length() + 1);
            }
        }
        
        return result;
    }
};