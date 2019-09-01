class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        vector<string> result;
        int sizeBeforeBlock;
        bool inBlock = false;
        for (int j = 0; j < source.size(); j++) {
            string& line = source[j];
            if (line.length() == 0) {
                continue;
            }
            if (inBlock) {
                for (int i = 0; i + 1 < line.length(); i++) {
                    if (line[i] == '*' && line[i + 1] == '/') {
                        inBlock = false;
                        if (sizeBeforeBlock == 0) {
                            line = line.substr(i + 2);
                        } else {
                            line = result.back() + line.substr(i + 2);
                            result.pop_back();
                        }
                        j--;
                        break;
                    }
                }
            } else {
                bool hasComment = false;
                for (int i = 0; i + 1 < line.length(); i++) {
                    if (line[i] == '/' && line[i + 1] == '/') {
                        hasComment = true;
                        line = line.substr(0, i);
                        j--;
                        break;
                    } else if (line[i] == '/' && line[i + 1] == '*') {
                        hasComment = true;
                        int idx = i + 2;
                        bool blockEnd = false;
                        while (idx + 1 < line.length()) {
                            if (line[idx] == '*' && line[idx + 1] == '/') {
                                blockEnd = true;
                                break;
                            }
                            idx++;
                        }
                        if (blockEnd) {
                            line = line.substr(0, i) + line.substr(idx + 2);
                            j--;
                        } else {
                            if (i > 0) {
                                result.push_back(line.substr(0, i));
                            }
                            sizeBeforeBlock = i;
                            inBlock = true;
                        }
                        break;
                    }
                }
                if (!hasComment) {
                    result.push_back(line);
                }
            }
        }
        return result;
    }
};