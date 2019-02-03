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
class Codec {
public:
    // 1[2,3[4,5[6]]]...
    
    // Encodes a tree to a single string.
    string serialize(Node* root) {
        string result = "";
        if (root == nullptr) return result;
        result += to_string(root->val);
        if (root->children.size() == 0) return result;
        result += "[";
        for (auto itr = root->children.begin(); itr != root->children.end(); ++itr) {
            if (itr != root->children.begin()) result += ",";
            result += serialize(*itr);
        }
        result += "]";
        return result;
    }

    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
        int dataLen = data.length();
        if (dataLen == 0) return nullptr;
        int idx = 0;
        while (idx < dataLen && data[idx] != '[') idx++;
        Node *result = new Node(atoi(data.substr(0, idx).c_str()));
        if (idx == dataLen) return result;
        // skip [
        idx++;
        while (idx < dataLen) {
            int oldIdx = idx;
            int leftBracketCnt = 0;
            while (leftBracketCnt > 0 || !(data[idx] == ',' || data[idx] == ']')) {
                if (data[idx] == '[') leftBracketCnt++;
                else if (data[idx] == ']') leftBracketCnt--;
                idx++;
            }
            result->children.push_back(deserialize(data.substr(oldIdx, idx - oldIdx)));
            idx++;
        }
        return result;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));