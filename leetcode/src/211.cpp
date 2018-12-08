class WordDictionary {
public:
    class TrieNode {
    public:
        TrieNode *next[26];
        bool isWord;
        TrieNode() {
            for (int i = 0; i < 26; i++) next[i] = nullptr;
            isWord = false;
        }
    };
    TrieNode *trieRoot = nullptr;
    
    /** Initialize your data structure here. */
    WordDictionary() {
        trieRoot = new TrieNode();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNode *currP = trieRoot;
        int wordLen = word.length();
        for (int i = 0; i < wordLen; i++) {
            if (currP->next[word[i] - 'a'] == nullptr) {
                currP->next[word[i] - 'a'] = new TrieNode();
            }
            currP = currP->next[word[i] - 'a'];
        }
        currP->isWord = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return searchTrie(word, trieRoot);
    }
    
    bool searchTrie(string word, TrieNode *p) {
        if (p == nullptr) {
            return false;
        } else if (word.length() == 0) {
            return p->isWord;
        } else {
            if (word[0] == '.') {
                for (int i = 0; i < 26; i++) {
                    if (searchTrie(word.substr(1), p->next[i])) return true;
                }
                return false;
            } else {
                return searchTrie(word.substr(1), p->next[word[0] - 'a']);
            }
        }
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */