class AutocompleteSystem {
public:
    class RankItem {
    public:
        int freq;
        string word;
        RankItem() {}
        RankItem(int freq_, string word_): freq(freq_), word(word_) {}
        bool operator< (const RankItem& i) const {
            if (freq != i.freq) {
                return freq > i.freq;
            }
            return word < i.word;
        }
    };
    
    class TrieNode {
    public:
        unordered_map<char, TrieNode*> next;
        vector<RankItem> items;
    };
    
    TrieNode* trieRoot;
    TrieNode *currP;
    unordered_map<string, int> wordFreq;
    string currWord;
    
    void insertWord(string& word, int freq) {
        wordFreq[word] += freq;
        RankItem currItem(wordFreq[word], word);
        TrieNode *p = trieRoot;
        int idx = 0;
        for (auto c : word) {
            if (p->next.find(c) == p->next.end()) {
                p->next[c] = new TrieNode();
            }
            p = p->next[c];
            
            // insert word into items if possible
            bool update = false;
            for (auto& item : p->items) {
                if (item.word == currItem.word) {
                    update = true;
                    item.freq = currItem.freq;
                    break;
                }
            }
            if (!update) {
                p->items.push_back(currItem);
            }
            sort(p->items.begin(), p->items.end());
            p->items.resize(min(3, int(p->items.size())));
        }
    }
    
    void deleteTrie(TrieNode *p) {
        if (p != nullptr) {
            for (auto& nextPair : p->next) {
                deleteTrie(nextPair.second);
            }
        }
        delete p;
    }
    
    AutocompleteSystem(vector<string>& sentences, vector<int>& times)
        : trieRoot(new TrieNode()), currP(trieRoot) {
        for (int i = 0; i < sentences.size(); i++) {
            insertWord(sentences[i], times[i]);
        }
    }
    
    ~AutocompleteSystem() {
        deleteTrie(trieRoot);
    }
    
    vector<string> input(char c) {
        vector<string> result;
        if (c == '#') {
            insertWord(currWord, 1);
            currWord = "";
            currP = trieRoot;
        } else {
            currWord += c;
            if (currP != nullptr &&
                currP->next.find(c) != currP->next.end()) {
                currP = currP->next[c];
            } else {
                currP = nullptr;
            }
            if (currP != nullptr) {
                for (auto& item : currP->items) {
                    result.push_back(item.word);
                }
            }
        }
        return result;
    }
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */