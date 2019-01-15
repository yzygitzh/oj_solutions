class Solution {
public:
    vector<int> powerfulIntegers(int x, int y, int bound) {
        set<int> uniqResult;
        vector<int> xPows, yPows;
        
        int xPow = 1;
        while (xPow <= bound) {
            xPows.push_back(xPow);
            xPow *= x;
            if (xPow == 1) break;
        }
        
        int yPow = 1;
        while (yPow <= bound) {
            yPows.push_back(yPow);
            yPow *= y;
            if (yPow == 1) break;
        }
        
        int xPowsLen = xPows.size(), yPowsLen = yPows.size();
        for (int i = 0; i < xPowsLen; i++) {
            for (int j = 0; j < yPowsLen; j++) {
                if (xPows[i] + yPows[j] <= bound) uniqResult.insert(xPows[i] + yPows[j]);
            }
        }
        
        return vector<int>(uniqResult.begin(), uniqResult.end());
    }
};