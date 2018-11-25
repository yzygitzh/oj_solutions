class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;

        int sLen = s.length();
        if (sLen == 0 ||
            words.size() == 0 ||
            words[0].length() == 0 ||
            words[0].length() > sLen) {
            return result;
        }
        int wordLen = words[0].length();
        int wordNum = words.size();

        map<string, int> wordCount;
        map<string, queue<int> > wordOccur;
        for (vector<string>::iterator itr = words.begin();
             itr != words.end(); ++itr) {
            wordCount[*itr]++;
            wordOccur[*itr] = queue<int>();
        }
        
        vector<map<string, queue<int> > > wordUsage(wordLen + 1);
        vector<int> validWords(wordLen + 1, 0);
        for (int i = 0; i < wordLen; i++) {
            wordUsage[i] = wordOccur;
        }
        // bound condition
        if (wordCount.find(s.substr(0, wordLen)) != wordCount.end()) {
            wordUsage[wordLen - 1][s.substr(0, wordLen)].push(0);
            validWords[wordLen - 1]++;
            if (validWords[wordLen - 1] == wordNum) {
                result.push_back(0);
            }
        }
        
        for (int i = wordLen; i < sLen; i++) {
            // update wordUsage
            string currSeg = s.substr(i - wordLen + 1, wordLen);
            if (wordCount.find(currSeg) != wordCount.end()) {
                // doing push/pop according to wordCount
                wordUsage[i % (wordLen + 1)] = wordUsage[(i - wordLen) % (wordLen + 1)];
                validWords[i % (wordLen + 1)] = validWords[(i - wordLen) % (wordLen + 1)];
                // some word runs out. pop until first met.
                if (wordUsage[i % (wordLen + 1)][currSeg].size() == wordCount[currSeg]) {
                    int finalPos = wordUsage[i % (wordLen + 1)][currSeg].front();
                    for (map<string, queue<int> >::iterator itr =
                         wordUsage[i % (wordLen + 1)].begin();
                         itr != wordUsage[i % (wordLen + 1)].end(); ++itr) {
                        while (itr->second.front() <= finalPos) {
                            itr->second.pop();
                            validWords[i % (wordLen + 1)]--;
                        }
                    }
                }
                wordUsage[i % (wordLen + 1)][currSeg].push(i - wordLen + 1);
                validWords[i % (wordLen + 1)]++;
                if (validWords[i % (wordLen + 1)] == wordNum) {
                    result.push_back(i - wordNum * wordLen + 1);
                }
            } else {
                // initial wordUsage and validWords
                validWords[i % (wordLen + 1)] = 0;
                wordUsage[i % (wordLen + 1)] = wordOccur;
            }
        }
        
        return result;
    }
};