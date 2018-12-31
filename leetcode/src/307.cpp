class NumArray {
public:
    class SegTreeNode {
    public:
        int left, right, sum;
        SegTreeNode *leftChild, *rightChild;
        SegTreeNode(int _left, int _right, int _sum):
        left(_left), right(_right), sum(_sum),
        leftChild(nullptr), rightChild(nullptr) {}
    };
    
    SegTreeNode *root;
    
    NumArray(vector<int> nums): root(nullptr) {
        if (nums.size() != 0) root = buildTree(0, nums.size() - 1, nums);
    }
    
    SegTreeNode *buildTree(int left, int right, vector<int> &nums) {
        if (left == right) {
            return new SegTreeNode(left, right, nums[left]);
        } else {
            int mid = (left + right) / 2;
            SegTreeNode *leftChild = buildTree(left, mid, nums);
            SegTreeNode *rightChild = buildTree(mid + 1, right, nums);
            SegTreeNode *newNode = new SegTreeNode(left, right,
                                                   leftChild->sum + rightChild->sum);
            newNode->leftChild = leftChild;
            newNode->rightChild = rightChild;
            return newNode;
        }
    }
    
    void update(int i, int val) {
        updateSegTree(i, val, root);
    }
    
    void updateSegTree(int i, int val, SegTreeNode *node) {
        if (node->left == node->right && i == node->left) {
            node->sum = val;
        } else {
            int mid = (node->left + node->right) / 2;
            if (i <= mid) updateSegTree(i, val, node->leftChild);
            if (i >= mid + 1) updateSegTree(i, val, node->rightChild);
            node->sum = node->leftChild->sum + node->rightChild->sum;
        }
    }
    
    int sumRange(int i, int j) {
        return sumRangeSegTree(i, j, root);
    }
    
    int sumRangeSegTree(int left, int right, SegTreeNode *node) {
        if (node->left == left &&
            node->right == right) return node->sum;
        else {
            int mid = (node->left + node->right) / 2;
            if (right <= mid) return sumRangeSegTree(left, right,
                                                     node->leftChild);
            else if (left >= mid + 1) return sumRangeSegTree(left, right,
                                                             node->rightChild);
            else return sumRangeSegTree(left, mid,
                                        node->leftChild) +
                        sumRangeSegTree(mid + 1, right,
                                        node->rightChild);
        }
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */