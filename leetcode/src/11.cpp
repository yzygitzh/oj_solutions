class Solution {
public:
    int maxArea(vector<int>& height) {
        int pointNum = height.size();
        int left = 0, right = pointNum - 1;
        int maxArea = 0;
        while (left != right) {
            int leftHeight = height[left];
            int rightHeight = height[right];
            int minHeight = leftHeight < rightHeight ? leftHeight : rightHeight;
            int area = minHeight * (right - left);
            if (area > maxArea) maxArea = area;
            if (leftHeight < rightHeight) left++;
            else right--;
        }
        return maxArea;
    }
};