class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int maxArea = 0;
        int heightsLen = heights.size();
        if (heightsLen == 0) return maxArea;
        
        int expandLen;
        vector<pair<int, int> > hStack; // height, length
        for (int i = 0; i < heightsLen; i++) {
            expandLen = 0;
            while (hStack.size() > 0 && hStack.rbegin()->first >= heights[i]) {
                expandLen += hStack.rbegin()->second;
                if (hStack.rbegin()->first * expandLen > maxArea) {
                    maxArea = hStack.rbegin()->first * expandLen;
                }
                hStack.pop_back();
            }
            expandLen += 1;
            hStack.push_back(make_pair(heights[i], expandLen));

            if (heights[i] * expandLen > maxArea) {
                maxArea = heights[i] * expandLen;
            }
            // invariant: heights in stack are increasing
        }
        
        int stackSize = hStack.size();
        expandLen = 0;
        for (int i = stackSize - 1; i >= 0; i--) {
            expandLen += hStack[i].second;
            if (hStack[i].first * expandLen > maxArea) {
                maxArea = hStack[i].first * expandLen;
            }
        }
        
        return maxArea;
    }
};