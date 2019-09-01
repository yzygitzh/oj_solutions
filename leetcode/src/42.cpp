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
            leftMax = getMax(leftMax, height[left]);
            rightMax = getMax(rightMax, height[right]);
            if (leftMax < rightMax) {
                water += leftMax - height[left];
                left++;
            } else {
                water += rightMax - height[right];
                right--;
            }
        }
        return water;
    }
};