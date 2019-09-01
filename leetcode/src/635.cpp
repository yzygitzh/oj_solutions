class LogSystem {
public:
    class TrieNode {
    public:
        TrieNode* next[10];
        vector<int> logIds;
        TrieNode() {
            for (int i = 0; i < 10; i++) {
                next[i] = nullptr;
            }
        }
    };
    
    TrieNode* trieRoot;
    unordered_map<string, int> graToPrefixLen;
    
    LogSystem() {
        trieRoot = new TrieNode();
        graToPrefixLen["Year"] = 4;
        graToPrefixLen["Month"] = 6;
        graToPrefixLen["Day"] = 8;
        graToPrefixLen["Hour"] = 10;
        graToPrefixLen["Minute"] = 12;
        graToPrefixLen["Second"] = 14;
    }
    
    void put(int id, string timestamp) {
        TrieNode* p = trieRoot;
        for (auto c : timestamp) {
            if (c == ':') {
                continue;
            }
            if (p->next[c - '0'] == nullptr) {
                p->next[c - '0'] = new TrieNode();
            }
            p = p->next[c - '0'];
        }
        p->logIds.push_back(id);
    }
    
    vector<int> retrieve(string s, string e, string gra) {
        vector<int> result;
        walkTrieNode(trieRoot, 0, graToPrefixLen[gra], s, e, result, true, true);
        return result;
    }
    
    void walkTrieNode(TrieNode* p,
                      int currPrefix, int graPrefix,
                      string& s, string& e,
                      vector<int>& result,
                      bool lowerBound, bool upperBound) {
        if (p == nullptr) {
            return;
        }
        if (currPrefix == 19) {
            for (auto logId : p->logIds) {
                result.push_back(logId);
            }
            return;
        }
        if (s[currPrefix] == ':') {
            currPrefix++;
            graPrefix++;
        }
        for (int i = 0; i < 10; i++) {
            if (p->next[i] != nullptr &&
                (currPrefix >= graPrefix ||
                 (!lowerBound || s[currPrefix] - '0' <= i) &&
                 (!upperBound || e[currPrefix] - '0' >= i))) {
                walkTrieNode(p->next[i], currPrefix + 1, graPrefix,
                             s, e, result,
                             lowerBound && s[currPrefix] - '0' == i,
                             upperBound && e[currPrefix] - '0' == i);
            }
        }
    }
};

/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem* obj = new LogSystem();
 * obj->put(id,timestamp);
 * vector<int> param_2 = obj->retrieve(s,e,gra);
 */