class Solution {
public:
    string strWithout3a3b(int A, int B) {
        string result;
        char lastChar = 'b';
        while (A > B && B > 0) {
            result += "aab";
            A -= 2;
            B -= 1;
            lastChar = 'b';
        }
        while (B > A && A > 0) {
            result += "bba";
            B -= 2;
            A -= 1;
            lastChar = 'a';
        }
        while (A > 0 && A == B) {
            if (lastChar == 'b') {
                result += "ab";
            } else {
                result += "ba";
            }
            A--;
            B--;
        }
        // A or B must be zero
        while (A > 0) {
            result += 'a';
            A--;
        }
        while (B > 0) {
            result += 'b';
            B--;
        }
        return result;
    }
};