/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int countNodes(TreeNode* root) {
        // return int: node number <= 2^31 - 1, i.e. leftLen <= 31
        int leftLen = 0, rightLen = 0;
        unsigned leftPath = 0, rightPath = 0;
        TreeNode *p;
        
        p = root;
        while (p != NULL) {
            p = p->left;
            leftLen++;
        }
        
        p = root;
        while (p != NULL) {
            rightPath |= (1 << rightLen);
            rightLen++;
            p = p->right;
        }
        
        if (leftLen == rightLen) return (1U << leftLen) - 1U;
        
        // bin search last level
        // leftLen >= 2, leftLen > rightLen, rightLen < 31
        // 0 <= leftPath, rightPath <= 0x7FFF, (0x7FFF << 1) == 0xFFFE
        while (leftPath + 1 < rightPath) {
            // loop invariant: rightPath leads to NULL, leftPath leads to non-NULL
            unsigned midPath = (leftPath + rightPath) / 2;
            // follow midPath
            p = root;
            for (int i = 0; i < rightLen; i++) {
                if (midPath & (1U << (rightLen - i - 1))) p = p-> right;
                else p = p->left;
            }
            if (p == NULL) {
                rightPath = midPath;
            } else {
                leftPath = midPath;
            }
        }
        
        return (1U << rightLen) + leftPath;
    }
};