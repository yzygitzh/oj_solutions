class NumArray {
public:
    class SegNode {
    public:
        int left, right, sum;
        SegNode* leftChild, *rightChild;
        SegNode(int _left, int _right)
            : left(_left), right(_right), sum(0),
              leftChild(nullptr), rightChild(nullptr) {}
    };
    
    SegNode *segRoot;
    
    SegNode *buildSeg(int left, int right, vector<int>& nums) {
        SegNode *result = new SegNode(left, right);
        if (left == right) {
            result->sum = nums[left];
        } else {
            int mid = left + (right - left) / 2;
            result->leftChild = buildSeg(left, mid, nums);
            result->rightChild = buildSeg(mid + 1, right, nums);
            result->sum = result->leftChild->sum + result->rightChild->sum;
        }
        return result;
    }
    
    void updateSeg(SegNode *p, int idx, int val) {
        if (p->left == p->right && p->left == idx) {
            p->sum = val;
        } else {
            int mid = p->left + (p->right - p->left) / 2;
            if (idx <= mid) updateSeg(p->leftChild, idx, val);
            else updateSeg(p->rightChild, idx, val);
            p->sum = p->leftChild->sum + p->rightChild->sum;
        }
    }
    
    int querySeg(SegNode *p, int left, int right) {
        if (left == p->left && right == p->right) {
            return p->sum;
        } else {
            int mid = p->left + (p->right - p->left) / 2;
            int result = 0;
            if (left <= mid) {
                result += querySeg(p->leftChild, left, min(mid, right));
            }
            if (right >= mid + 1) {
                result += querySeg(p->rightChild, max(mid + 1, left), right);
            }
            return result;
        }
    }
    
    NumArray(vector<int>& nums) {
        if (nums.size() == 0) {
            segRoot = nullptr;
        } else {
            segRoot = buildSeg(0, nums.size() - 1, nums);
        }
    }
    
    void update(int i, int val) {
        if (segRoot != nullptr) {
            updateSeg(segRoot, i, val);
        }
    }
    
    int sumRange(int i, int j) {
        if (segRoot == nullptr) {
            return 0;
        } else {
            return querySeg(segRoot, i, j);
        }
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */