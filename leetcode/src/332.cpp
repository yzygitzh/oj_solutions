class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        unordered_map<string, int> visited;
        unordered_map<string, set<string> > itinerary;
        int ticketsLen = tickets.size();
        vector<string> partResult, result;
        for (int i = 0; i < ticketsLen; i++) {
            itinerary[tickets[i].first].insert(tickets[i].second);
            visited[tickets[i].first + "-" + tickets[i].second]++;
        }
        DFS("JFK", partResult, result, itinerary, visited, ticketsLen);
        return result;
    }
    
    void DFS(string city, vector<string> &partResult, vector<string> &result,
             unordered_map<string, set<string> > &itinerary,
             unordered_map<string, int> &visited, int restTravel) {
        partResult.push_back(city);
        if (restTravel == 0) {
            if (result.size() == 0) result = partResult;
        } else {
            for (set<string>::iterator itr = itinerary[city].begin();
                 itr != itinerary[city].end(); ++itr) {
                if (visited[city + "-" + *itr]) {
                    visited[city + "-" + *itr] -= 1;
                    DFS(*itr, partResult, result, itinerary, visited, restTravel - 1);
                    visited[city + "-" + *itr] += 1;
                }
                if (result.size() != 0) break;
            }
        }
        partResult.pop_back();
    }
};