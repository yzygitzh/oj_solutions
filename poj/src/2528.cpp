/*
 * POJ 2528 - Mayor's posters
 *
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <string>
#include <map>
#include <cmath>

using namespace std;

class SegTreeNode {
public:
    int val, left, right;
    SegTreeNode *leftChild, *rightChild;
    bool valid;
    SegTreeNode(int _left, int _right)
        : val(-1), left(_left), right(_right),
          leftChild(NULL), rightChild(NULL), valid(true) {}
};

SegTreeNode* buildSegTree(int left, int right) {
    if (left == right) {
        return new SegTreeNode(left, right);
    } else {
        SegTreeNode* root = new SegTreeNode(left, right);
        int mid = left + (right - left) / 2;
        root->leftChild = buildSegTree(left, mid);
        root->rightChild = buildSegTree(mid + 1, right);
        return root;
    }
}

void freeSegTree(SegTreeNode *root) {
    if (root == NULL) return;
    freeSegTree(root->leftChild);
    freeSegTree(root->rightChild);
    delete root;
}

void updateSeg(SegTreeNode *root, int left, int right, int newVal) {
    if (root->left == left && root->right == right) {
        root->valid = true;
        root->val = newVal;
    } else {
        int mid = root->left + (root->right - root->left) / 2;
        if (root->valid) {
            updateSeg(root->leftChild, root->left, mid, root->val);
            updateSeg(root->rightChild, mid + 1, root->right, root->val);
            root->valid = false;
        }
        if (left <= mid) {
            updateSeg(root->leftChild, left, min(right, mid), newVal);
        }
        if (right >= mid + 1) {
            updateSeg(root->rightChild, max(mid + 1, left), right, newVal);
        }
    }
}

int querySeg(SegTreeNode* root, int pos) {
    if (root->valid) {
        return root->val;
    } else {
        int mid = root->left + (root->right - root->left) / 2;
        if (pos <= mid) {
            return querySeg(root->leftChild, pos);
        } else {
            return querySeg(root->rightChild, pos);
        }
    }
}

int main() {
    // TODO: test multiple test cases
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--) {
        int postNum;
        scanf("%d", &postNum);
        int maxId = -1;
        map<int, int> posToId;
        vector<pair<int, int> > posters;
        for (int i = 0; i < postNum; i++) {
            int leftVal, rightVal;
            scanf("%d%d", &leftVal, &rightVal);
            posters.push_back(make_pair(leftVal, rightVal));
            posToId[leftVal] = posToId[rightVal] = 0;
        }
        for (map<int, int>::iterator itr = posToId.begin();
             itr != posToId.end(); ++itr) {
            itr->second = ++maxId;
        }
        for (int i = 0; i < postNum; i++) {
            posters[i].first = posToId[posters[i].first];
            posters[i].second = posToId[posters[i].second];
        }
        SegTreeNode *segRoot = buildSegTree(0, maxId);
        for (int i = 0; i < postNum; i++) {
            updateSeg(segRoot, posters[i].first, posters[i].second, i);
        }
        set<int> posterCnt;
        for (int i = 0; i <= maxId; i++) {
            int posterId = querySeg(segRoot, i);
            if (posterId >= 0) {
                posterCnt.insert(posterId);
            }
        }
        cout << posterCnt.size() << endl;
        freeSegTree(segRoot);
    }
    return 0;
}

