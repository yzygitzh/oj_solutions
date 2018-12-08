class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int wordLen = beginWord.length();
        int wordListLen = wordList.size();
        unordered_map<string, set<string> > adjList;
        for (int i = 0; i < wordListLen; i++) {
            for (int j = i + 1; j < wordListLen; j++) {
                int diffCount = 0;
                for (int k = 0; k < wordLen; k++) {
                    if (wordList[i][k] != wordList[j][k]) {
                        diffCount++;
                    }
                }
                if (diffCount == 1) {
                    adjList[wordList[i]].insert(wordList[j]);
                    adjList[wordList[j]].insert(wordList[i]);
                }
            }
            // also add beginWord's targets
            int diffCount = 0;
            for (int j = 0; j < wordLen; j++) {
                if (wordList[i][j] != beginWord[j]) {
                    diffCount++;
                }
            }
            if (diffCount == 1) {
                adjList[wordList[i]].insert(beginWord);
                adjList[beginWord].insert(wordList[i]);
            }
        }
        unordered_set<string> visited;
        int pathLen = 0;
        queue<pair<string, int> > bfsQ;
        bfsQ.push(make_pair(beginWord, 1));
        visited.insert(beginWord);
        while (!bfsQ.empty()) {
            pair<string, int> currWord = bfsQ.front();
            bfsQ.pop();
            if (currWord.first == endWord) return currWord.second;
            for (set<string>::iterator itr = adjList[currWord.first].begin();
                 itr != adjList[currWord.first].end(); ++itr) {
                if (!visited.count(*itr)) {
                    bfsQ.push(make_pair(*itr, currWord.second + 1));
                    visited.insert(*itr);
                }
            }
        }
        return 0;
    }
};