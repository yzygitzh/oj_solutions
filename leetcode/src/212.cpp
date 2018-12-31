class Solution {
public:
    class TrieNode {
    public:
        TrieNode *next[26];
        bool isEnd, visited;
        TrieNode() {
            for (int i = 0; i < 26; i++) {
                next[i] = nullptr;
            }
            isEnd = false;
            visited = false;
        }
    };
    
    TrieNode *trieRoot;
    
    void insertWord(string word) {
        if (trieRoot == nullptr) trieRoot = new TrieNode();
        TrieNode *p = trieRoot;
        int wordLen = word.length();
        for (int i = 0; i < wordLen; i++) {
            if (p->next[word[i] - 'a'] == nullptr) {
                p->next[word[i] - 'a'] = new TrieNode();
            }
            p = p->next[word[i] - 'a'];
        }
        p->isEnd = true;
    }
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        
        int m = board.size();
        if (m == 0) return result;
        int n = board[0].size();
        if (n == 0) return result;
        int wordsLen = words.size();
        if (wordsLen == 0) return result;
        
        for (int i = 0; i < wordsLen; i++) insertWord(words[i]);
        
        string partResult;
        vector<vector<int> > visited(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                searchTrie(i, j, partResult, result, visited, board, trieRoot);
            }
        }
        return result;
    }
    
    void searchTrie(int row, int col,
                    string &partResult, vector<string> &result,
                    vector<vector<int> >& visited,
                    vector<vector<char>>& board, TrieNode *p) {
        if (p->isEnd && !p->visited) {
            p->visited = true;
            result.push_back(partResult);
        }
        
        int m = board.size();
        int n = board[0].size();

        if (row < 0 || row >= m || col < 0 || col >= n) return;

        if (!visited[row][col] && p->next[board[row][col] - 'a'] != nullptr) {
            visited[row][col] = 1;
            partResult += board[row][col];
            // up
            searchTrie(row - 1, col, partResult, result, visited,
                       board, p->next[board[row][col] - 'a']);
            // down
            searchTrie(row + 1, col, partResult, result, visited,
                       board, p->next[board[row][col] - 'a']);
            // left
            searchTrie(row, col - 1, partResult, result, visited,
                       board, p->next[board[row][col] - 'a']);
            // right
            searchTrie(row, col + 1, partResult, result, visited,
                       board, p->next[board[row][col] - 'a']);
            partResult.pop_back();
            visited[row][col] = 0;
        }
    }
};