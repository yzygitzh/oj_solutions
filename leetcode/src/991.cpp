class Solution {
public:
    int brokenCalc(int X, int Y) {
        int step = 0;
        while (Y > X) {
            if (Y % 2) {
                Y++;
            } else {
                Y /= 2;
            }
            step++;
        }
        return step + X - Y;
    }
};