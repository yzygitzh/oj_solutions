class Solution {
public:
    vector<vector<int>> hLines, vLines;
    
    class SegTreeNode {
    public:
        SegTreeNode *left, *right;
        int leftVal, rightVal, maxCov, minCov, lazyVal;
        SegTreeNode() {
            left = right = nullptr;
            leftVal = rightVal = maxCov = minCov = lazyVal = 0;
        }
    };
    
    int getMin(int a, int b) {
        return a < b ? a : b;
    }
    
    int getMax(int a, int b) {
        return a > b ? a : b;
    }
    
    SegTreeNode* buildSegTree(int leftVal, int rightVal) {
        SegTreeNode *p = new SegTreeNode();
        p->leftVal = leftVal;
        p->rightVal = rightVal;
        if (leftVal != rightVal) {
            int mid = (leftVal + rightVal) / 2;
            p->left = buildSegTree(leftVal, mid);
            p->right = buildSegTree(mid + 1, rightVal);
        }
        return p;
    }
    
    void freeSegTree(SegTreeNode *root) {
        if (root == nullptr) return;
        freeSegTree(root->left);
        freeSegTree(root->right);
        delete root;
    }
    
    void modifySeg(SegTreeNode *root, int leftVal, int rightVal, int delta) {
        if (root == nullptr) {
            return;
        }
        if (root->leftVal == leftVal && root->rightVal == rightVal) {
            root->lazyVal += delta;
            root->minCov += delta;
            root->maxCov += delta;
        } else {
            int mid = (root->leftVal + root->rightVal) / 2;
            // first pass lazyVal
            modifySeg(root->left, root->leftVal, mid, root->lazyVal);
            modifySeg(root->right, mid + 1, root->rightVal, root->lazyVal);
            // then pass delta
            if (leftVal <= mid) modifySeg(root->left,
                                          leftVal,
                                          getMin(mid, rightVal),
                                          delta);
            if (rightVal >= mid + 1) modifySeg(root->right,
                                               getMax(mid + 1, leftVal),
                                               rightVal,
                                               delta);
            // clear lazy value
            root->lazyVal = 0;
            // root->left and root->right cannot be nullptr because segment tree is binary complete
            // and this is not the leaf
            root->minCov = getMin(root->left->minCov, root->right->minCov);
            root->maxCov = getMax(root->left->maxCov, root->right->maxCov);
        }
    }
    
    bool isValidLines(vector<vector<int>> &lines, int maxVal) {
        SegTreeNode *segTree = buildSegTree(0, maxVal);
        int lineIdx = 0;
        while (lineIdx < lines.size()) {
            int currX = lines[lineIdx][0];
            while (lineIdx < lines.size() && lines[lineIdx][0] == currX) {
                modifySeg(segTree, lines[lineIdx][2], lines[lineIdx][3] - 1, lines[lineIdx][1]);
                lineIdx++;
            }
            if (lineIdx < lines.size()) {
                if (segTree->minCov != 1 || segTree->maxCov != 1) {
                    freeSegTree(segTree);
                    return false;
                }
            } else {
                if (segTree->minCov != 0 || segTree->maxCov != 0) {
                    freeSegTree(segTree);
                    return false;
                }
            }
        }
        freeSegTree(segTree);
        return true;
    }
    
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        // first judge whether sum of areas equals to total area
        // then try to find overlaps using sweep-line with segment tree
        int rectNum = rectangles.size();
        
        set<int> xSet, ySet;
        unordered_map<int, int> newX, newY;
        
        for (int i = 0; i < rectNum; i++) {
            xSet.insert(rectangles[i][0]);
            xSet.insert(rectangles[i][2]);
            ySet.insert(rectangles[i][1]);
            ySet.insert(rectangles[i][3]);
        }
        
        int xIdx = 0, yIdx = 0;
        for (auto itr = xSet.begin(); itr != xSet.end(); ++itr) newX[*itr] = xIdx++;
        for (auto itr = ySet.begin(); itr != ySet.end(); ++itr) newY[*itr] = yIdx++;
        
        for (int i = 0; i < rectNum; i++) {
            int lowX = rectangles[i][0], highX = rectangles[i][2],
                lowY = rectangles[i][1], highY = rectangles[i][3];
            // y, beg/end, x1, x2
            hLines.push_back(vector<int>{newY[lowY], 1, newX[lowX], newX[highX]});
            hLines.push_back(vector<int>{newY[highY], -1, newX[lowX], newX[highX]});
            vLines.push_back(vector<int>{newX[lowX], 1, newY[lowY], newY[highY]});
            vLines.push_back(vector<int>{newX[highX], -1, newY[lowY], newY[highY]});
        }
        sort(hLines.begin(), hLines.end());
        sort(vLines.begin(), vLines.end());
        
        // scan vLines
        bool validV = isValidLines(vLines, yIdx - 2);
        if (!validV) return false;
        // scan hLines
        bool validH = isValidLines(hLines, xIdx - 2);
        return validH;
    }
};