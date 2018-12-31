/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) return "()";
        string leftStr = serialize(root->left);
        string rightStr = serialize(root->right);
        string rootStr = "(";
        rootStr += to_string(root->val) + leftStr + rightStr;
        rootStr += ")";
        return rootStr;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data[1] == ')') return nullptr;
        int left = 1, right = 2, moreLeft;
        while (data[right] != '(') right++;
        TreeNode *p = new TreeNode(atoi(data.substr(left, right - left).c_str()));
        left = right;
        right = left + 1;
        moreLeft = 1;
        while (moreLeft) {
            if (data[right] == '(') moreLeft++;
            else if (data[right] == ')') moreLeft--;
            right++;
        }
        p->left = deserialize(data.substr(left, right - left));
        left = right;
        right = left + 1;
        moreLeft = 1;
        while (moreLeft) {
            if (data[right] == '(') moreLeft++;
            else if (data[right] == ')') moreLeft--;
            right++;
        }
        p->right = deserialize(data.substr(left, right - left));
        return p;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));