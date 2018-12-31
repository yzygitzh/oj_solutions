class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        vector<string> lineStack;
        int lineWordLen = 0;
        int wordNum = words.size();
        
        for (int i = 0; i < wordNum; i++) {
            // try peek next word
            if (lineWordLen + lineStack.size() +
                words[i].length() <= maxWidth) {
                lineWordLen += words[i].length();
                lineStack.push_back(words[i]);
            } else {
                string justified;
                // justify last line
                if (lineStack.size() == 1) {
                    justified += lineStack[0];
                    justified += string(maxWidth - lineWordLen, ' ');
                } else {
                    int lowSpace = (maxWidth - lineWordLen) /
                                   (lineStack.size() - 1);
                    int lowSpaceStart = (maxWidth - lineWordLen) %
                                        (lineStack.size() - 1);
                    for (int i = 0; i < lineStack.size(); i++) {
                        justified += lineStack[i];
                        if (i + 1 < lineStack.size()) {
                            if (i <  lowSpaceStart) {
                                justified += string(lowSpace + 1, ' ');
                            } else {
                                justified += string(lowSpace, ' ');
                            }
                        }
                    }
                }
                result.push_back(justified);
                // reset
                lineStack.clear();
                lineStack.push_back(words[i]);
                lineWordLen = words[i].length();
            }
        }
        
        if (lineStack.size() > 0) {
            string justified;
            for (int i = 0; i < lineStack.size(); i++) {
                if (i != 0) justified += ' ';
                justified += lineStack[i];
            }
            justified += string(maxWidth - lineWordLen -
                                lineStack.size() + 1, ' ');
            result.push_back(justified);
        }
        
        return result;
    }
};