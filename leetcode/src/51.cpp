class Solution {
public:
    vector<vector<string> > result;
    vector<string> partResult;
    vector<pair<int, int> > occupied;
    
    vector<vector<string>> solveNQueens(int n) {
        if (n <= 0) return result;
        DFS(0, n);
        return result;
    }
    
    bool isConflict(pair<int, int> a, pair<int, int> b) {
        return a.first == b.first ||
               a.second == b.second ||
               a.first + a.second == b.first + b.second ||
               a.first - b.first == a.second - b.second;
    }
    
    void DFS(int row, int n) {
        if (row == n) {
            result.push_back(partResult);
        } else {
            for (int i = 0; i < n; i++) {
                pair<int, int> tryPnt = make_pair(row, i);
                bool validPos = true;
                for (vector<pair<int, int> > ::iterator itr =
                     occupied.begin(); itr != occupied.end(); ++itr) {
                    validPos &= !isConflict(tryPnt, *itr); 
                }
                if (validPos) {
                    occupied.push_back(tryPnt);
                    string rowStr(n, '.');
                    rowStr[i] = 'Q';
                    partResult.push_back(rowStr);
                    DFS(row + 1, n);
                    partResult.pop_back();
                    occupied.pop_back();
                }
            }
        }
    }
};