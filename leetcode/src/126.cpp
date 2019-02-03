class Solution {
public:
    vector<vector<string>> result;
    unordered_map<string, int> wordToId;
    unordered_map<int, string> idToWord;
    int wordLen, wId, endId;
    int shortestLen;

    vector<vector<string>> findLadders(string beginWord, string endWord,
                                       vector<string>& wordList) {
        wordLen = beginWord.length();
        int wordNum = wordList.size();

        wordToId[beginWord] = 0;
        idToWord[0] = beginWord;
        int wId = 1;
        for (int i = 0; i < wordNum; i++) {
            if (!wordToId.count(wordList[i])) {
                wordToId[wordList[i]] = wId;
                idToWord[wId] = wordList[i];
                wId++;
            }
        }
        if (!wordToId.count(endWord)) return result;
        endId = wordToId[endWord];
        
        // find shortest path length
        vector<unordered_set<int>> preNode(wId);
        vector<int> minLen(wId);
        queue<vector<int>> bfsQ;
        bfsQ.push(vector<int>{0});
        while (!bfsQ.empty()) {
            vector<int> top = bfsQ.front();
            bfsQ.pop();
            if (shortestLen > 0 && top.size() > shortestLen) break;
            if (*top.rbegin() == endId) {
                shortestLen = top.size();
            } else {
                string lastWord = idToWord[*top.rbegin()];
                for (int i = 0; i < wordLen; i++) {
                    char oldChar = lastWord[i];
                    for (int j = 0; j < 26; j++) {
                        char newChar = (char)('a' + j);
                        lastWord[i] = newChar;
                        if (wordToId.count(lastWord)) {
                            int lastId = wordToId[lastWord];
                            vector<int> newPath = top;
                            newPath.push_back(lastId);
                            if (preNode[lastId].size() == 0) {
                                bfsQ.push(newPath);
                                minLen[lastId] = newPath.size();
                                preNode[lastId].insert(*top.rbegin());
                            } else if (newPath.size() == minLen[lastId]) {
                                preNode[lastId].insert(*top.rbegin());
                            }
                        }
                    }
                    lastWord[i] = oldChar;
                }
            }
        }
        
        // generate all paths by dfs on preNode
        vector<int> partResult{endId};
        dfs(partResult, preNode);
        
        return result;
    }
    
    void dfs(vector<int>& partResult, vector<unordered_set<int>>& preNode) {
        if (*partResult.rbegin() == 0) {
            vector<string> path;
            for (auto itr = partResult.rbegin(); itr != partResult.rend(); ++itr) {
                path.push_back(idToWord[*itr]);
            }
            result.push_back(path);
        } else {
            int lastId = *partResult.rbegin();
            for (auto itr = preNode[lastId].begin();
                 itr != preNode[lastId].end(); ++itr) {
                partResult.push_back(*itr);
                dfs(partResult, preNode);
                partResult.pop_back();
            }
        }
    }
};