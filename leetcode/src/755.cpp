class Solution {
public:
    class StackElem {
    public:
        int height, start, end;
        StackElem (int height_, int start_, int end_): height(height_), start(start_), end(end_) {}
    };
    
    // stack is mono decrease (last element is strict mono decrease), stack bottom < heights[K]
    void growStack(vector<StackElem>& heightStack, int delta, vector<int>& heights, int K) {
        int idx = K;
        if (!heightStack.empty()) {
            idx = heightStack.back().end;
        }
        while (idx + delta >= 0 && idx + delta < heights.size()) {
            if (heights[idx + delta] == heights[idx]) {
                if (!heightStack.empty()) {
                    heightStack.back().end += delta;
                } else {
                    heightStack.push_back(StackElem(heights[idx + delta], idx + delta, idx + delta));
                }
            } else if (heights[idx + delta] < heights[idx]) {
                heightStack.push_back(StackElem(heights[idx + delta], idx + delta, idx + delta));
            } else {
                break;
            }
            idx += delta;
        }
    }
    
    bool placeDrop(vector<StackElem>& heightStack, int delta, vector<int>& heights, int K) {
        if (heightStack.empty() || heightStack.back().height == heights[K]) {
            return false;
        }
        StackElem top = heightStack.back();
        heightStack.pop_back();
        if (!heightStack.empty() && heightStack.back().height == top.height + 1) {
            heightStack.back().end += delta;
        } else {
            heightStack.push_back(StackElem(top.height + 1, top.start, top.start));
        }
        heights[top.start]++;
        if (top.start != top.end) {
            top.start += delta;
            heightStack.push_back(top);
        }
        return true;
    }
    
    vector<int> pourWater(vector<int>& heights, int V, int K) {
        vector<StackElem> leftStack, rightStack;
        while (V) {
            growStack(leftStack, -1, heights, K);
            growStack(rightStack, 1, heights, K);
            if (!placeDrop(leftStack, -1, heights, K) &&
                !placeDrop(rightStack, 1, heights, K)) {
                heights[K]++;
            }
            V--;
        }
        return heights;
    }
};