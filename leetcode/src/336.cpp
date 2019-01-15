class Solution {
public:
    class TrieNode {
    public:
        TrieNode *next[26];
        int idx;
        TrieNode() {
            for (int i = 0; i < 26; i++) next[i] = nullptr;
            idx = -1;
        }
    };
    
    void insertWord(string word, int idx, TrieNode *trieRoot) {
        int wordLen = word.length();
        TrieNode *p = trieRoot;
        for (int i = 0; i < wordLen; i++) {
            if (p->next[word[i] - 'a'] == nullptr) {
                p->next[word[i] - 'a'] = new TrieNode();
            }
            p = p->next[word[i] - 'a'];
        }
        p->idx = idx;
    }
    
    void freeTrie(TrieNode *trieRoot) {
        if (trieRoot == nullptr) return;
        for (int i = 0; i < 26; i++) {
            freeTrie(trieRoot->next[i]);
        }
        delete trieRoot;
    }
    
    bool isPalin(string word) {
        int wordLen = word.length();
        for (int i = 0; i < (wordLen + 1) / 2; i++) {
            if (word[i] != word[wordLen - 1 - i]) return false;
        }
        return true;
    }
    
    vector<vector<int>> palindromePairs(vector<string>& words) {
        TrieNode *trieRoot;
        int wordsLen = words.size();
        set<vector<int>> result;
        
        trieRoot = new TrieNode();
        calcPalindromePairs(words, trieRoot, result, false);
        freeTrie(trieRoot);
        
        for (int i = 0; i < wordsLen; i++) {
            reverse(words[i].begin(), words[i].end());
        }
        trieRoot = new TrieNode();
        calcPalindromePairs(words, trieRoot, result, true);
        freeTrie(trieRoot);
        
        return vector<vector<int>>(result.begin(), result.end());
    }
    
    void calcPalindromePairs(vector<string>& words,
                             TrieNode *trieRoot,
                             set<vector<int>>& result,
                             bool reversed) {
        // use trie to store all word reverse
        int wordsLen = words.size();
        for (int i = 0; i < wordsLen; i++) {
            string reverseWord = words[i];
            reverse(reverseWord.begin(), reverseWord.end());
            insertWord(reverseWord, i, trieRoot);
        }
        
        // for each word, find it's prefix in trie
        // only find len(word) > len(trie match) cases
        for (int i = 0; i < wordsLen; i++) {
            string word = words[i];
            int wordLen = word.length();
            
            string trieStr;
            TrieNode *p = trieRoot;
            // check empty trieStr
            if (p->idx >= 0) {
                if (i != p->idx && isPalin(word)) {
                    if (!reversed) result.insert(vector<int>{i, p->idx});
                    else result.insert(vector<int>{p->idx, i});
                }
            }
            for (int j = 0; j < wordLen; j++) {
                // try match
                if (p->next[word[j] - 'a'] != nullptr) {
                    trieStr += word[j];
                    p = p->next[word[j] - 'a'];
                } else {
                    // no match of word in trie
                    break;
                }
                if (p->idx >= 0) {
                    string reverseTrieStr = trieStr;
                    reverse(reverseTrieStr.begin(), reverseTrieStr.end());
                    if (i != p->idx && isPalin(word + reverseTrieStr)) {
                        if (!reversed) result.insert(vector<int>{i, p->idx});
                        else result.insert(vector<int>{p->idx, i});
                    }
                }
            }
        }
    }
};