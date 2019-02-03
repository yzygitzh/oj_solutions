class Solution {
public:
    class TrieNode {
    public:
        TrieNode *next[26];
        TrieNode () {
            for (int i = 0; i < 26; i++) next[i] = nullptr;
        }
    };
    
    TrieNode *trieRoot;
    int strLen;
    
    void insertWord(string word) {
        if (trieRoot == nullptr) trieRoot = new TrieNode();
        TrieNode *p = trieRoot;
        for (auto itr = word.begin(); itr != word.end(); ++itr) {
            if (p->next[(*itr) - 'a'] == nullptr) {
                p->next[(*itr) - 'a'] = new TrieNode();
            }
            p = p->next[(*itr) - 'a'];
        }
    }
    
    string minAbbreviation(string target, vector<string>& dictionary) {
        strLen = target.length();
        if (strLen == 0) return "0";
        for (auto itr = dictionary.begin();
             itr != dictionary.end(); ++itr) {
            if (itr->length() == strLen) insertWord(*itr);
        }
        if (trieRoot == nullptr) return to_string(strLen);
        
        int minLen = strLen;
        string result = target;
        for (int bit = (1 << strLen) - 1; bit >= 0; bit--) {
            int bitLen = 0, currDigit = 0;
            string currAbbr;
            TrieNode *p = trieRoot;
            unordered_set<TrieNode*> validNodes;
            validNodes.insert(trieRoot);
            for (int i = 0; i < strLen; i++) {
                if (bit & (1 << (strLen - i - 1))) {
                    currDigit++;
                    if (i == strLen - 1 || !(bit & (1 << (strLen - i - 2)))) {
                        currAbbr += to_string(currDigit);
                        currDigit = 0;
                        bitLen++;
                    }
                } else {
                    currAbbr += target[i];
                    bitLen++;
                }
                if (bitLen >= minLen) break;
                unordered_set<TrieNode*> newValidNodes;
                for (auto itr = validNodes.begin();
                     itr != validNodes.end(); ++itr) {
                    if (bit & (1 << (strLen - i - 1))) {
                        // all next is ok
                        for (int j = 0; j < 26; j++) {
                            if ((*itr)->next[j] != nullptr) {
                                newValidNodes.insert((*itr)->next[j]);
                            }
                        }
                    } else {
                        if ((*itr)->next[target[i] - 'a'] != nullptr) {
                            newValidNodes.insert((*itr)->next[target[i] - 'a']);
                        }
                    }
                }
                validNodes = newValidNodes;
            }
            if (validNodes.size() == 0 && bitLen < minLen) {
                minLen = bitLen;
                result = currAbbr;
            }
        }
        return result;
    }
};