class Solution {
public:
    vector<string> generateAbbreviations(string word) {
        int wordLen = word.length();
        vector<string> result;
        result.push_back("");
        
        for (int i = 0; i < wordLen; i++) {
            vector<string> newResult;
            int currResultNum = result.size();
            for (int j = 0; j < currResultNum; j++) {
                string currAbbr = result[j];
                // plus letter
                newResult.push_back(currAbbr + word.substr(i, 1));
                // plus one
                int lastIdx = currAbbr.length() - 1;
                int lastNum = 0;
                int currRate = 1;
                while (lastIdx >= 0 &&
                       currAbbr[lastIdx] >= '0' && currAbbr[lastIdx] <= '9') {
                    lastNum += (currAbbr[lastIdx] - '0') * currRate;
                    currRate *= 10;
                    lastIdx--;
                }
                newResult.push_back(currAbbr.substr(0, lastIdx + 1) +
                                    to_string(lastNum + 1));
            }
            result = newResult;
        }
        return result;
    }
};