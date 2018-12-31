class Solution {
public:
    int getMin(int a, int b) {
        return a < b ? a : b;
    }
    
    string getHint(string secret, string guess) {
        unordered_map<char, int> secretCnt, guessCnt;
        int bulls = 0, cows = 0;
        int sLen = secret.length();
        
        for (int i = 0; i < sLen; i++) {
            if (secret[i] == guess[i]) {
                bulls++;
            } else {
                secretCnt[secret[i]]++;
                guessCnt[guess[i]]++;
            }
        }
        
        for (unordered_map<char, int>::iterator itr = secretCnt.begin();
             itr != secretCnt.end(); ++itr) {
            if (guessCnt.find(itr->first) != guessCnt.end()) {
                cows += getMin(itr->second, guessCnt[itr->first]);
            }
        }
        
        string hint;
        hint += to_string(bulls);
        hint += "A";
        hint += to_string(cows);
        hint += "B";
        return hint;
    }
};