class Solution {
public:
    class TrieNode {
    public:
        TrieNode *next[26];
        TrieNode() {
            for (int i = 0; i < 26; i++) next[i] = nullptr;
        }
    };
    
    TrieNode *trieRoot = nullptr;
    int wordLen, wordNum;
    vector<vector<string>> result;
    
    void insertWord(string word) {
        if (trieRoot == nullptr) trieRoot = new TrieNode();
        TrieNode *p = trieRoot;
        for (auto itr = word.begin(); itr != word.end(); ++itr) {
            if (p->next[*itr - 'a'] == nullptr) {
                p->next[*itr - 'a'] = new TrieNode();
            }
            p = p->next[*itr - 'a'];
        }
    }
    
    bool checkResult(vector<string>& partResult) {
        int resultLen = partResult.size();
        // check whether newly added word is valid
        for (int i = 0; i + 1 < resultLen; i++) {
            if (partResult[i][resultLen - 1] !=
                partResult[resultLen - 1][i]) return false;
        }
        // check whether uncomplete prefix exists in trie
        for (int i = resultLen; i < wordLen; i++) {
            TrieNode *p = trieRoot;
            for (int j = 0; j < resultLen; j++) {
                if (p->next[partResult[j][i] - 'a'] == nullptr) return false;
                p = p->next[partResult[j][i] - 'a'];
            }
        }
        return true;
    }
    
    void dfs(vector<string>& partResult, vector<string>& words) {
        if (partResult.size() == wordLen) {
            result.push_back(partResult);
        } else {
            for (int i = 0; i < wordNum; i++) {
                partResult.push_back(words[i]);
                if (checkResult(partResult)) {
                    dfs(partResult, words);
                }
                partResult.pop_back();
            }
        }
    }
    
    vector<vector<string>> wordSquares(vector<string>& words) {
        wordNum = words.size();
        wordLen = words[0].length();
        for (auto itr = words.begin(); itr != words.end(); ++itr) {
            insertWord(*itr);
        }
        vector<string> partResult;
        dfs(partResult, words);
        return result;
    }
};