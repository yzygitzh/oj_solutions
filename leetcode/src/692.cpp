class Solution {
public:
    class Cmp {
    public:
       bool operator() (const pair<int, string>& a, const pair<int, string>& b) const {
           return a.first != b.first ? a.first > b.first : a.second < b.second;
       }
    };
    
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> wordCnt;
        for (auto& word : words) {
            wordCnt[word]++;
        }
        priority_queue<pair<int, string>, vector<pair<int, string>>, Cmp> minHeap;
        for (auto& p : wordCnt) {
            auto currPair = make_pair(p.second, p.first);
            minHeap.push(currPair);
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        vector<string> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};