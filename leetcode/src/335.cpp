class Solution {
public:
    bool isSelfCrossing(vector<int>& x) {
        // case 1: x hits (x + 3)
        // case 2: x hits (x + 4)
        // case 3: x hits (x + 5)
        int xLen = x.size();
        if (xLen <= 3) return false;
        for (int i = 3; i < xLen; i++) {
            if (x[i] >= x[i - 2] &&
                x[i - 1] <= x[i - 3]) return true;
            if (i >= 4 &&
                x[i] + x[i - 4] >= x[i - 2] &&
                x[i - 1] == x[i - 3]) return true;
            if (i >= 5 &&
                x[i - 2] >= x[i - 4] &&
                x[i - 4] - x[i - 2] + x[i] >= 0 &&
                x[i - 4] - x[i - 2] + x[i] <= x[i - 4] &&
                x[i - 3] >= x[i - 5] &&
                x[i - 5] - x[i - 3] + x[i - 1] >= 0 &&
                x[i - 5] - x[i - 3] + x[i - 1] <= x[i - 5]) return true;
        }
        return false;
    }
};