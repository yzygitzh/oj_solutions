class Solution {
public:
    int result = 0;
    
    // empty string is lower than non-empty string
    bool lessThan(string a, string b) {
        int aLen = a.length(), bLen = b.length();
        if (aLen < bLen) return true;
        else if (aLen > bLen) return false;
        int idx = 0;
        while (idx < aLen) {
            if (a[idx] < b[idx]) return true;
            if (a[idx] > b[idx]) return false;
            idx++;
        }
        return false;
    }

    int strobogrammaticInRange(string low, string high) {
        // 1,69,8,0
        dfs("0", low, high);
        dfs("1", low, high);
        dfs("8", low, high);
        dfs("", low, high);
        return result;
    }
    
    void dfs(string currNum, string low, string high) {
        if (lessThan(high, currNum)) {
            return;
        } else {
            if ((lessThan(low, currNum) || low == currNum) &&
                !(currNum[0] == '0' && currNum.length() > 1)) {
                result++;
            }
            char tryChar[5] = {'0', '1', '6', '8', '9'};
            for (int i = 0; i < 5; i++) {
                string tryStr;
                tryStr += tryChar[i];
                tryStr += currNum;
                if (tryChar[i] == '6') tryStr += '9';
                else if (tryChar[i] == '9') tryStr += '6';
                else tryStr += tryChar[i];
                dfs(tryStr, low, high);
            }
        }
    }
};