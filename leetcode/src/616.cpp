class Solution {
public:
    class TrieNode {
    public:
        unordered_map<char, TrieNode*> next;
        bool isEnd;
        TrieNode () : isEnd(false) {}
    };
    
    TrieNode *trieRoot = nullptr;
    
    void insertWord(string& word) {
        if (trieRoot == nullptr) {
            trieRoot = new TrieNode();
        }
        TrieNode *p = trieRoot;
        for (auto c : word) {
            if (p->next.find(c) == p->next.end()) {
                p->next[c] = new TrieNode();
            }
            p = p->next[c];
        }
        p->isEnd = true;
    }
    
    string addBoldTag(string s, vector<string>& dict) {
        for (string& word : dict) {
            insertWord(word);
        }
        vector<int> isBold(s.length(), 0);
        for (int i = 0; i < s.length(); i++) {
            int idx = i, maxIdx = -1;
            TrieNode *p = trieRoot;
            while (p != nullptr && idx < s.length()) {
                if (p->next.find(s[idx]) != p->next.end()) {
                    p = p->next[s[idx]];
                } else {
                    break;
                }
                if (p->isEnd) {
                    maxIdx = idx;
                }
                idx++;
            }
            for (int j = i; j <= maxIdx; j++) {
                isBold[j] = 1;
            }
        }
        string result;
        for (int i = 0; i < s.length(); i++) {
            if (isBold[i] == 0) {
                result += s[i];
            } else {
                result += "<b>";
                while (i < s.length() && isBold[i] == 1) {
                    result += s[i];
                    i++;
                }
                result += "</b>";
                i--;
            }
        }
        return result;
    }
};