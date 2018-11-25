#include <map>
#include <string>

using namespace std;

class Solution {
    map<int, string> romanMap;
public:
    Solution() {
        romanMap[1] = "I";
        romanMap[5] = "V";
        romanMap[10] = "X";
        romanMap[50] = "L";
        romanMap[100] = "C";
        romanMap[500] = "D";
        romanMap[1000] = "M";
    }
    string intToRoman(int num) {
        string ans = "";
        int filter = 1000;
        while (filter > 0) {
            int currDigit = (num / filter) % 10;
            
            if (currDigit == 0) {
                ans += "";
            } else if (currDigit <= 3) {
                for (int i = 0; i < currDigit; i++)
                    ans += romanMap[filter];
            } else if (currDigit == 4) {
                ans += romanMap[filter] + romanMap[5 * filter];
            } else if (currDigit <= 8) {
                ans += romanMap[5 * filter];
                for (int i = 5; i < currDigit; i++)
                    ans += romanMap[filter];
            } else {
                ans += romanMap[filter] + romanMap[10 * filter];
            }
            
            num -= currDigit * filter;
            filter /= 10;
        }
        return ans;
    }
};