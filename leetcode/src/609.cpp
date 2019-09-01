class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        map<string, vector<string>> contentToFiles;
        for (auto& path : paths) {
            int idx = 0;
            
            while (path[idx] != ' ') {
                idx++;
            }
            string dir = path.substr(0, idx);
            idx++;
            
            while (idx < path.length()) {
                int fileNameIdx = idx;
                while (path[idx] != '(') {
                    idx++;
                }
                string fileName = path.substr(fileNameIdx, idx - fileNameIdx);
                idx++;
                
                int contentIdx = idx;
                while (path[idx] != ')') {
                    idx++;
                }
                string content = path.substr(contentIdx, idx - contentIdx);
                idx += 2;
                
                contentToFiles[content].push_back(dir + "/" + fileName);
            }
        }
        vector<vector<string>> result;
        for (auto& p : contentToFiles) {
            if (p.second.size() > 1) {
                result.push_back(p.second);
            }
        }
        return result;
    }
};