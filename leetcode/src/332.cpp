/*
 * LeetCode 332 Reconstruct Itinerary
 * Hierholzer algorithm for Eularian path
 * 1. visitedå»ºå¨è¾¹ä¸èä¸æ¯ç¹ä¸
 */

class Solution {
public:
  unordered_map<string, map<string, int>> adjList;
  vector<string> result;

  vector<string> findItinerary(vector<pair<string, string>> tickets) {
    for (auto& ticket : tickets) {
      adjList[ticket.first][ticket.second]++;
    }
    dfs("JFK");
    reverse(result.begin(), result.end());
    return result;
  }

  void dfs(string city) {
    for (auto itr = adjList[city].begin();
         itr != adjList[city].end(); ++itr) {
      if (itr->second > 0) {
        itr->second--;
        dfs(itr->first);
      }
    }
    result.push_back(city);
  }

};