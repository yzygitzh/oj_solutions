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
    class NodeInfo {
    public:
        int depth, val;
        NodeInfo(int _depth, int _val): depth(_depth), val(_val) {}
    };
    
    vector<NodeInfo> parseS(string S) {
        // S cannot be empty
        int SLen = S.length(), idx = 0;
        vector<NodeInfo> result;
        while (idx < SLen) {
            int depth = 0, val = 0;
            while (S[idx] == '-') {
                depth++;
                idx++;
            }
            while (idx < SLen && '0' <= S[idx] && '9' >= S[idx]) {
                val *= 10;
                val += S[idx] - '0';
                idx++;
            }
            result.push_back(NodeInfo(depth, val));
        }
        return result;
    }
    
    TreeNode* recoverFromPreorder(string S) {
        // stack-based
        vector<NodeInfo> nodeInfos = parseS(S);
        int nodeNum = nodeInfos.size();
        vector<NodeInfo> nodeInfoStack;
        vector<TreeNode*> nodeStack;
        nodeInfoStack.push_back(nodeInfos[0]);
        nodeStack.push_back(new TreeNode(nodeInfos[0].val));
        for (int i = 1; i < nodeNum; i++) {
            while (nodeInfoStack.back().depth >= nodeInfos[i].depth) {
                nodeInfoStack.pop_back();
                nodeStack.pop_back();
            }
            if (nodeStack.back()->left == nullptr) {
                nodeStack.back()->left = new TreeNode(nodeInfos[i].val);
                nodeStack.push_back(nodeStack.back()->left);
            } else {
                nodeStack.back()->right = new TreeNode(nodeInfos[i].val);
                nodeStack.push_back(nodeStack.back()->right);
            }
            nodeInfoStack.push_back(nodeInfos[i]);
        }
        return nodeStack[0];
    }
};