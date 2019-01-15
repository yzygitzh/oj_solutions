class Solution {
public:
    string getMinUnit(string s) {
        int sLen = s.length();
        for (int i = 1; i <= sLen / 2; i++) {
            if (sLen % i) continue;
            bool found = true;
            for (int j = 1; j * i < sLen; j++) {
                for (int k = 0; k < i; k++) {
                    if (s[j * i + k] != s[(j - 1) * i + k]) {
                        found = false;
                        break;
                    }
                }
                if (!found) break;
            }
            if (found) return s.substr(0, i);
        }
        return s;
    }
    
    class RationalNumber {
    public:
        string intPart, nonRepeatPart, repeatPart;
        RationalNumber(string _i, string _n, string _r): intPart(_i), nonRepeatPart(_n), repeatPart(_r) {}
    };
    
    RationalNumber parseNumber(string s) {
        int sLen = s.length();
        int sIdx = 0;
        // try to find integer part
        while (sIdx < sLen && s[sIdx] != '.') sIdx++;
        string intPart = s.substr(0, sIdx);
        if (intPart == "") intPart = "0";
        else intPart = to_string(atoi(intPart.c_str()));
        // try to find non-repeat part
        sIdx++;
        int afterPointIdx = sIdx;
        while (sIdx < sLen && s[sIdx] != '(') sIdx++;
        string nonRepeatPart = afterPointIdx < sLen ? s.substr(afterPointIdx, sIdx - afterPointIdx) : "";
        // try to find repeat part
        sIdx++;
        int afterBracketIdx = sIdx;
        while (sIdx < sLen && s[sIdx] != ')') sIdx++;
        string repeatPart = afterBracketIdx < sLen ? s.substr(afterBracketIdx, sIdx - afterBracketIdx) : "";
        
        repeatPart = getMinUnit(repeatPart);
        
        // try to reduce non-repeat part
        int rLen = repeatPart.length();
        while (rLen > 0 && nonRepeatPart.length() > 0) {
            if (*repeatPart.rbegin() == *nonRepeatPart.rbegin()) {
                nonRepeatPart = nonRepeatPart.substr(0, nonRepeatPart.length() - 1);
                repeatPart = repeatPart.substr(rLen - 1, 1) + repeatPart.substr(0, rLen - 1);
            } else {
                break;
            }
        }
        
        if (repeatPart == "0") {
            repeatPart = "";
            if (atoi(nonRepeatPart.c_str()) == 0) nonRepeatPart = "";
        }
        // try to get rid of (9)
        if (repeatPart == "9") {
            repeatPart = "";
            if (nonRepeatPart.length() > 0) {
                string newNonRepeatPart = "1";
                newNonRepeatPart += nonRepeatPart;
                newNonRepeatPart = to_string(atoi(newNonRepeatPart.c_str()) + 1);
                nonRepeatPart = newNonRepeatPart.substr(1);
                if (newNonRepeatPart[0] == '1') {
                    nonRepeatPart = newNonRepeatPart.substr(1);
                } else {
                    intPart = to_string(atoi(intPart.c_str()) + 1);
                    nonRepeatPart = "";
                }
            } else {
                intPart = to_string(atoi(intPart.c_str()) + 1);
            }
        }
        
        return RationalNumber(intPart, nonRepeatPart, repeatPart);
    }
    
    bool isRationalEqual(string S, string T) {
        // divide int/frac part
        // getMinUnit for frac part
        // find representable parts in non-repeating part
        // if repeating part = (9), judge it
        RationalNumber sr = parseNumber(S), tr = parseNumber(T);
        return sr.intPart == tr.intPart && sr.nonRepeatPart == tr.nonRepeatPart && sr.repeatPart == tr.repeatPart;
    }
};