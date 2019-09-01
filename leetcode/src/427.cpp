/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {}

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/
class Solution {
public:
    // get four sums
    Node* construct(vector<vector<int>>& grid) {
        return construct(grid, 0, grid.size() - 1, 0, grid.size() - 1);
    }
    
    Node* construct(vector<vector<int>>& grid, int left, int right, int up, int down) {
        if (left == right) {
            return new Node(grid[left][up] == 1, true,
                            nullptr, nullptr, nullptr, nullptr);
        } else {
            int leftUp = 0, rightUp = 0, leftDown = 0, rightDown = 0;
            for (int i = left; i <= right; i++) {
                for (int j = up; j <= down; j++) {
                    if (grid[i][j] == 1) {
                        if (i <= left + (right - left) / 2 &&
                            j <= up + (down - up) / 2) leftUp++;
                        if (i <= left + (right - left) / 2 &&
                            j > up + (down - up) / 2) rightUp++;
                        if (i > left + (right - left) / 2 &&
                            j <= up + (down - up) / 2) leftDown++;
                        if (i > left + (right - left) / 2 &&
                            j > up + (down - up) / 2) rightDown++;
                    }
                }
            }
            int sum = leftUp + rightUp + leftDown + rightDown;
            int area = (right - left + 1) * (down - up + 1);
            bool isLeaf = sum == area || sum == 0;
            Node* result = new Node(sum == area, isLeaf, nullptr, nullptr, nullptr, nullptr);
            if (!isLeaf) {
                result->topLeft = construct(grid, left, left + (right - left) / 2, up, up + (down - up) / 2);
                result->topRight = construct(grid, left, left + (right - left) / 2, up + (down - up) / 2 + 1, down);
                result->bottomLeft = construct(grid, left + (right - left) / 2 + 1, right, up, up + (down - up) / 2);
                result->bottomRight = construct(grid, left + (right - left) / 2 + 1, right, up + (down - up) / 2 + 1, down);
            }
            return result;
        }
    }
};