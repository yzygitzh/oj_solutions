class Solution {
public:
    int findBlackPixel(vector<vector<char>>& picture, int N) {
        int m = picture.size(), n = picture[0].size();
        vector<int> rowCnt(m, 0), colCnt(n, 0);
        map<string, vector<int>> rowStrCnt;
        for (int i = 0; i < m; i++) {
            string rowStr;
            for (int j = 0; j < n; j++) {
                rowStr += picture[i][j];
                if (picture[i][j] == 'B') {
                    rowCnt[i]++;
                    colCnt[j]++;
                }
            }
            rowStrCnt[rowStr].push_back(i);
        }
        int result = 0;
        for (auto itr = rowStrCnt.begin(); itr != rowStrCnt.end(); ++itr) {
            if (rowCnt[itr->second[0]] == N &&
                itr->second.size() == N) {
                for (int i = 0; i < n; i++) {
                    if (itr->first[i] == 'B' && colCnt[i] == N) {
                        result += N;
                    }
                }
            }
        }
        return result;
    }
};