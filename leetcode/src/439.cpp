class Solution {
public:
    class ExpElem {
    public:
        char cond, leftVal, rightVal;
        ExpElem (char _cond)
            : cond(_cond), leftVal('#'), rightVal('#') {}
    };
    
    string parseTernary(string exp) {
        int expLen = exp.length(), idx = 0;
        vector<ExpElem> expStack;
        while (idx < expLen) {
            // invariant: exp[idx] is T or F or 0-9
            if (idx + 1 < expLen && exp[idx + 1] == '?') {
                expStack.push_back(ExpElem(exp[idx]));
            } else {
                if (expStack.size() > 0) {
                    if (expStack.rbegin()->leftVal == '#') {
                        expStack.rbegin()->leftVal = exp[idx];
                    } else {
                        expStack.rbegin()->rightVal = exp[idx];
                    }
                } else {
                    expStack.push_back(ExpElem('T'));
                    expStack.rbegin()->leftVal = exp[idx];
                    expStack.rbegin()->rightVal = exp[idx];
                }
                while (expStack.size() > 1 &&
                       expStack.rbegin()->leftVal != '#' &&
                       expStack.rbegin()->rightVal != '#') {
                    ExpElem top = *expStack.rbegin();
                    expStack.pop_back();
                    char val = top.cond == 'T' ? top.leftVal : top.rightVal;
                    if (expStack.rbegin()->leftVal == '#') {
                        expStack.rbegin()->leftVal = val;
                    } else {
                        expStack.rbegin()->rightVal = val;
                    }
                }
            }
            idx += 2;
        }
        return expStack.begin()->cond == 'T' ? 
               string() + expStack.begin()->leftVal : string() + expStack.begin()->rightVal;
    }
};