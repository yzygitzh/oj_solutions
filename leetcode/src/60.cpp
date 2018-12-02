class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> visited(10, 0);
        return genPermute(n, k, visited);
    }
    
    string genPermute(int len, int k, vector<int>& visited) {
        string result;
        if (len == 1) {
            for (int i = 1; i <= 9; i++) {
                if (!visited[i])  {
                    visited[i] = 1;
                    result += '0' + i;
                    return result;
                }
            }
        } else {
            int nextLenFact = 1;
            for (int i = 1; i < len; i++) {
                nextLenFact *= i;
            }
            // decrease k until k <= nextLenFact
            for (int i = 1; i <= 9; i++) {
                if (!visited[i])  {
                    if (k <= nextLenFact) {
                        visited[i] = 1;
                        result += '0' + i;
                        return result + genPermute(len - 1, k, visited);
                    } else {
                        k -= nextLenFact;
                    }
                }
            }
        }
        return result;
    }
};