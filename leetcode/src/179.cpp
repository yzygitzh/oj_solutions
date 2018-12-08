class Solution {
public:
    class StrCmp {
    public:
        bool operator() (const string &a, const string &b) const {
            return compare(a, b);
        }
        
        bool compare(const string &a, const string &b) const {
            if (a.length() == b.length()) return a > b;
            else {
                if (a.length() < b.length()) {
                    if (b.substr(0, a.length()) == a) {
                        // e.g. 30 vs. 3090, need return false.
                        return compare(a, b.substr(a.length()));
                    } else {
                        return a > b;
                    }
                } else {
                    if (a.substr(0, b.length()) == b) {
                        // e.g. 3090 vs. 30, need return true.
                        return compare(a.substr(b.length()), b);
                    } else {
                        return a > b;
                    }
                }
            }
        }
    };
    
    string largestNumber(vector<int>& nums) {
        int numsLen = nums.size();
        vector<string> numStrs;
        for (int i = 0; i < numsLen; i++) {
            numStrs.push_back(to_string(nums[i]));
        }
        sort(numStrs.begin(), numStrs.end(), StrCmp());
        if (numStrs[0] == "0") return "0";
        string result;
        for (int i = 0; i < numsLen; i++) {
            result += numStrs[i];
        }
        return result;
    }
};