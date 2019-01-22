// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

class Solution {
public:
    int rand10() {
        int num1 = rand7();
        int num2 = rand7();
        if ((num1 - 1) * 7 + num2 <= 40) {
            return ((num1 - 1) * 7 + num2 - 1) / 4 + 1;
        }
        return rand10();
    }
};