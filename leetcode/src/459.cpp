class Solution {
public:
    int kmp(string p, string t) {
        int pLen = p.length(), tLen = t.length();
        // build next
        vector<int> next(pLen);
        next[0] = -1;
        int i = 0, k = -1;
        while (i < pLen) {
            while (k >= 0 && p[i] != p[k]) k = next[k];
            i++, k++;
            if (i == pLen) break;
            if (p[i] == p[k]) next[i] = next[k];
            else next[i] = k;
        }
        int j = 0;
        i = 0;
        while (i < pLen && j < tLen) {
            if (i < 0 || p[i] == t[j]) i++, j++;
            else i = next[i];
        }
        if (i == pLen) return j - pLen;
        else return -1;
    }
    
    bool repeatedSubstringPattern(string s) {
        if (s.length() <= 1) return false;
        string newS = s;
        newS += s;
        newS = newS.substr(1, newS.length() - 2);
        return kmp(s, newS) != -1;
    }
};