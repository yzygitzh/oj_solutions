/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
public:
    class StackElem {
    public:
        const vector<NestedInteger> &list;
        vector<NestedInteger>::iterator itr;
        StackElem (vector<NestedInteger> &_list,
                   vector<NestedInteger>::iterator _itr): list(_list), itr(_itr) {}
    };
    vector<StackElem> nodeStack;
    
    NestedIterator(vector<NestedInteger> &nestedList) {
        nodeStack.push_back(StackElem(nestedList, nestedList.begin()));
        moveToNext();
    }

    int next() {
        int stackIdx = nodeStack.size() - 1;
        int result = nodeStack[stackIdx].itr->getInteger();
        ++nodeStack[stackIdx].itr;
        moveToNext();
        return result;
    }

    bool hasNext() {
        return nodeStack.size() > 0;
    }
    
    void moveToNext() {
        while (nodeStack.size() > 0) {
            int stackIdx = nodeStack.size() - 1;
            if (nodeStack[stackIdx].itr == nodeStack[stackIdx].list.end()) {
                // top list has been explored
                nodeStack.pop_back();
                if (nodeStack.size() > 0) ++nodeStack[stackIdx - 1].itr;
            } else if (!(nodeStack[stackIdx].itr->isInteger())) {
                // next element is a list
                vector<NestedInteger> &nextList = nodeStack[stackIdx].itr->getList();
                nodeStack.push_back(StackElem(nextList, nextList.begin()));
            } else {
                // next element is an integer
                break;
            }
        }
        // invariant: any node in stack has been explored until node.itr
        // and node.itr points to an integer.
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */