class Solution {
public:
    int findRepeat(string s) {
        string p = s;
        string t = s;
        t += s;
        t = t.substr(1, t.length() - 2);
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
        
        // match
        i = k = 0;
        while (i < tLen && k < pLen) {
            if (k < 0 || t[i] == p[k]) i++, k++;
            else k = next[k];
        }
        
        if (k == pLen) return i - k + 1;
        else return -1;
    }
    
    string encode(string s) {
        // 2D/1D dp
        int sLen = s.length();
        if (sLen == 0) return "";
        vector<vector<string>> minEncode(sLen, vector<string>(sLen, ""));
        for (int i = 1; i <= sLen; i++) {
            for (int j = 0; j + i - 1 < sLen; j++) {
                if (i <= 4) {
                    minEncode[j][j + i - 1] = s.substr(j, i);
                } else {
                    // characters before k is left string
                    for (int k = j + 1; k < j + i; k++) {
                        if (minEncode[j][j + i - 1] == "" ||
                            minEncode[j][j + i - 1].length() >
                            minEncode[j][k - 1].length() + minEncode[k][j + i - 1].length()) {
                            minEncode[j][j + i - 1] = minEncode[j][k - 1];
                            minEncode[j][j + i - 1] += minEncode[k][j + i - 1];
                        }
                    }
                    // find repeating string
                    int pLen = findRepeat(s.substr(j, i));
                    if (pLen > 0) {
                        string rEncode = to_string(i / pLen);
                        rEncode += '[';
                        rEncode += minEncode[j][j + pLen - 1];
                        rEncode += ']';
                        if (minEncode[j][j + i - 1] == "" ||
                            minEncode[j][j + i - 1].length() > rEncode.length()) {
                            minEncode[j][j + i - 1] = rEncode;
                        }
                    }
                }
            }
        }
        return minEncode[0][sLen - 1];
    }
};