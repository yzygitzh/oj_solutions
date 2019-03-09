class NumArray {
public:
    class SegTreeNode {
    public:
        int left, right, sum;
        SegTreeNode *leftChild, *rightChild;
        SegTreeNode(int _left, int _right, int _sum)
            : left(_left), right(_right), sum(_sum), leftChild(nullptr), rightChild(nullptr) {}
    };
    
    SegTreeNode *segTreeRoot = nullptr;
    
    SegTreeNode *buildSegTree(vector<int>& nums, int left, int right) {
        if (left == right) {
            return new SegTreeNode(left, right, nums[left]);
        } else {
            int mid = (left + right) / 2;
            SegTreeNode *result = new SegTreeNode(left, right, 0);
            result->leftChild = buildSegTree(nums, left, mid);
            result->rightChild = buildSegTree(nums, mid + 1, right);
            result->sum = result->leftChild->sum + result->rightChild->sum;
            return result;
        }
    }
    
    void updateTree(SegTreeNode *p, int idx, int val) {
        if (p->left == p->right && p->left == idx) {
            p->sum = val;
        } else {
            int mid = (p->left + p->right) / 2;
            if (idx <= mid) updateTree(p->leftChild, idx, val);
            else updateTree(p->rightChild, idx, val);
            p->sum = p->leftChild->sum + p->rightChild->sum;
        }
    }
    
    int rangeSumTree(SegTreeNode *p, int left, int right) {
        if (p->left == left && p->right == right) {
            return p->sum;
        } else {
            int mid = (p->left + p->right) / 2;
            int result = 0;
            if (left <= mid) result += rangeSumTree(p->leftChild, left, min(mid, right));
            if (right >= mid + 1) result += rangeSumTree(p->rightChild, max(mid + 1, left), right);
            return result;
        }
    }
    
    NumArray(vector<int> nums) {
        if (nums.size() == 0) return;
        segTreeRoot = buildSegTree(nums, 0, nums.size() - 1);
    }
    
    void update(int i, int val) {
        if (segTreeRoot == nullptr) return;
        updateTree(segTreeRoot, i, val);
    }
    
    int sumRange(int i, int j) {
        if (segTreeRoot == nullptr) return 0;
        return rangeSumTree(segTreeRoot, i, j);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */