class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string, vector<string> > groupResult;
        vector<vector<string> > result;
        
        for (vector<string>::iterator itr = strs.begin();
             itr != strs.end(); ++itr) {
            string sid = *itr;
            sort(sid.begin(), sid.end());
            if (groupResult.find(sid) == groupResult.end()) {
                groupResult[sid] = vector<string>();
            }
            groupResult[sid].push_back(*itr);
        }
        
        for (map<string, vector<string> >::iterator itr =
             groupResult.begin(); itr != groupResult.end(); ++itr) {
            result.push_back(itr->second);
        }
        
        return result;
    }
};