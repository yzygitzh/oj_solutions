/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    int maxDepth = 1;
    int result = 0;
    
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        walkNestedList(nestedList, 1);
        sumNestedList(nestedList, 1);
        return result;
    }
    
    void walkNestedList(const vector<NestedInteger>& nestedList, int depth) {
        for (auto itr = nestedList.begin(); itr != nestedList.end(); ++itr) {
            maxDepth = max(maxDepth, depth);
            if (!itr->isInteger()) {
                walkNestedList(itr->getList(), depth + 1);
            }
        }
    }
    
    void sumNestedList(vector<NestedInteger>& nestedList, int depth) {
        for (auto itr = nestedList.begin(); itr != nestedList.end(); ++itr) {
            if (!itr->isInteger()) {
                sumNestedList(itr->getList(), depth + 1);
            } else {
                result += itr->getInteger() * (maxDepth - depth + 1);
            }
        }
    }
};