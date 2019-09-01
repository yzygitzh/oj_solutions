class Solution {
public:
    map<string, map<string, int>> graph;
    vector<string> answer;
    
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (auto p : tickets) {
            graph[p[0]][p[1]]++;
        }
        dfs("JFK");
        reverse(answer.begin(), answer.end());
        return answer;
    }
    
    void dfs(string city) {
        for (auto itr = graph[city].begin();
             itr != graph[city].end(); ++itr) {
            if (itr->second > 0) {
                itr->second--;
                dfs(itr->first);
            }
        }
        answer.push_back(city);
    }
};