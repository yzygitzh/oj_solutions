class Solution {
public:
    int getMin(int a, int b) {
        return a < b ? a : b;
    }
    
    int getMax(int a, int b) {
        return a > b ? a : b;
    }
    
    int trap(vector<int>& height) {
        int heightLen = height.size();
        if (heightLen < 3) return 0;
        
        int left = 0, right = heightLen - 1;
        int leftMax = height[left], rightMax = height[right];
        int water = 0;
        while (left <= right) {
            if (height[left] <= getMin(leftMax, rightMax)) {
                water += getMin(leftMax, rightMax) - height[left];
                left++;
                leftMax = getMax(leftMax, height[left]);
            } else if (height[right] <= getMin(leftMax, rightMax)) {
                water += getMin(leftMax, rightMax) - height[right];
                right--;
                rightMax = getMax(rightMax, height[right]);
            }
        }
        return water;
    }
};