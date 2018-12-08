class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        char bit2char[4] = {'A', 'C', 'G', 'T'};
        unordered_map<char, unsigned> char2bit;
        char2bit['A'] = 0;
        char2bit['C'] = 1;
        char2bit['G'] = 2;
        char2bit['T'] = 3;
        
        unsigned sBit = 0, sMask = 0x000FFFFF;
        unordered_map<unsigned, unsigned> sCount;
        
        int sLen = s.length();
        for (int i = 0; i < sLen; i++) {
            sBit = ((sBit << 2) | char2bit[s[i]]) & sMask;
            if (i >= 9) sCount[sBit]++;
        }
        
        vector<string> result;
        for (unordered_map<unsigned, unsigned>::iterator itr = sCount.begin();
             itr != sCount.end(); ++itr) {
            if (itr->second > 1) {
                string currResult;
                for (int i = 0; i < 10; i++) {
                    currResult += bit2char[((0x3 << ((9 - i) * 2)) & itr->first) >> ((9 - i) * 2)];
                }
                result.push_back(currResult);
            }
        }
        return result;
    }
};