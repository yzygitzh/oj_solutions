class Solution {
public:
    class BfsElem {
    public:
        int row, col, val;
        BfsElem(int _row, int _col, int _val): row(_row), col(_col), val(_val) {}
        bool operator< (const BfsElem &b) const {
            return val > b.val;
        }
    };
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        priority_queue<BfsElem> bfsQ;
        vector<vector<int> > visited(n, vector<int>(n, 0));
        bfsQ.push(BfsElem(0, 0, matrix[0][0]));
        while (--k) {
            BfsElem top = bfsQ.top();
            bfsQ.pop();
            if (top.row + 1 < n && !visited[top.row + 1][top.col]) {
                visited[top.row + 1][top.col] = 1;
                bfsQ.push(BfsElem(top.row + 1, top.col, matrix[top.row + 1][top.col]));
            }
            if (top.col + 1 < n && !visited[top.row][top.col + 1]) {
                visited[top.row][top.col + 1] = 1;
                bfsQ.push(BfsElem(top.row, top.col + 1, matrix[top.row][top.col + 1]));
            }
        }
        return bfsQ.top().val;
    }
};