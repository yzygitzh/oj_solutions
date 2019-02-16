/*
 * LeetCode 307 Range Sum Query - Mutable
 * Segment Tree
 */
class NumArray {
public:
  class SegNode {
  public:
    int left, right, sum;
    SegNode *leftChild, *rightChild;
    SegNode(int _left, int _right, int _sum)
      : left(_left), right(_right), sum(_sum),
        leftChild(nullptr), rightChild(nullptr) {}
  };

  SegNode *segRoot = nullptr;
  
  SegNode* buildSeg(vector<int>& nums, int left, int right) {
    if (left == right) {
      return new SegNode(left, right, nums[left]);
    } else {
      int mid = (left + right) / 2;
      SegNode *result = new SegNode(left, right, 0);
      result->leftChild = buildSeg(nums, left, mid);
      result->rightChild = buildSeg(nums, mid + 1, right);
      result->sum = result->leftChild->sum + result->rightChild->sum;
      return result;
    }
  }

  void updateSeg(SegNode *p, int i, int val) {
    if (p->left == p->right && p->left == i) {
      p->sum = val;
    } else {
      int mid = (p->left + p->right) / 2;
      if (i <= mid) updateSeg(p->leftChild, i, val);
      else updateSeg(p->rightChild, i, val);
      p->sum = p->leftChild->sum + p->rightChild->sum;
    }
  }

  int segRange(SegNode *p, int left, int right) {
    if (p->left == left && p->right == right) {
      return p->sum;
    } else {
      int mid = (p->left + p->right) / 2;
      int result = 0;
      if (left <= mid) {
        result += segRange(p->leftChild, left, min(mid, right));
      }
      if (right >= mid + 1) {
        result += segRange(p->rightChild, max(mid + 1, left), right);
      }
      return result;
    }
  }

  NumArray(vector<int> nums) {
    if (nums.size() == 0) return;
    segRoot = buildSeg(nums, 0, nums.size() - 1);
  }
    
  void update(int i, int val) {
    updateSeg(segRoot, i, val);
  }
    
  int sumRange(int i, int j) {
    return segRange(segRoot, i, j);
  }
};
