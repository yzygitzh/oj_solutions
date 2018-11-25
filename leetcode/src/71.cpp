class Solution {
public:
    string buildResult(vector<string> &fields) {
        // fields contain multiple non-null labels
        string result;
        for (vector<string>::iterator itr = fields.begin();
             itr != fields.end(); ++itr) {
            result += "/";
            result += *itr;
        }
        if (result.length() == 0) result = "/";
        return result;
    }
    string simplifyPath(string path) {
        vector<string> fields;
        int pathLen = path.length();
        int idx = 0;
        while (idx < pathLen) {
            if (path[idx] == '/') {
                // do nothing
            } else {
                int startPos = idx;
                while (idx < pathLen && path[idx] != '/') {
                    idx++;
                }
                idx--;
                string field = path.substr(startPos, idx - startPos + 1);
                if (field == ".") {
                    // do nothing
                } else if (field == "..") {
                    if (fields.size() > 0) fields.pop_back();
                } else {
                    fields.push_back(field);
                }
            }
            idx++;
        }
        return buildResult(fields);
    }
};