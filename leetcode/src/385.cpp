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
    NestedInteger deserialize(string s) {
        // nested = [nested]|nested,nested|[0-9]+
        // use stack
        vector<NestedInteger> nStack;
        int sLen = s.length();
        int idx = 0, sign = 1;
        while (idx < sLen) {
            if (s[idx] == '[') {
                // open a new list
                nStack.push_back(NestedInteger());
            } else if (s[idx] == ',' || s[idx] == ']') {
                // add stack top to nested list, if something pushed since last [
                if (s[idx - 1] != '[') {
                    NestedInteger top = *nStack.rbegin();
                    nStack.pop_back();
                    nStack.rbegin()->add(top);
                }
            } else if (s[idx] == '-') {
                sign = -1;
            } else {
                // add a number to stack top
                int currNum = 0;
                while (idx < sLen && s[idx] >= '0' && s[idx] <= '9') {
                    currNum *= 10;
                    currNum += s[idx] - '0';
                    idx++;
                }
                idx--;
                nStack.push_back(NestedInteger(sign * currNum));
                sign = 1;
            }
            idx++;
        }
        return *nStack.begin();
    }
};