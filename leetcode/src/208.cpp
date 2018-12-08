class Trie {
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
    TrieNode *root;
    
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        int wordLen = word.size();
        TrieNode *p = root;
        for (int i = 0; i < wordLen; i++) {
            if (p->next[word[i] - 'a'] == nullptr) {
                p->next[word[i] - 'a'] = new TrieNode();
            }
            p = p->next[word[i] - 'a'];
        }
        p->isEnd = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        int wordLen = word.size();
        TrieNode *p = root;
        for (int i = 0; i < wordLen; i++) {
            if (p->next[word[i] - 'a'] == nullptr) return false;
            p = p->next[word[i] - 'a'];
        }
        return p->isEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        int prefixLen = prefix.size();
        TrieNode *p = root;
        for (int i = 0; i < prefixLen; i++) {
            if (p->next[prefix[i] - 'a'] == nullptr) return false;
            p = p->next[prefix[i] - 'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */