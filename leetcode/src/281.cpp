class ZigzagIterator {
public:
    int lastIdx;
    map<int, vector<int>::iterator> itrs;
    map<int, vector<int>::iterator> endItrs;
    
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if (v1.size() > 0) {
            itrs[0] = v1.begin();
            endItrs[0] = v1.end();
        }
        if (v2.size() > 0) {
            itrs[1] = v2.begin();
            endItrs[1] = v2.end();
        }
        if (itrs.size() > 0) {
            lastIdx = itrs.begin()->first;
        }
    }

    int next() {
        int result = *itrs[lastIdx];
        ++itrs[lastIdx];
        if (itrs[lastIdx] == endItrs[lastIdx]) {
            itrs.erase(lastIdx);
            endItrs.erase(lastIdx);
        }
        auto newItr = itrs.upper_bound(lastIdx);
        if (newItr != itrs.end()) {
            lastIdx = newItr->first;
        } else if (itrs.size() > 0) {
            lastIdx = itrs.begin()->first;
        }
        return result;
    }

    bool hasNext() {
        return itrs.size() > 0;
    }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */