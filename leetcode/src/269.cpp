class Solution {
public:
    string alienOrder(vector<string>& words) {
        // topological sort
        // init graph
        unordered_set<char> charSet;
        unordered_map<char, unordered_set<char>> adjList;
        unordered_map<char, int> inDegree;
        int wordsNum = words.size();
        for (int i = 0; i < wordsNum; i++) {
            int word1Len = words[i].length();
            for (int j = 0; j < word1Len; j++) {
                charSet.insert(words[i][j]);
                if (!inDegree.count(words[i][j])) {
                    inDegree[words[i][j]] = 0;
                }
            }
            if (i + 1 < wordsNum) {
                int word2Len = words[i + 1].length();
                for (int j = 0; j < word1Len && j < word2Len; j++) {
                    if (words[i][j] != words[i + 1][j]) {
                        if (!adjList[words[i][j]].count(words[i + 1][j])) {
                            adjList[words[i][j]].insert(words[i + 1][j]);
                            inDegree[words[i + 1][j]]++;
                        }
                        break;
                    }
                }
            }
        }
        // do sort
        string result;
        queue<char> zeroQ;
        for (auto itr = inDegree.begin(); itr != inDegree.end(); ++itr) {
            if (itr->second == 0) {
                zeroQ.push(itr->first);
            }
        }
        while (!zeroQ.empty()) {
            char currNode = zeroQ.front();
            zeroQ.pop();
            result += currNode;
            for (auto itr = adjList[currNode].begin();
                 itr != adjList[currNode].end(); ++itr) {
                inDegree[*itr]--;
                if (inDegree[*itr] == 0) {
                    zeroQ.push(*itr);
                }
            }
            adjList.erase(currNode);
        }
        if (adjList.size() == 0) return result;
        else return "";
    }
};