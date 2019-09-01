class Solution {
public:
    // minimum string length starts with src and ends with tgt
    int getMinLen(const string& src, const string& tgt) {
        vector<int> next(tgt.length(), 0);
        next[0] = -1;
        int i = 0, j = -1;
        while (i < tgt.length()) {
            while (j >= 0 && tgt[i] != tgt[j]) j = next[j];
            i++, j++;
            if (i == tgt.length()) break;
            if (tgt[i] == tgt[j]) next[i] = next[j];
            else next[i] = j;
        }
        i = 0, j = 0;
        while (i < src.length() && j < tgt.length()) {
            while (j >= 0 && src[i] != tgt[j]) j = next[j];
            i++, j++;
        }
        // first j characters of tgt matches.
        return max(src.length(),
                   src.length() + tgt.length() - j);
    }
    
    string shortestSuperstring(vector<string>& A) {
        // hamilton path
        int N = A.size();
        vector<vector<int>> graph(N, vector<int>(N));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                graph[i][j] = getMinLen(A[i], A[j]);
            }
        }
        // state: low 16 bits: visited nodes, high 16 bits: new node
        // <result len, last node id>
        unordered_map<unsigned, pair<int, int>> memo;
        int minLen = 0x7FFFFFFF;
        int lastNode, lastState;
        for (int i = 0; i < N; i++) {
            unsigned state = ((1 << N) - 1) - (1 << i) + ((1 << i) << 16);
            dfs(state, graph, memo);
            if (memo[state].first < minLen) {
                minLen = memo[state].first;
                lastNode = i;
                lastState = state;
            }
        }
        vector<int> nodeSeq;
        while (true) {
            nodeSeq.push_back(lastNode);
            lastNode = memo[lastState].second;
            if (lastNode == -1) break;
            lastState -= (1 << lastNode);
            lastState &= 0xFFFF;
            lastState += ((1 << lastNode) << 16);
        }
        string result = A[nodeSeq.back()];
        lastNode = nodeSeq.back();
        for (int i = nodeSeq.size() - 2; i >= 0; i--) {
            string& word = A[nodeSeq[i]];
            result += word.substr(word.length() -
                                  (graph[lastNode][nodeSeq[i]] - 
                                   graph[lastNode][lastNode]));
            lastNode = nodeSeq[i];
        }
        return result;
    }
    
    pair<int, int> dfs(unsigned state,
                       vector<vector<int>>& graph,
                       unordered_map<unsigned, pair<int, int>>& memo) {
        if (memo.find(state) == memo.end()) {
            unsigned newNodeRep = (state >> 16), newNode = -1;
            while (newNodeRep) {
                newNode++;
                newNodeRep >>= 1;
            }
            if ((state & 0xFFFF) == 0) {
                memo[state] = make_pair(graph[newNode][newNode], -1);
            } else {
                unsigned visitedNodesRep = state & 0xFFFF;
                int minLen = 0x7FFFFFFF;
                int lastNode;
                for (int i = 0; i < 16; i++) {
                    if (visitedNodesRep & (1 << i)) {
                        auto r = dfs(visitedNodesRep - (1 << i) + ((1 << i) << 16),
                                     graph, memo);
                        int len = r.first + graph[i][newNode] - graph[i][i];
                        if (len < minLen) {
                            minLen = len;
                            lastNode = i;
                        }
                    }
                }
                memo[state] = make_pair(minLen, lastNode);
            }
        }
        return memo[state];
    }
};