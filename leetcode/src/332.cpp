/*
 * Hierholzer algorithm for Eularian path
 *
 */

class Solution {
public:
    unordered_map<string, map<string, int>> cityGraph;
    vector<string> path;

    vector<string> findItinerary(vector<pair<string, string>> tickets) {
      // convert city to id
      for (auto itr = tickets.begin(); itr != tickets.end(); ++itr) {
        cityGraph[itr->first][itr->second]++;
      }
      // do hierholzer
      dfs("JFK");
      reverse(path.begin(), path.end());
      return path;
    }

    void dfs(string city) {
      for (auto itr = cityGraph[city].begin();
           itr != cityGraph[city].end(); ++itr) {
        if (itr->second > 0) {
          itr->second--;
          dfs(itr->first);
        }
      }
      path.push_back(city);
    }
};
