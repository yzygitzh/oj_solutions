class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string, vector<string> > buckets;
        vector<vector<string> > result;
        
        for (vector<string>::iterator itr = strings.begin();
             itr != strings.end(); ++itr) {
            // calc key
            if (itr->length() > 0) {
                string key;
                int delta = (*itr)[0] - 'a';
                for (string::iterator itr2 = itr->begin();
                     itr2 != itr->end(); ++itr2) {
                    key += 'a' + (((*itr2) - 'a' - delta + 26) % 26);
                }
                buckets[key].push_back(*itr);
            } else {
                buckets[""].push_back("");
            }
        }
        
        for (auto itr = buckets.begin(); itr != buckets.end(); ++itr) {
            result.push_back(itr->second);
        }
        return result;
    }
};