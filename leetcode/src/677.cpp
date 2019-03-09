class MapSum {
public:
    class TrieNode {
    public:
        unordered_map<char, TrieNode*> next;
        int count;
        TrieNode(): count(0) {}
    };
    
    TrieNode *trieRoot = nullptr;
    unordered_map<string, int> kv;
    
    void insertWord(string& word, int delta) {
        if (trieRoot == nullptr) trieRoot = new TrieNode();
        TrieNode *p = trieRoot;
        p->count += delta;
        for (auto c : word) {
            if (!p->next.count(c)) {
                p->next[c] = new TrieNode();
            }
            p = p->next[c];
            p->count += delta;
        }
    }
    
    int getPrefixCnt(string& prefix) {
        TrieNode *p = trieRoot;
        for (auto c : prefix) {
            if (!p->next.count(c)) {
                return 0;
            }
            p = p->next[c];
        }
        return p->count;
    }
    
    /** Initialize your data structure here. */
    MapSum() {
        
    }
    
    void insert(string key, int val) {
        int delta = val - kv[key];
        kv[key] = val;
        insertWord(key, delta);
    }
    
    int sum(string prefix) {
        return getPrefixCnt(prefix);
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum obj = new MapSum();
 * obj.insert(key,val);
 * int param_2 = obj.sum(prefix);
 */