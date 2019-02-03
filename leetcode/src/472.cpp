class Solution {
public:
    class TrieNode {
    public:
        TrieNode *next[26];
        bool isEnd;
        TrieNode() {
            for (int i = 0; i < 26; i++) next[i] = nullptr;
            isEnd = false;
        }
    };
    
    TrieNode *trieRoot = nullptr;
    vector<string> result;
    
    void insertWord(string word) {
        if (trieRoot == nullptr) trieRoot = new TrieNode();
        TrieNode *p = trieRoot;
        for (auto itr = word.begin(); itr != word.end(); ++itr) {
            if (p->next[*itr - 'a'] == nullptr) {
                p->next[*itr - 'a'] = new TrieNode();
            }
            p = p->next[*itr - 'a'];
        }
        p->isEnd = true;
    }
    
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        for (auto itr = words.begin(); itr != words.end(); ++itr) {
            insertWord(*itr);
        }
        for (auto itr = words.begin(); itr != words.end(); ++itr) {
            int wordLen = itr->length();
            vector<int> maxCut(wordLen + 1, 0);
            for (int i = 0; i < wordLen; i++) {
                if (i > 0 && maxCut[i] == 0) continue;
                TrieNode *p = trieRoot;
                // find whether the string starting from i can be a word
                int idx = i;
                while (idx < wordLen && p->next[(*itr)[idx] - 'a'] != nullptr) {
                    p = p->next[(*itr)[idx] - 'a'];
                    idx++;
                    if (p->isEnd) {
                        maxCut[idx] = max(maxCut[idx], maxCut[i] + 1);
                    }
                }
            }
            if (maxCut[wordLen] > 1) result.push_back(*itr);
        }
        return result;
    }
};