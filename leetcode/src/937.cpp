struct CustomLess {
    bool operator() (const string &a, const string &b) const {
        int spaceIdxA = 0;
        while (a[spaceIdxA] != ' ') spaceIdxA++;
        int spaceIdxB = 0;
        while (b[spaceIdxB] != ' ') spaceIdxB++;
        if (a.substr(spaceIdxA + 1) != b.substr(spaceIdxB + 1)) {
            return a.substr(spaceIdxA + 1) < b.substr(spaceIdxB + 1);
        } else {
            return a.substr(0, spaceIdxA) < b.substr(0, spaceIdxB);
        }
    }
};

class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<string> letterLogs;
        vector<string> digitLogs;
        for (vector<string>::iterator itr = logs.begin();
             itr != logs.end(); ++itr) {
            int spaceIdx = 0;
            while ((*itr)[spaceIdx] != ' ') spaceIdx++;
            if ('0' <= (*itr)[spaceIdx + 1] && '9' >= (*itr)[spaceIdx + 1]) {
                digitLogs.push_back(*itr);
            } else {
                letterLogs.push_back(*itr);
            }
        }
        sort(letterLogs.begin(), letterLogs.end(), CustomLess());
        letterLogs.insert(letterLogs.end(), digitLogs.begin(), digitLogs.end());
        return letterLogs;
    }
};