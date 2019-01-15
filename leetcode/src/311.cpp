class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A,
                                 vector<vector<int>>& B) {
        int dimA1 = A.size();
        int dimB1 = B.size();
        int dimB2 = B[0].size();
        
        vector<vector<pair<int, int>>> ARows(dimA1), BCols(dimB2);
        for (int i = 0; i < dimA1; i++) {
            for (int j = 0; j < dimB1; j++) {
                if (A[i][j]) ARows[i].push_back(make_pair(A[i][j], j));
            }
        }
        for (int i = 0; i < dimB2; i++) {
            for (int j = 0; j < dimB1; j++) {
                if (B[j][i]) BCols[i].push_back(make_pair(B[j][i], j));
            }
        }
        
        vector<vector<int>> result(dimA1, vector<int>(dimB2, 0));
        for (int i = 0; i < dimA1; i++) {
            for (int j = 0; j < dimB2; j++) {
                // multiply two vectors
                int idxA = 0, idxB = 0;
                while (idxA < ARows[i].size() && idxB < BCols[j].size()) {
                    if (ARows[i][idxA].second == BCols[j][idxB].second) {
                        result[i][j] += ARows[i][idxA].first *
                                        BCols[j][idxB].first;
                        idxA++;
                        idxB++;
                    } else if (ARows[i][idxA].second <
                               BCols[j][idxB].second) {
                        idxA++;
                    } else {
                        idxB++;
                    }
                }
            }
        }
        return result;
    }
};