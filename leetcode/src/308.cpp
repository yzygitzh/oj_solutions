class NumMatrix {
public:
    class QuadTreeNode {
    public:
        int lX, lY, hX, hY, sum;
        QuadTreeNode *lu, *ru, *ld, *rd;
        QuadTreeNode(int _lX, int _lY, int _hX, int _hY, int _sum)
            :lX(_lX), lY(_lY), hX(_hX), hY(_hY), sum(_sum),
             lu(nullptr), ru(nullptr), ld(nullptr), rd(nullptr) {}
    };
    
    QuadTreeNode *qRoot = nullptr;
    
    QuadTreeNode* buildTree(vector<vector<int>>& matrix,
                            int lX, int lY, int hX, int hY) {
        if (lX > hX || lY > hY) return nullptr;
        if (lX == hX && lY == hY) {
            return new QuadTreeNode(lX, lY, hX, hY, matrix[lX][lY]);
        }
        QuadTreeNode *p = new QuadTreeNode(lX, lY, hX, hY, 0);
        int midX = (lX + hX) / 2, midY = (lY + hY) / 2;
        p->lu = buildTree(matrix, lX, lY, midX, midY);
        p->ru = buildTree(matrix, lX, midY + 1, midX, hY);
        p->ld = buildTree(matrix, midX + 1, lY, hX, midY);
        p->rd = buildTree(matrix, midX + 1, midY + 1, hX, hY);
        if (p->lu != nullptr) p->sum += p->lu->sum;
        if (p->ru != nullptr) p->sum += p->ru->sum;
        if (p->ld != nullptr) p->sum += p->ld->sum;
        if (p->rd != nullptr) p->sum += p->rd->sum;
        return p;
    }
    
    void updateTree(QuadTreeNode *p, int x, int y, int newVal) {
        if (p == nullptr) return;
        if (p->lX == x && p->hX == x &&
            p->lY == y && p->hY == y) {
            p->sum = newVal;
        } else {
            int midX = (p->lX + p->hX) / 2,
                midY = (p->lY + p->hY) / 2;
            if (x <= midX && y <= midY) updateTree(p->lu, x, y, newVal);
            else if (x <= midX && y >= midY + 1) updateTree(p->ru, x, y, newVal);
            else if (x >= midX + 1 && y <= midY) updateTree(p->ld, x, y, newVal);
            else updateTree(p->rd, x, y, newVal);
            p->sum = 0;
            if (p->lu != nullptr) p->sum += p->lu->sum;
            if (p->ru != nullptr) p->sum += p->ru->sum;
            if (p->ld != nullptr) p->sum += p->ld->sum;
            if (p->rd != nullptr) p->sum += p->rd->sum;
        }
    }
    
    int sumTree(QuadTreeNode *p, int lX, int lY, int hX, int hY) {
        if (p == nullptr) return 0;
        if (p->lX == lX && p->hX == hX &&
            p->lY == lY && p->hY == hY) {
            return p->sum;
        }
        int sum = 0;
        int midX = (p->lX + p->hX) / 2,
            midY = (p->lY + p->hY) / 2;
        if (lX <= midX && lY <= midY) {
            sum += sumTree(p->lu, lX, lY, min(midX, hX), min(midY, hY));
        }
        if (lX <= midX && hY >= midY + 1) {
            sum += sumTree(p->ru, lX, max(midY + 1, lY), min(midX, hX), hY);
        }
        if (hX >= midX + 1 && lY <= midY) {
            sum += sumTree(p->ld, max(midX + 1, lX), lY, hX, min(midY, hY));
        }
        if (hX >= midX + 1 && hY >= midY + 1) {
            sum += sumTree(p->rd, max(midX + 1, lX), max(midY + 1, lY), hX, hY);
        }
        return sum;
    }
    
    NumMatrix(vector<vector<int>> matrix) {
        // quad-tree
        int m = matrix.size();
        if (m == 0) return;
        int n = matrix[0].size();
        if (n == 0) return;
        qRoot = buildTree(matrix, 0, 0, m - 1, n - 1);
    }
    
    void update(int row, int col, int val) {
        if (qRoot == nullptr) return;
        updateTree(qRoot, row, col, val);
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        if (qRoot == nullptr) return 0;
        return sumTree(qRoot, row1, col1, row2, col2);
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */