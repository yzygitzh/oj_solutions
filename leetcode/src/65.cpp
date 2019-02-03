class Solution {
public:
    bool isNumber(string s) {
        // enumerate valid characters
        unordered_set<char> validChar;
        validChar.insert('e');
        validChar.insert('-');
        validChar.insert('+');
        validChar.insert('.');
        for (int i = 0; i < 10; i++) validChar.insert('0' + i);
        
        // remove spaces
        int sIdx = 0, sLen = s.length();
        while (sIdx < sLen && s[sIdx] == ' ') sIdx++;
        s = s.substr(sIdx);
        while (s.length() > 0 && *s.rbegin() == ' ') s.pop_back();
        
        // check invalid characters
        for (auto itr = s.begin(); itr != s.end(); ++itr) {
            if (!validChar.count(*itr)) return false;
        }
        
        // no invalid character including space
        sIdx = 0;
        sLen = s.length();
        bool hasInt = false, hasFrac = false;
        
        // try find sign
        if (sIdx < sLen && (s[sIdx] == '-' || s[sIdx] == '+')) {
            sIdx++;
        }
        
        // try find int
        while (sIdx < sLen && s[sIdx] >= '0' && s[sIdx] <= '9') {
            hasInt = true;
            sIdx++;
        }
        
        // try find dot
        if (sIdx < sLen && s[sIdx] == '.') {
            sIdx++;
        }
        
        // try find frac
        while (sIdx < sLen && s[sIdx] >= '0' && s[sIdx] <= '9') {
            hasFrac = true;
            sIdx++;
        }
        
        // try find e
        if (sIdx < sLen && s[sIdx] == 'e') {
            sIdx++;
            bool validE = false;
            // try find esign
            if (sIdx < sLen && (s[sIdx] == '-' || s[sIdx] == '+')) {
                sIdx++;
            }
            // try find e-num
            while (sIdx < sLen && s[sIdx] >= '0' && s[sIdx] <= '9') {
                validE = true;
                sIdx++;
            }
            if (!validE) return false;
        }
        
        return sIdx == sLen && (hasInt || hasFrac);
    }
};