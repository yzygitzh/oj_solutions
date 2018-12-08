class Solution {
public:
    int integerReplacement(int n) {
        queue<pair<unsigned, int> > bfsQ;
        bfsQ.push(make_pair(n, 0));
        set<unsigned> visited{n};
        
        while (!bfsQ.empty()) {
            pair<unsigned, int> top = bfsQ.front();
            bfsQ.pop();
            if (top.first == 1) return top.second;
            if (top.first & 1) {
                if (!visited.count(top.first + 1)) {
                    visited.insert(top.first + 1);
                    bfsQ.push(make_pair(top.first + 1, top.second + 1));
                }
                if (!visited.count(top.first - 1)) {
                    visited.insert(top.first - 1);
                    bfsQ.push(make_pair(top.first - 1, top.second + 1));
                }
            } else {
                if (!visited.count(top.first >> 1)) {
                    visited.insert(top.first >> 1);
                    bfsQ.push(make_pair(top.first >> 1, top.second + 1));
                }
            }
        }
    }
};