/*
// Definition for a Node.
class Node {
public:
    int val = NULL;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
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
    // left-children right-sibling
    
    // Encodes an n-ary tree to a binary tree.
    TreeNode* encode(Node* root) {
        if (root == nullptr) return nullptr;
        TreeNode *result = new TreeNode(root->val);
        TreeNode *p = result;
        for (auto itr = root->children.begin();
             itr != root->children.end(); ++itr) {
            if (p == result) {
                p->left = encode(*itr);
                p = p->left;
            } else {
                p->right = encode(*itr);
                p = p->right;
            }
        }
        return result;
    }

    // Decodes your binary tree to an n-ary tree.
    Node* decode(TreeNode* root) {
        if (root == nullptr) return nullptr;
        Node *result = new Node(root->val);
        TreeNode *p = root->left;
        while (p != nullptr) {
            result->children.push_back(decode(p));
            p = p->right;
        }
        return result;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(root));