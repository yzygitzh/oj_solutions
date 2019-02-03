class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        int seqLen = start.length();
        char acids[4] = {'A', 'C', 'G', 'T'};

        unordered_map<string, int> visited;
        for (auto itr = bank.begin(); itr != bank.end(); ++itr) {
            visited[*itr] = 0;
        }
        
        queue<pair<string, int>> bfsQ;
        bfsQ.push(make_pair(start, 0));
        if (visited.find(start) != visited.end()) {
            visited[start] = 1;
        }
        
        while (!bfsQ.empty()) {
            pair<string, int> state = bfsQ.front();
            bfsQ.pop();
            if (state.first == end) return state.second;
            string mutated = state.first;
            for (int i = 0; i < seqLen; i++) {
                if (i > 0) mutated[i - 1] = state.first[i - 1];
                for (int j = 0; j < 4; j++) {
                    if (acids[j] == state.first[i]) continue;
                    mutated[i] = acids[j];
                    if (visited.find(mutated) != visited.end() &&
                        !visited[mutated]) {
                        visited[mutated] = 1;
                        bfsQ.push(make_pair(mutated, state.second + 1));
                    }
                }
            }
        }
        
        return -1;
    }
};