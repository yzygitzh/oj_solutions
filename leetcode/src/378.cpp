class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();
        if (m == 0) return 0;
        int n = matrix[0].size();
        if (n == 0) return 0;
        
        priority_queue<int> maxHeap;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                maxHeap.push(matrix[i][j]);
                if (maxHeap.size() > k) {
                    maxHeap.pop();
                }
            }
        }
        return maxHeap.top();
    }
};