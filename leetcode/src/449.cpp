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
    // 1,,-1,,,  use preorder traversal

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string result;
        TreeNode *tmp;
        while (root != nullptr) {
            if (root->left != nullptr) {
                tmp = root->left;
                while (tmp->right != nullptr && tmp->right != root) {
                    tmp = tmp->right;
                }
                if (tmp->right == nullptr) {
                    result += to_string(root->val);
                    result += ',';
                    tmp->right = root;
                    root = root->left;
                } else {
                    result += ',';
                    tmp->right = nullptr;
                    root = root->right;
                }
            } else {
                result += to_string(root->val);
                result += ",,";
                root = root->right;
            }
        }
        result += ',';
        return result;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<TreeNode*> nodeStack;
        vector<int> fillStack;
        int idx = 0, dataLen = data.length();
        while (idx < dataLen) {
            int oldIdx = idx;
            while (idx < dataLen && data[idx] != ',') idx++;
            if (oldIdx == idx) {
                // nullptr
                if (fillStack.size() > 0) {
                    (*fillStack.rbegin())++;
                    while (fillStack.size() > 1 && *fillStack.rbegin() == 2) {
                        fillStack.pop_back();
                        TreeNode *p = *nodeStack.rbegin();
                        nodeStack.pop_back();
                        if (*fillStack.rbegin() == 0) {
                            (*nodeStack.rbegin())->left = p;
                        } else {
                            (*nodeStack.rbegin())->right = p;
                        }
                        (*fillStack.rbegin())++;
                    }
                }
            } else {
                int val = atoi(data.substr(oldIdx, idx - oldIdx).c_str());
                nodeStack.push_back(new TreeNode(val));
                fillStack.push_back(0);
            }
            idx++;
        }
        return nodeStack.size() == 0 ? nullptr : *nodeStack.begin();
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));