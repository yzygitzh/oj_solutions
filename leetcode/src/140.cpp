class Solution {
public:
    class TrieNode {
    public:
        TrieNode* next[26];
        bool isEnd;
        TrieNode() {
            for (int i = 0; i < 26; i++) next[i] = nullptr;
            isEnd = false;
        }
    };
    
    TrieNode *trieRoot;
    
    void insertWord(string word) {
        TrieNode *p = trieRoot;
        for (string::iterator itr = word.begin(); itr != word.end(); ++itr) {
            if (p->next[(*itr) - 'a'] == nullptr) {
                p->next[(*itr) - 'a'] = new TrieNode();
            }
            p = p->next[(*itr) - 'a'];
        }
        p->isEnd = true;
    }
    
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        vector<string> result;
        int sLen = s.size();
        int wordSize = wordDict.size();
        if (wordSize == 0) return result;
        
        trieRoot = new TrieNode();
        
        for (int i = 0; i < wordSize; i++) insertWord(wordDict[i]);
        vector<vector<int> > possibleNext(sLen);
        
        for (int i = sLen - 1; i >= 0; i--) {
            // try walk in trie
            TrieNode *p = trieRoot;
            for (int j = i; j < sLen; j++) {
                p = p->next[s[j] - 'a'];
                if (p == nullptr) break;
                if (p->isEnd && possibleNext[j + 1].size() > 0) {
                    possibleNext[i].push_back(j + 1);
                }
            }
        }
        
        // generate results
        vector<string> partResult;
        genResults(s, 0, possibleNext, partResult, result);
        return result;
    }
    
    void genResults(string& s, int idx, vector<vector<int> >& possibleNext,
                    vector<string>& partResult, vector<string>& result) {
        if (idx == possibleNext.size()) {
            int resultSize = partResult.size();
            string resultStr;
            for (int i = 0; i < resultSize; i++) {
                if (i != 0) resultStr += ' ';
                resultStr += partResult[i];
            }
            result.push_back(resultStr);
        } else {
            for (vector<int>::iterator itr = possibleNext[idx].begin();
                 itr != possibleNext[idx].end(); ++itr) {
                partResult.push_back(s.substr(idx, (*itr) - idx));
                genResults(s, *itr, possibleNext, partResult, result);
                partResult.pop_back();
            }
        }
    }
};