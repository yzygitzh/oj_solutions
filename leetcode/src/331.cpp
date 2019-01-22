class Solution {
public:
    bool isValidSerialization(string preorder) {
        int capacity = 1;
        preorder += ',';
        int idx = 0;
        int preorderLen = preorder.length();
        while (idx < preorderLen) {
            while (preorder[idx] != ',') {
                idx++;
            }
            if (preorder[idx - 1] == '#') {
                capacity--;
                if (capacity < 0) return false;
            } else {
                capacity--;
                if (capacity < 0) return false;
                capacity += 2;
            }
            idx++;
        }
        return capacity == 0;
    }
};